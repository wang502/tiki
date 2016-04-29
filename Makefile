SQLSELECT = lexer_test.o sqlselect.o
CC = g++
CFLAGS = -c

select : $(SQLSELECT)
	$(CC) $(SQLSELECT) -o main

lexer_test.o: lexer_test.cpp
	$(CC) $(CFLAGS) lexer_test.cpp

sqlselect.o: sqlselect.cpp sqlselect.h
	$(CC) $(CFLAGS) sqlselect.cpp

clean:
	rm *.o main
