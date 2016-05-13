#include <iostream>
#include "sqlselect.h"
#include <vector>
using namespace std;

sqlselect::sqlselect(){}

void sqlselect::add_column(sqlcolumn target){
  this->columns.push_back(target);
}

void sqlselect::add_where(sqlcolumn column, string value){
  sqlwhere where(column, value);
  this->wheres.push_back(where);
}
void sqlselect::set_table(string t){
  this->table = t;
}
void sqlselect::set_order_by(string o){
  this->order_by = o;
  this->order = true;
}
string sqlselect::get_table(){
  return this->table;
}
void sqlselect::print_columns(){
  cout<<"columns: ";
  for (int i=0; i<this->columns.size(); i++){
    cout<<this->columns[i].name<<", ";
  }
  cout<<endl;
}

void sqlselect::print_table(){
  cout<<"table: "<<this->table<<endl;
}

void sqlselect::print_wheres(){
  for (int i=0; i<this->wheres.size();i++){
    cout<<this->wheres[i].column.name<<"="<<this->wheres[i].value<<endl;
  }
}

void sqlselect::print_order_by(){
  cout<<"Order by: "<<this->order_by<<endl;
}
