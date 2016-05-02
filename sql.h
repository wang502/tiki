#ifndef SQL_H
#define SQL_H

#include <cstring>
#include <vector>

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
  //bool is_primary;
  sqlcolumn(string newname): name(newname){}; //is_primary(is){};
};

struct sqlwhere{
  sqlcolumn column;
  sqlstring value;
  sqlwhere(sqlcolumn newcolumn, sqlstring newvalue):column(newcolumn), value(newvalue){};
};

struct sqltable{
  sqlstring name;
  vector<sqlcolumn> columns;
  sqlstring primary_key;
};

#endif
