#include <iostream>
#include <algorithm>
#include <cctype>
#include <cstring>
#include "sqlselect.h"

#define PEEK (sql_state->buffer[sql_state->offset])
#define SKIP (sql_state->offset++)

typedef enum{
  TOK_NULL, TOK_DELETE, TOK_ORDER, TOK_BY,
  TOK_FROM, TOK_SELECT, TOK_HAVING, TOK_TRUNCATE,
  TOK_INSERT, TOK_UNION, TOK_UPDATE, TOK_JOIN, TOK_WHERE,
  TOK_MERGE, TOK_DEFAULT
} sql_token;

using namespace std;

struct sqlstate{
  char *buffer;
  int offset;
};

sql_token sql_keyword(char *str, int length){
  switch (length) {
    case 2:
      if (!strcasecmp(str, "by"))
        return TOK_BY;
      break;
    case 4:
      if (!strcasecmp(str, "null"))
        return TOK_NULL;
      if (!strcasecmp(str, "from"))
        return TOK_FROM;
      if (!strcasecmp(str, "join"))
        return TOK_JOIN;
      break;
    case 5:
      if (!strcasecmp(str, "order"))
        return TOK_ORDER;
      if (!strcasecmp(str, "union"))
        return TOK_UNION;
      if (!strcasecmp(str, "where"))
        return TOK_WHERE;
      if (!strcasecmp(str, "merge"))
        return TOK_MERGE;
      break;
    case 6:
      if (!strcasecmp(str, "select"))
        return TOK_SELECT;
      if (!strcasecmp(str, "delete"))
        return TOK_DELETE;
      if (!strcasecmp(str, "insert"))
        return TOK_INSERT;
      if (!strcasecmp(str, "update"))
        return TOK_UPDATE;
      if (!strcasecmp(str, "having"))
        return TOK_HAVING;
      break;
  }
  return TOK_DEFAULT;
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

bool is_puntuation(char c){
  return c == '.' || c == ',' || c == ';' || c == '(' || c == ')';
}

bool is_equal(char c){
  return c == '=';
}

void slice_buffer(char *buffer, int offset, int length){
  char sliced[length];
  int i=0;
  while (i<length){
    sliced[i] = buffer[i + offset];
    i++;
  }
  sliced[i] = '\0';
  cout<<sliced<<endl;
}


void lexer_alpha(sqlstate *sql_state){
  int offset = sql_state->offset;
  while (is_identifier(PEEK)){
    sql_state->offset++;
  }
  int length = sql_state->offset - offset;
  slice_buffer(sql_state->buffer, offset, length);
  cout<<length<<endl;
}

void lexer_alpha(sqlstate *sql_state, sqlselect *sql){
  int offset = sql_state->offset;
  while (is_identifier(PEEK)){
    sql_state->offset++;
  }
  int length = sql_state->offset - offset;
  slice_buffer(sql_state->buffer, offset, length);
  cout<<length<<endl;
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
void lexer_select_next(sqlstate *sql_state, sqlselect *sql){
  char c = PEEK;
  if (is_alpha(c)){
    lexer_alpha(sql_state, sql);
  }
  c = PEEK;
  if (is_space(c)) SKIP;
}

void lexer_select(char *buffer){
  struct sqlstate sql_state;
  //sqlselect *sql = new sqlselect();
  sqlselect sql;
  sql_state.buffer = buffer;
  sql_state.offset = 0;
  while (sql_state.offset <= strlen(sql_state.buffer)-1){
    lexer_select_next(&sql_state, &sql);
  }
  //delete(sql);
}

int main(){
  char sql[] = "select * from users where ";
  //lexer_select(sql);
  char keyword[] = "null";
  cout<<sql_keyword(keyword, 4)<<endl;
}
