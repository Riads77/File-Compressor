CC = gcc
CFLAGS = -Wall -Wfatal-errors
LDFLAGS = -l MLV
OBJ = main.o graphique.o Pixel.o Tree.o

quadtee : $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

main.o: main.c graphique.h Pixel.h Tree.h

graphique.o: graphique.c graphique.h Pixel.h Tree.h

Pixel.o: Pixel.c Pixel.h

Tree.o: Tree.c Tree.h graphique.h

clean:
	rm -f *.o *.gch

mrproper: clean
	rm -f quadtee

exec:
	./quadtee


%.o: %.c
	$(CC) -c $^ $(CFLAGS)