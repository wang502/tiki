#ifndef KEYWORD_H
#define KEYWORD_H

typedef enum{
  /* 0 */TOK_NULL,
  /* 1 */TOK_DELETE,
  /* 2 */TOK_ORDER,
  /* 3 */TOK_BY,
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
  /* 16 */TOK_PASS
} sql_token;



sql_token sql_keyword(char *str, int length){
  switch (length) {
    case 2:
      if (!strcasecmp(str, "by"))
        return TOK_BY;
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
#endif
