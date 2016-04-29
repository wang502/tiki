#ifndef KEYWORD_H
#define KEYWORD_H

typedef enum{
  TOK_NULL, TOK_DELETE, TOK_ORDER, TOK_BY,
  TOK_FROM, TOK_SELECT, TOK_HAVING, TOK_TRUNCATE,
  TOK_INSERT, TOK_UNION, TOK_UPDATE, TOK_JOIN, TOK_WHERE,
  TOK_MERGE, TOK_DEFAULT
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
  return TOK_DEFAULT;
}
#endif
