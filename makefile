objects = bean-chess.o moves.o bits.o

all:	bean-chess.exe

bean-chess.exe:	$(objects)
		gcc -o bean-chess.exe $(objects)

bean-chess.o:

moves.o: moves.h

bits.o: bits.h

clean:
		rm $(objects) bean-chess.exe
		rm temp
