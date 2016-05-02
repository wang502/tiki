#include <iostream>
#include "sqlselect.h"
#include <vector>
using namespace std;

sqlselect::sqlselect(){}

void sqlselect::add_column(sqlcolumn target){
  this->columns.push_back(target);
}

void sqlselect::add_where(sqlcolumn column, sqlstring value){
  sqlwhere where(column, value);
  this->wheres.push_back(where);
}
void sqlselect::set_table(string t){
  this->table = t;
}
