#include "sqlcreate.h"

sqlcreate::sqlcreate(){}

void set_name(string n){
  this->name = n;
}

void sqlcreate::add_column(sqlcolumn c){
  this->columns.push_back(c);
}

void sqlcreate::set_primary(sqlcolumn c){
  this->primary = c;
}

string sqlcreate::get_name(){
  return this->name;
}

vector<sqlcolumn> sqlcreate::get_columns(){
  return this->columns;
}

sqlcolumn sqlcreate::get_primary(){
  return this->primary;
}

void sqlcreate::print_columns(){
  for (int i=0; i<this->columns.size();i++){
    cout<<"column name: "<<this->columns[i].name<<" Type: "<<this->columns[i].sql_type;
    if (this->primary.name == this->columns[i].name){
      cout<<" (primary key)"<<endl;
    }
  }
}
