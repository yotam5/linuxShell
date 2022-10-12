FLAGS = -ansi -Wall -pedantic -g3
TARGET = shell

shell: shell.o
	gcc -g $(FLAGS) shell.o -o shell

shell.o: shell.c
	gcc -c $(FLAGS) shell.c -o shell.o

clean:
	rm -f *.o *~ $(TARGET)

