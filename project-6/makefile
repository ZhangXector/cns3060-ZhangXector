all: clean parta partb partc partd

parta: clean parta.c
	gcc parta.c -o parta

partb: clean partb.c
	gcc partb.c -o partb

partc: clean partc.c
	gcc partc.c -o partc

partd: clean partd.c
	gcc partd.c -o partd

run: clean parta partb partc partd
	./parta
	./partb
	./partc
	./partd

clean:
	rm -f parta partb partc partd
