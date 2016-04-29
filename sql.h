#ifndef SQL_H
#define SQL_H

#include <cstring>
#include <vector>

using namespace std;

struct sqlstring {
  string s;
};

struct sqlcolumn{
  sqlstring name;
  bool is_primary;
  sqlcolumn(sqlstring newname, bool is): name(newname), is_primary(is){};
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
