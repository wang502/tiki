#ifndef SQLCREATE_H
#define SQLCREATE_H
#include "sql.h"
#include <vector>

using namespace std;

class sqlcreate{
  // table name
  string name;

  // tatble's columns
  vector<sqlcolumn> columns;

  // primary column
  sqlcolumn primary;

public:
    sqlcreate();

    void set_name(string n);

    void add_column(sqlcolumn c);

    void set_primary(sqlcolumn c);

    string get_name();

    vector<sqlcolumn> get_columns();

    sqlcolumn void get_primary();

    void print_columns();
};

#endif
