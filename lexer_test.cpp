#include <iostream>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <cassert>
#include "sqlselect.h"
#include "keyword.h"
#include "utils.h"

#define PEEK (sql_state->buffer[sql_state->offset])
#define SKIP (sql_state->offset++)

using namespace std;

sql_token slice_buffer(char *buffer, int offset, int length){
  char sliced[length];
  int i=0;
  while (i<length){
    sliced[i] = buffer[i + offset];
    i++;
  }
  sliced[i] = '\0';
  return sql_keyword(sliced, length);
}


void lexer_alpha(sqlstate *sql_state){
  int offset = sql_state->offset;
  while (is_identifier(PEEK)){
    sql_state->offset++;
  }
  int length = sql_state->offset - offset;
}

// lexer alphabetical string for select statement
sql_token lexer_alpha(sqlstate *sql_state, sqlselect *sql){
  int offset = sql_state->offset;
  while (is_identifier(PEEK)){
    sql_state->offset++;
  }
  int length = sql_state->offset - offset;
  sql_token t = slice_buffer(sql_state->buffer, offset, length);

  if (t != TOK_IDENTIFIER) return t;
  sql_state->identifier.offset = offset;
  sql_state->identifier.length = length;
  return TOK_IDENTIFIER;
}

// lexer numerical string for select statement
//sql_token lexer_num(sqlstate *sql_state, sqlselect *sql){

//}

void lexer_next(sqlstate *sql_state){
  char c = PEEK;
  //cout<<"peek: "<<c<<endl;
  if (is_alpha(c)) {
    lexer_alpha(sql_state);
  }
  c = PEEK;
  //cout<<"peek: "<<c<<endl;
  if (is_space(c)) SKIP; cout<<"skip once\n";
  c = PEEK;
  //cout<<"peek: "<<c<<endl;
  if (is_all(c)) SKIP; cout<<"skip once\n";
}

// lexer analysis for select statement
sql_token lexer_select_next(sqlstate *sql_state, sqlselect *sql){
loop:
  char c = PEEK;
  if (is_space(c)){
    SKIP;
    goto loop;
   }
   /* to be changed */
  if (is_identifier(c)){
    return lexer_alpha(sql_state, sql);
  }
  /* checking if is digit */
  if (is_digit(c)){

  }
  if (is_all(c)){SKIP; goto loop;}
  if (is_quote(c)){SKIP; goto loop;}
  if (is_terminator(c)){return TOK_TERMINATOR;}

  return TOK_ERROR;
}

// lexer the selected target columns
//   "user.name, user.email"
// or  "name, email"
/* lexer of aggregate function needed */
sql_token lexer_select_columns(sqlstate *sql_state, sqlselect *sql){
  loop:
    char c =PEEK;
    if (is_space(c)){
      SKIP;
      c = PEEK;
      // when there is no table name coming befor the dot '.'
      if (is_dot(c)) return TOK_ERROR;
      goto loop;
    }
    if (is_identifier(c)){
      sql_token t = lexer_alpha(sql_state, sql);
      /* put the target column name into sql */
      if (t == TOK_FROM) return t;
      c = PEEK;
      if (is_dot(c)){
        SKIP;
        char name[10];
        extract(sql_state, name);
        string table_name(name);
        sql->set_table(table_name);
        //cout<<"table name: "<<table_name<<endl;
        goto loop;
      }
      else {
        char name[10];
        extract(sql_state, name);
        string n(name);
        sqlcolumn col(n);
        //cout<<"column name: "<<col.name<<endl;
        sql->add_column(col);
        goto loop;
      }
    }
    if (is_puntuation(c)){
      SKIP;
      goto loop;
    }
    return TOK_ERROR;
}

// lexer the SQL where clauses
sql_token lexer_select_where(sqlstate *sql_state, sqlselect *sql){
  loop:
    char c = PEEK;
    if (is_space(c)){
      SKIP;
      c = PEEK;
      // when there is no table name coming befor the dot '.'
      // ie where .username = ''
      if (is_dot(c)) return TOK_ERROR;
      goto loop;
    }
    if (is_alpha(c)){
      sql_token t = lexer_alpha(sql_state, sql);
      if (t == TOK_AND) {goto loop;}
      c = PEEK;
      if (is_dot(c)){
        SKIP;
        char name[10];
        extract(sql_state, name);
        string table_name(name);

        cout<<"table name:"<<table_name<<endl;

        if (table_name != sql->get_table()) return TOK_ERROR;
        goto loop;
      }
      else{
        char name[10];
        extract(sql_state, name);
        string column_name(name);

        cout<<"column name: "<<column_name<<endl;

        sqlcolumn col(column_name);
        // where username = ''
        while (PEEK != '='){
          SKIP;
        }
        SKIP;
        sql_token t = lexer_select_next(sql_state, sql);
        extract(sql_state, name);
        string value(name);

        cout<<"value name: "<<value<<endl;

        sql->add_where(col, value);
        goto loop;
      }
    }
    if (is_puntuation(c)) SKIP;
    if (is_terminator(c)) return TOK_TERMINATOR;
    if (is_quote(c)){SKIP; goto loop;}

    return TOK_ERROR;
}

sql_token lexer_select(char *buffer, sqlselect *sql){
  struct sqlidentifier i(0, 0);
  struct sqlstate sql_state(buffer, 0, i);
  sql_token t = lexer_select_next(&sql_state, sql);
  if (t != TOK_SELECT) return TOK_ERROR;

  // lexer the targeted columns
  t = lexer_select_columns(&sql_state, sql);
  if (t != TOK_FROM || t == TOK_ERROR){
    cout<<"Syntax error around the column names"<<endl;
    return TOK_ERROR;}

  // lexer the table name
  t = lexer_select_next(&sql_state, sql);
  char name[10];
  extract(&sql_state, name);
  string table_name(name);
  if (sql->get_table() != table_name){
    cout<<"Table name not matching."<<endl;
    return TOK_ERROR;
  }

  t = lexer_select_next(&sql_state, sql);
  if (t == TOK_TERMINATOR) return t;
  if (t != TOK_WHERE) return TOK_ERROR;
  /* lexer the where clauses */

  t = lexer_select_where(&sql_state, sql);
  if (t != TOK_TERMINATOR) return TOK_ERROR;
  return t;
}

int main(){

  // Wrong SQL where the table name not matching
  char buffer[] = "select users.username, users.name from use where users.email = 'setheang@gmail.com'";
  sqlselect sql;
  sql_token t = lexer_select(buffer, &sql);
  assert(t==TOK_ERROR);
  cout<<buffer<<endl;
  std::cout << "Parsing return TOK_ERROR"<<endl;

  cout<<endl;

  // Wrong SQL command where an additional dot "." coming before the column names
  char buffer2[] = "select .username, users.name from users where users.email = 'setheang@gmail.com'";
  sqlselect sql2;
  sql_token t2 = lexer_select(buffer2, &sql2);
  assert(t2 == TOK_ERROR);
  cout<<buffer2<<endl;
  std::cout << "Parsing return ERROR token"<<endl;

  cout<<endl;

  char buffer3[] = "select users.username, users.name from users;";
  sqlselect sql3;
  sql_token t3 = lexer_select(buffer3, &sql3);
  //assert(t3 == TOK_TERMINATOR);
  cout<<buffer3<<endl;
  std::cout << "Parsing return TERMINATOR token"<<endl;
  sql3.print_table();
  sql3.print_columns();

  cout<<endl;

  // only lexer until where keyword
  /*char buffer4[] = "select users.username, users.name from users where users.email = 'sethwang199418@gmail.com'";
  sqlselect sql4;
  sql_token t4 = lexer_select(buffer4, &sql4);
  assert(t4 == TOK_WHERE);
  cout<<buffer4<<endl;
  std::cout << "Parsing return WHERE token"<<endl;
  sql4.print_table();
  sql4.print_columns();
  */

  /* ---------------------------------------------------------------------------- */
  /* Test of lexer with 1 where clause */
  char buffer5[] = "select users.username, users.name from users where users.username = 'sethwang';";
  sqlselect sql5;
  sql_token t5 = lexer_select(buffer5, &sql5);
  assert(t5 == TOK_TERMINATOR);
  cout<<buffer5<<endl;
  cout<< "Parsing return TERMINATOR token"<<endl;
  sql5.print_table();
  sql5.print_columns();
  sql5.print_wheres();

  cout<<endl;
  /* ---------------------------------------------------------------------------- */
  /* Test of lexer with more than 1 where clause */
  char buffer6[] = "select users.username, users.name from users where users.username = 'sethwang' and users.age=21;";
  sqlselect sql6;
  sql_token t6 = lexer_select(buffer6, &sql6);
  assert(t6 == TOK_TERMINATOR);
  cout<<buffer6<<endl;
  cout<< "Parsing return TERMINATOR token"<<endl;
  sql6.print_table();
  sql6.print_columns();
  sql6.print_wheres();

  cout<<endl;
}
