gameEngine: gameEngine.o handleEvents.o physics2d.o mapEditor.o
	gcc -Wall -lSDL2 -lSDL2_mixer -lSDL2_image gameEngine.o handleEvents.o physics2d.o mapEditor.o -o Game.app

gameEngine.o :
	gcc -c gameEngine.c 

handleEvents.o :
	gcc -c handleEvents.c

physics2D.o :
	gcc -c physics2d.c

mapEditor.o :
	gcc -c mapEditor.c

clean:
	rm -f *.o