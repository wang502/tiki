#include <cstring>
using namespace std;

struct sqlstring {
  string s;
}

struct sqlcolumn{
  string name;
  bool isPrimary;
}

struct sqlwhere{
  sqlcolumn column;
  sqlstring value;
}

struct sqltable{
  sqlstring name;
  vector<sqlcolumn> columns;
  sqlstring primary_key;
}
