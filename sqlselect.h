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

  void add_where(sqlcolumn column, string value);

  void set_table(string t);

  string get_table();

  void print_columns();

  void print_table();

  void print_wheres();

};
#endif
