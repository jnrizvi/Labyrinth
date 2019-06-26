gameEngine: gameEngine.o handleEvents.o physics2d.o mapEditor.o
	gcc -lSDL2 -lSDL2_mixer -lSDL2_image gameEngine.o handleEvents.o physics2d.o mapEditor.o -o Game.app

gameEngine.o : handleEvents.h physics2d.h
	gcc -c gameEngine.c 

handleEvents.o : handleEvents.h
	gcc -c handleEvents.c

physics2D.o : physics2d.h
	gcc -c physics2d.c

mapEditor.o : mapEditor.h
	gcc -c mapEditor.c

clean:
	rm -f *.o