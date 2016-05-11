#ifndef KEYWORD_H
#define KEYWORD_H

typedef enum{
  /* 0 */TOK_NULL,
  /* 1 */TOK_DELETE,
  /* 2 */TOK_ORDER,
  /* 3 */TOK_BY,
  /* 4 */TOK_AND,
  /* 4 */TOK_FROM,
  /* 5 */TOK_SELECT,
  /* 6 */TOK_HAVING,
  /* 7 */TOK_TRUNCATE,
  /* 8 */TOK_INSERT,
  /* 9 */TOK_UNION,
  /* 10 */TOK_UPDATE,
  /* 11 */TOK_JOIN,
  /* 12 */TOK_WHERE,
  /* 13 */ TOK_MERGE,
  /* 14 */TOK_IDENTIFIER,
  /* 15 */TOK_ERROR,
  /* 16 */TOK_PASS,
  /* 17 */TOK_TERMINATOR
} sql_token;

typedef enum{
  /* 1 */ TYPE_INT,
  /* 2 */ TYPE_CHAR,
  /* 3 */ TYPE_MONEY,
  /* 4 */ TYPE_BINARY,
  /* 5 */ TYPE_NUMERIC,
  /* 6 */ TYPE_BOOLEAN,
  /* 7 */ TYPE_VARCHAR,
  /* 7 */ TYPE_NONE,
} sql_type;

sql_token sql_keyword(char *str, int length){
  switch (length) {
    case 2:
      if (!strcasecmp(str, "by"))
        return TOK_BY;
      break;
    case 3:
      if (!strcasecmp(str, "and"))
        return TOK_AND;
      break;
    case 4:
      if (!strcasecmp(str, "null"))
        return TOK_NULL;
      if (!strcasecmp(str, "from"))
        return TOK_FROM;
      if (!strcasecmp(str, "join"))
        return TOK_JOIN;
      break;
    case 5:
      if (!strcasecmp(str, "order"))
        return TOK_ORDER;
      if (!strcasecmp(str, "union"))
        return TOK_UNION;
      if (!strcasecmp(str, "where"))
        return TOK_WHERE;
      if (!strcasecmp(str, "merge"))
        return TOK_MERGE;
      break;
    case 6:
      if (!strcasecmp(str, "select"))
        return TOK_SELECT;
      if (!strcasecmp(str, "delete"))
        return TOK_DELETE;
      if (!strcasecmp(str, "insert"))
        return TOK_INSERT;
      if (!strcasecmp(str, "update"))
        return TOK_UPDATE;
      if (!strcasecmp(str, "having"))
        return TOK_HAVING;
      break;
  }
  return TOK_IDENTIFIER;
}

sql_type sql_checktype(char *s, int l){
  switch(l){
    case 3:
      if (strcasecmp(s, "int"))
        return TYPE_INT;
      break;
    case 4:
      if (strcasecmp(s, "char"))
        return TYPE_CHAR;
      break;
    case 5:
      if (strcasecmp(s, "money"))
        return TYPE_MONEY;
      break;
    case 6:
      if (strcasecmp(s, "binary"))
        return TYPE_BINARY;
      break;
    case 7:
      if (strcasecmp(s, "boolean"))
        return TYPE_BOOLEAN;
      if (strcasecmp(s, "numeric"))
        return TYPE_NUMERIC;
      if (strcasecmp(s, "varchar"))
        return TYPE_VARCHAR;
      break;
  }
  return TYPE_NONE;
}

#endif
