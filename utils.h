#ifndef UTILS_H
#define UTILS_H
#include <cstring>
/* This file contains function that do string manipulation, string matching, character matching */


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


#endif
