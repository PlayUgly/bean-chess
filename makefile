objects = bean-chess.o moves.o

all:	bean-chess.exe

bean-chess.exe:	$(objects)
			gcc -o bean-chess.exe $(objects)

bean-chess.o:

moves.o: moves.h

clean:
		rm $(objects) bean-chess.exe
