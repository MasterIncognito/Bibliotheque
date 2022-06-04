all: exec

main.o: main.c function.h file.h user.h book.h
	gcc -c $< -o $@

function.o: function.c function.h
	gcc -c $< -o $@

file.o: file.c file.h
	gcc -c $< -o $@

user.o: user.c user.h
	gcc -c $< -o $@

book.o: book.c book.h
	gcc -c $< -o $@

exec: main.o function.o file.o user.o book.o
	gcc $^ -o $@
