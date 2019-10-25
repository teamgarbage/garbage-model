
main : main.o wavfile.o
	gcc -g -o main obj/main.o obj/wavfile.o

main.o : main.c main.h wavfile.h
	gcc -c -g main.c -o obj/main.o

wavfile.o : wavfile.c wavfile.h
	gcc -c -g wavfile.c -o obj/wavfile.o

clean:
	rm obj/* main