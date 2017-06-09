all:
	gcc -w src/* -o nsh
	./test.sh

clean:
	rm nsh
