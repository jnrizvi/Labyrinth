gameEngine: gameEngine.o handleEvents.o physics2d.o
	gcc -lSDL2 -lSDL2_mixer -lSDL2_image gameEngine.o handleEvents.o physics2d.o -o Game.app

gameEngine.o : handleEvents.h physics2d.h
	gcc -c gameEngine.c 

handleEvents.o : handleEvents.h
	gcc -c handleEvents.c

physics2D.o : physics2d.h
	gcc -c physics2d.c

clean:
	rm -f *.o