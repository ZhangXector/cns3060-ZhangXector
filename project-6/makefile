all: clean parta partb partc partd

parta: parta.c
	gcc parta.c -o parta

partb: partb.c
	gcc partb.c -o partb

partc: partc.c
	gcc partc.c -o partc

partd: partd.c
	gcc partd.c -o partd

run: clean parta partb partc partd
	./parta
	./partb
	./partc
	./partd

clean:
	rm -f parta partb partc partd
