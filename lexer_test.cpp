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
  if (is_alpha(c)){
    return lexer_alpha(sql_state, sql);
  }
  if (is_all(c)){SKIP; goto loop;}
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
      if (is_dot(c)) return TOK_ERROR;
      goto loop;
    }
    if (is_alpha(c)){
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

sql_token lexer_select(char *buffer, sqlselect *sql){
  struct sqlidentifier i(0, 0);
  struct sqlstate sql_state(buffer, 0, i);
  sql_token t = lexer_select_next(&sql_state, sql);
  if (t != TOK_SELECT) return TOK_ERROR;
  //return t;
  t = lexer_select_columns(&sql_state, sql);
  if (t != TOK_FROM || t == TOK_ERROR) return TOK_ERROR;

  /* lexer form clause */

  return t;
}

int main(){
  char buffer[] = "select users.username, users.name from users where users.email = 'setheang@gmail.com'";
  sqlselect sql;
  sql_token t = lexer_select(buffer, &sql);
  assert(t==TOK_FROM);
  std::cout << "Parsing return TOK_FROM\n";
  sql.print_table();
  sql.print_columns();
  char buffer2[] = "select .username, users.name from users where users.email = 'setheang@gmail.com'";
  sqlselect sql2;
  sql_token t2 = lexer_select(buffer2, &sql2);
  assert(t2 == TOK_ERROR);
  std::cout << "Parsing return ERROR token\n";
  sql2.print_table();
  sql2.print_columns();
}
