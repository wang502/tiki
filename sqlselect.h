#ifndef SQLSELECT_H
#define SQLSELECT_H

#include "sql.h"
#include <vector>

using namespace std;

class sqlselect{
  bool select_all;

  vector<sqlcolumn> columns;

  vector<sqlwhere> wheres;

  string table;

  bool to_sort;

  bool to_limit;

public:
  sqlselect();

  void add_column(sqlcolumn target);

  void add_where(sqlcolumn column, sqlstring value);

  void set_table(string t);

};
#endif
