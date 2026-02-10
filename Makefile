all:
	gcc -Wall -g ./src/*.c -o ./out/main -lSDL3

run: all
	./out/main

clean:
	rm -f main
