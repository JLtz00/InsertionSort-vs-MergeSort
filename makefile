CC = gcc
CFLAGS = -O2 -Wall -Wextra -std=c11 -pedantic

programa: experimento.c
	$(CC) $(CFLAGS) experimento.c -o experimento

run: experimento
	./experimento > resultados.dat

plot: resultados.dat
	gnuplot experimento.plt
	xdg-open experimento.png

clean:
	rm -f experimento resultados.dat experimento.png
