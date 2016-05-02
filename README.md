# Tiki

This is a SQL parser implemented in C++, using lexical analysis.

Inspired by article [Following a Select Statement Through Postgres Internals](http://patshaughnessy.net/2014/10/13/following-a-select-statement-through-postgres-internals), which talks about how PostgreSQL parser in works.

Still under development

## Why

This repo is for the purpose of learning and demonstrating the concept of lexical analysis.

## Testing

Test the SELECT statement parser:

    $make select
    $./main
