all:
	gcc -w *.c *.h -o nsh

clean:
	rm nsh
