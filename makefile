
main : main.o wavfile.o dft.o convolution.o
	gcc -g -o main obj/main.o obj/wavfile.o obj/dft.o obj/convolution.o -lm

main.o : main.c main.h wavfile.h
	gcc -c -g main.c -o obj/main.o

wavfile.o : wavfile.c wavfile.h
	gcc -c -g wavfile.c -o obj/wavfile.o

dft.o : dft.c dft.h
	gcc -c -g dft.c -o obj/dft.o

convolution.o : convolution.c convolution.h
	gcc -c -g convolution.c -o obj/convolution.o

clean:
	rm obj/* main