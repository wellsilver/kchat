args = -lm

all:
	mkdir -p out
	g++ src/main.cpp -o out/main $(args) -l ncurses
	./out/main