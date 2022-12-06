CC = g++
CFLAGS = -g -Wall -ldl -lGL -lOpenGL -lGLU -lglfw
OBJ = glad.c main.o shader.o target.o wave.o

RADAR: $(OBJ)
	$(CC) $(CFLAGS) -o RADAR $(OBJ)

main.o: main.cpp target.h wave.h
	$(CC) -g -c main.cpp
shader.o: shader.cpp shader.h
	$(CC) -g -c shader.cpp
target.o: target.cpp target.h
	$(CC) -g -c target.cpp
wave.o: wave.cpp wave.h
	$(CC) -g -c wave.cpp

clean:
	rm -f *.o RADAR
