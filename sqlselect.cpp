#include <iostream>
#include "sqlselect.h"
#include <vector>
using namespace std;

sqlselect::sqlselect(){}

void sqlselect::add_target(sqlcolumn target){
  this->targets.push_back(target);
}

void sqlselect::add_where(sqlcolumn column, sqlstring value){
  sqlwhere where(column, value);
  this->wheres.push_back(where);
}
