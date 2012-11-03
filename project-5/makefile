all: more1

more1: more1.c
	gcc more1.c -o more1

run1: clean more1
	./more1

run2: clean more1
	./more1 yankee.txt

debug: clean more1.c
	gcc -g more1.c -o more1
	gdb more1

clean:
	rm -f more1
