CC = g++
CFLAGS = -Wall -ggdb
INCLUDE_DIR_SDL = -ISDL2
SDL_EXT = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
OBJ_FILES = ./obj/Vec2.o ./obj/Projectile.o ./obj/Arme.o ./obj/Personnage.o ./obj/Jeu.o ./obj/Terrain.o ./obj/winTxt.o ./obj/sdlj.o ./obj/Ennemi.o

all: ./bin/sdlj ./bin/texte ./bin/testTer ./bin/testProj ./bin/testPers ./bin/testJeu ./bin/testEnn ./bin/testArme

./bin/sdlj: $(OBJ_FILES) ./obj/sdljmain.o
	$(CC) -g $(OBJ_FILES) ./obj/sdljmain.o -o ./bin/sdlj $(SDL_EXT)

./bin/texte: $(OBJ_FILES) ./obj/maintxt.o
	$(CC) -g $(OBJ_FILES) ./obj/maintxt.o -o ./bin/texte $(SDL_EXT)

./obj/sdljmain.o: ./src/sdl/sdljmain.cpp ./src/core/Jeu.h ./src/core/Personnage.h ./src/txt/winTxt.h
	$(CC) $(CFLAGS) $(INCLUDE_DIR_SDL) -c ./src/sdl/sdljmain.cpp -o ./obj/sdljmain.o

./bin/testTer: $(OBJ_FILES) ./obj/mainTestTer.o
	$(CC) $(OBJ_FILES) ./obj/mainTestTer.o -o ./bin/testTer $(SDL_EXT)

./bin/testProj: $(OBJ_FILES) ./obj/mainTestProj.o
	$(CC) $(OBJ_FILES) ./obj/mainTestProj.o -o ./bin/testProj $(SDL_EXT)

./bin/testPers: $(OBJ_FILES) ./obj/mainTestPers.o
	$(CC) $(OBJ_FILES) ./obj/mainTestPers.o -o ./bin/testPers $(SDL_EXT)

./bin/testJeu: $(OBJ_FILES) ./obj/mainTestJeu.o
	$(CC) $(OBJ_FILES) ./obj/mainTestJeu.o -o ./bin/testJeu $(SDL_EXT)

./bin/testEnn: $(OBJ_FILES) ./obj/mainTestEnn.o
	$(CC) $(OBJ_FILES) ./obj/mainTestEnn.o -o ./bin/testEnn $(SDL_EXT)

./bin/testArme: $(OBJ_FILES) ./obj/mainTestArme.o
	$(CC) $(OBJ_FILES) ./obj/mainTestArme.o -o ./bin/testArme $(SDL_EXT)

./obj/sdlj.o: ./src/sdl/sdlj.cpp ./src/sdl/sdlj.h ./src/core/Jeu.h
	$(CC) $(CFLAGS) $(INCLUDE_DIR_SDL) -c ./src/sdl/sdlj.cpp -o ./obj/sdlj.o

./obj/maintxt.o: ./src/txt/maintxt.cpp ./src/core/Jeu.h  ./src/core/Personnage.h ./src/txt/winTxt.h
	$(CC) $(CFLAGS) $(INCLUDE_DIR_SDL) -c ./src/txt/maintxt.cpp -o ./obj/maintxt.o

./obj/winTxt.o: ./src/txt/winTxt.cpp ./src/txt/winTxt.h
	$(CC) $(CFLAGS) $(INCLUDE_DIR_SDL) -c ./src/txt/winTxt.cpp -o ./obj/winTxt.o

./obj/mainTestJeu.o: ./src/tests/mainTestJeu.cpp ./src/core/Jeu.h
	$(CC) $(CFLAGS) $(INCLUDE_DIR_SDL) -c ./src/tests/mainTestJeu.cpp -o ./obj/mainTestJeu.o

./obj/Jeu.o: ./src/core/Jeu.cpp ./src/core/Jeu.h ./src/core/Terrain.h ./src/core/Personnage.h
	$(CC) $(CFLAGS) $(INCLUDE_DIR_SDL) -c ./src/core/Jeu.cpp -o ./obj/Jeu.o

./obj/mainTestPers.o: ./src/tests/mainTestPers.cpp ./src/core/Personnage.h
	$(CC) $(CFLAGS) $(INCLUDE_DIR_SDL) -c ./src/tests/mainTestPers.cpp -o ./obj/mainTestPers.o

./obj/Personnage.o: ./src/core/Personnage.cpp ./src/core/Personnage.h ./src/core/Arme.h ./src/core/Terrain.h
	$(CC) $(CFLAGS) $(INCLUDE_DIR_SDL) -c ./src/core/Personnage.cpp -o  ./obj/Personnage.o

./obj/mainTestEnn.o: ./src/tests/mainTestEnn.cpp ./src/core/Ennemi.h
	$(CC) $(CFLAGS) $(INCLUDE_DIR_SDL) -c ./src/tests/mainTestEnn.cpp -o ./obj/mainTestEnn.o

./obj/Ennemi.o: ./src/core/Ennemi.cpp ./src/core/Ennemi.h ./src/core/Vec2.h ./src/core/Terrain.h
	$(CC) $(CFLAGS) $(INCLUDE_DIR_SDL) -c ./src/core/Ennemi.cpp -o  ./obj/Ennemi.o

./obj/mainTestTer.o: ./src/tests/mainTestTer.cpp ./src/core/Terrain.h
	$(CC) $(CFLAGS) $(INCLUDE_DIR_SDL) -c ./src/tests/mainTestTer.cpp -o ./obj/mainTestTer.o

./obj/Terrain.o: ./src/core/Terrain.cpp ./src/core/Terrain.h
	$(CC) $(CFLAGS) $(INCLUDE_DIR_SDL) -c ./src/core/Terrain.cpp -o ./obj/Terrain.o

./obj/mainTestArme.o: ./src/tests/mainTestArme.cpp ./src/core/Arme.h
	$(CC) $(CFLAGS) $(INCLUDE_DIR_SDL) -c ./src/tests/mainTestArme.cpp -o ./obj/mainTestArme.o

./obj/Arme.o: ./src/core/Arme.cpp ./src/core/Arme.h ./src/core/Projectile.h
	$(CC) $(CFLAGS) $(INCLUDE_DIR_SDL) -c ./src/core/Arme.cpp -o ./obj/Arme.o

./obj/mainTestProj.o: ./src/tests/mainTestProj.cpp ./src/core/Projectile.h
	$(CC) $(CFLAGS) $(INCLUDE_DIR_SDL) -c ./src/tests/mainTestProj.cpp -o ./obj/mainTestProj.o

./obj/Projectile.o: ./src/core/Projectile.cpp ./src/core/Projectile.h ./src/core/Vec2.h
	$(CC) $(CFLAGS) $(INCLUDE_DIR_SDL) -c ./src/core/Projectile.cpp -o ./obj/Projectile.o

./obj/Vec2.o: ./src/core/Vec2.h ./src/core/Vec2.cpp 
	$(CC) $(CFLAGS) $(INCLUDE_DIR_SDL) -c ./src/core/Vec2.cpp -o ./obj/Vec2.o

clean: 
	rm ./obj/*.o && rm ./bin/* 