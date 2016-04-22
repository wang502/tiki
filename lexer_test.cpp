#include <iostream>
#include <algorithm>
#include <cctype>

#define PEEK (sql_state->buffer[sql_state->offset])
using namespace std;

struct sqlstate{
  char *buffer;
  int offset;
};

bool is_identifier(char c){
  return isalpha(c) || isdigit(c) || c == '_';
}

bool is_alphe(char c){
  return isalpha(c);
}

void lexer_alpha(sqlstate *sql_state){
  int offset = sql_state->offset;
  while (is_identifier(PEEK)){
    sql_state->offset++;
  }
  int length = sql_state->offset - offset;
  cout<<length<<endl;
}

void lexer_next(sqlstate *sql_state){
  char c = PEEK;
  if (isalpha(c)) lexer_alpha(sql_state);
}

void lexer(char *sql){
  struct sqlstate sql_state;
  sql_state.buffer = sql;
  sql_state.offset = 0;
  lexer_next(&sql_state);
}

int main(){
  char sql[] = "select * from users";
  lexer(sql);
}
