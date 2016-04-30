#include <iostream>
#include <algorithm>
#include <cctype>
#include <cstring>
#include "sqlselect.h"
#include "keyword.h"

#define PEEK (sql_state->buffer[sql_state->offset])
#define SKIP (sql_state->offset++)

using namespace std;

struct sqlidentifier{
  char *buffer;
  int length;
};

struct sqlstate{
  char *buffer;
  int offset;
  sqlidentifier *identifier;
};

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
  cout<<sliced<<endl;
  return sql_keyword(sliced, length);
}


void lexer_alpha(sqlstate *sql_state){
  int offset = sql_state->offset;
  while (is_identifier(PEEK)){
    sql_state->offset++;
  }
  int length = sql_state->offset - offset;
  cout<<length<<endl;
}

// lexer alphabetical string for select statement
sql_token lexer_alpha(sqlstate *sql_state, sqlselect *sql){
  int offset = sql_state->offset;
  while (is_identifier(PEEK)){
    sql_state->offset++;
  }
  int length = sql_state->offset - offset;
  sql_token t = slice_buffer(sql_state->buffer, offset, length);
  cout<<length<<endl;
  if (t != TOK_IDENTIFIER) return t;
  sqlidentifier *i;
  i->buffer = sql_state->buffer;
  i->length = length;
  sql_state->identifier = i;
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
  if (is_all(c)){SKIP; cout<<"skip once\n"; goto loop;}
  return TOK_ERROR;
}

sql_token lexer_select_target(sql_state *state, sql *sql){
  loop:
    char c =PEEK;
    if (is_space(c)){
      SKIP;
      goto loop;
    }
    if (is_dot(c)){
      SKIP;
      lexer_alpha(state, sql);
      /* put the target column name into sql */
      
    }
}

sql_token lexer_select(char *buffer, sqlselect *sql){
  struct sqlstate sql_state;
  sql_state.buffer = buffer;
  sql_state.offset = 0;
  //while (sql_state.offset <= strlen(sql_state.buffer)-1){
  sql_token t = lexer_select_next(&sql_state, &sql);
  if (t != TOK_SELECT) return TOK_ERROR;
  //return t;
  t = lexer_select_targets(&sql_state, &sql);
  //delete(sql);
}

int main(){
  char buffer[] = "select username from users where user.email = 'setheang@gmail.com'";
  sqlselect sql;
  cout<<lexer_select(buffer, &sql)<<endl;
  //char keyword[] = "null";
  //cout<<sql_keyword(keyword, 4)<<endl;
}
