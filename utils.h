#ifndef UTILS_H
#define UTILS_H
#include <cstring>

string extract(sqlstate *state){
  char *copy;
  int i;
  cout<<"o: "<<state->buffer<<endl;
  int offset = state->identifier.offset;
  int length = state->identifier.length;
  cout<<"o: "<<state->identifier.offset<<endl;
  for (i=0; i<length; i++){
    *(copy+i) = *(state->buffer+offset+i);
  }
  *(copy+i) = '\0';
  cout<<"string: "<<copy<<endl;
  string str(copy);
  cout<<"string: "<<str<<endl;
  return str;
}
#endif
