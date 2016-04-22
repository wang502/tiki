#include <iostream>
#include <algorithm>
#include <cctype>

#define PEEK (sql_state->buffer[sql_state->offset])
#define SKIP (sql_state->offset++)

using namespace std;

struct sqlstate{
  char *buffer;
  int offset;
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

void lexer(char *sql){
  struct sqlstate sql_state;
  sql_state.buffer = sql;
  sql_state.offset = 0;
  while (sql_state.offset <= strlen(sql_state.buffer)-1){
    lexer_next(&sql_state);
  }
}

int main(){
  char sql[] = "select * from users";
  lexer(sql);
}
