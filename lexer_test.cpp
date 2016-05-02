#include <iostream>
#include <algorithm>
#include <cctype>
#include <cstring>
#include "sqlselect.h"
#include "keyword.h"
//#include "utils.h"

#define PEEK (sql_state->buffer[sql_state->offset])
#define SKIP (sql_state->offset++)

using namespace std;

// extract slice of string given the buffer, offset position and length
void extract(sqlstate *state, char *copy){
  int i;
  int offset = state->identifier.offset;
  int length = state->identifier.length;

  for (i=0; i<length; i++){
    *(copy+i) = *(state->buffer+offset+i);
  }
  *(copy+i) = '\0';
}

bool is_identifier(char c){
  return isalpha(c) || isdigit(c) || c == '_';
}

bool is_alpha(char c){
  return isalpha(c);
}

bool is_space(char c){
  return c == ' ' || c == '\t' || c == '\v' || c == '\f';
}
bool is_all(char c){
  return c == '*';
}

bool is_dot(char c){
  return c == '.';
}

bool is_puntuation(char c){
  return c == ',' || c == ';' || c == '(' || c == ')';
}

bool is_equal(char c){
  return c == '=';
}

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
  //sqlidentifier i(offset, length);
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
  //c = PEEK;
  //if (is_space(c)) SKIP;
  if (is_all(c)){SKIP; goto loop;}
  return TOK_ERROR;
}

// lexer the selected target columns
//   "user.name, user.email"
// or  "name, email"
sql_token lexer_select_columns(sqlstate *sql_state, sqlselect *sql){
  loop:
    char c =PEEK;
    if (is_space(c)){
      SKIP;
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
  //sql_state.buffer = buffer;
  //sql_state.offset = 0;
  //sql_state.identifier = i;
  //while (sql_state.offset <= strlen(sql_state.buffer)-1){
  sql_token t = lexer_select_next(&sql_state, sql);
  if (t != TOK_SELECT) return TOK_ERROR;
  //return t;
  t = lexer_select_columns(&sql_state, sql);
  if (t != TOK_FROM || t == TOK_ERROR) return TOK_ERROR;
  return t;
  //delete(sql);
}

int main(){
  char buffer[] = "select <users.username, users.name from users where users.email = 'setheang@gmail.com'";
  sqlselect sql;
  cout<<lexer_select(buffer, &sql)<<endl;
  cout<<sql.get_table()<<endl;
  sql.print_columns();
}
