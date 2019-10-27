
main : main.o wavfile.o dft.o
	gcc -g -o main obj/main.o obj/wavfile.o obj/dft.o -lm

main.o : main.c main.h wavfile.h
	gcc -c -g main.c -o obj/main.o

wavfile.o : wavfile.c wavfile.h
	gcc -c -g wavfile.c -o obj/wavfile.o

dft.o : dft.c dft.h
	gcc -c -g dft.c -o obj/dft.o

clean:
	rm obj/* main