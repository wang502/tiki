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

  bool order;

  bool to_limit;

  string order_by;

public:
  sqlselect();

  void add_column(sqlcolumn target);

  void add_where(sqlcolumn column, string value);

  void set_table(string t);

  void set_order_by(string o);

  string get_table();

  void print_columns();

  void print_table();

  void print_wheres();

  void print_order_by();

};

#endif
