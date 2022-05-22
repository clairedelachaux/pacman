prog2 : main.o pacman.o env.o
	gcc -o prog2 main.o pacman.o env.o


env.o : env.c env.h
	gcc -c env.c

pacman.o : pacman.c pacman.h
	gcc -c -Wall -Werror -Wfatal-errors pacman.c

main.o : main.c
	gcc -c -Wall -Werror -Wfatal-errors main.c

clean :
	rm -f prog2 main.o pacman.o env.o