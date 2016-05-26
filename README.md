# Tiki

This is a SQL parser implemented in C++, using recursive descent parsing.

Inspired by article [Following a Select Statement Through Postgres Internals](http://patshaughnessy.net/2014/10/13/following-a-select-statement-through-postgres-internals), which talks about how PostgreSQL parser in works.

Still under development

## Why

This repo is for the purpose of learning and demonstrating the concept of a common parsing concept -- recursive descent parsing.

## Testing

Test the SELECT statement parser:
```
  $make select
  $./main
```

## Example

Suppose the input query is
```SQL
  select users.username from users;
```
Then the parser will parsing the query string return a structure like this
```CPP
  char buffer[] = select users.username from users;
  sqlselect sql;
  token = lexer_select(buffer, &sql);
```
sqlselect class has members:
- select_all
- columns
- wheres
- table
- order
- to_limit
- order_by
