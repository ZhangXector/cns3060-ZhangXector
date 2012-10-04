all: du1

du1: du1.c
	gcc -g du1.c -o du1

debug: clean du1
	gdb du1 

clean:
	rm -f du1

run: clean du1
	./du1 
