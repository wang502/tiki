#ifndef SQLSELECT_H
#define SQLSELECT_H
#include "sql.h"
#include <vector>
using namespace std;

class sqlselect{
  vector<sqlstring> targets;
  vector<sqlwhere> wheres;

public:
  sqlselect();

  set_target(sqlstring target);

  add_where(sqlcolumn column, sqlstring value);

  
};
#endif
