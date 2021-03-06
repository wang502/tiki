#ifndef SQL_H
#define SQL_H

#include <cstring>
#include <vector>
#include "keyword.h"

using namespace std;

struct sqlidentifier{
  int offset;
  int length;
  sqlidentifier(int o, int l):offset(o), length(l){};
};

struct sqlstate{
  char *buffer;
  int offset;
  sqlidentifier identifier;
  sqlstate(char *c, int o, sqlidentifier i):buffer(c), offset(o), identifier(i){};
};

struct sqlstring {
  string s;
};

struct sqlcolumn{
  string name;
  sql_type type;
  sqlcolumn(string newname): name(newname){}; //is_primary(is){};
};

struct sqlwhere{
  sqlcolumn column;
  string value;
  sqlwhere(sqlcolumn newcolumn, string newvalue):column(newcolumn), value(newvalue){};
};

struct sqltable{
  sqlstring name;
  vector<sqlcolumn> columns;
  sqlstring primary_key;
};

#endif
