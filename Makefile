#CFLAGS = -g -Wall -Wextra -pedantic -Wno-unused-parameter
CFLAGS = -g -Wno-unused-parameter
CC = gcc

PROGRAMS =   tests_ecosys ecosys tests2_ecosys

.PHONY:	all clean #Commande 'make' rettrouve donc 'all' en premier

all: $(PROGRAMS)

tests_ecosys: main_tests.o ecosys.o
	$(CC) -o $@ $(CFLAGS) $^

ecosys: main_ecosys.o ecosys.o
	$(CC) -o $@ $(CFLAGS) $^

tests2_ecosys: main_tests2.o ecosys.o
	$(CC) -o $@ $(CFLAGS) $^

ecosys.o: ecosys.c
	gcc $(CFLAGS) -c ecosys.c

main_tests.o: main_tests.c
	gcc $(CFLAGS) -c main_tests.c

main_ecosys.o: main_ecosys.c 
	gcc $(CFLAGS) -c main_ecosys.c

main_tests2.o: main_tests2.c 
	gcc $(CFLAGS) -c main_tests2.c


#Ou plus simplement
#%.o:%.c %.h
#	$(CC)  $(GCC_FLAGS) -c  $<

graph: evolution.gnu Evol_Pop.txt
	gnuplot evolution.gnu

clean:
	rm -f *.o *.txt graphe.gnu *~ $(PROGRAMS)
