#ifndef SQLSELECT_H
#define SQLSELECT_H

#include "sql.h"
#include <vector>

using namespace std;

class sqlselect{
  bool select_all;

  vector<sqlcolumn> targets;

  vector<sqlwhere> wheres;

  sqltable from;

  bool to_sort;

  bool to_limit;

public:
  sqlselect();

  void add_target(sqlcolumn target);

  void add_where(sqlcolumn column, sqlstring value);

};
#endif
