CC = gcc

SRC = src/main.c src/linkedlist.c src/program.c src/ui.c 

TARGET = fintrack

all: $(TARGET) clean dist

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)
	chmod u+x $(TARGET)
	mkdir -p release
	mv $(TARGET) ./release/

clean:
	rm -f *.o

dist: clean
	mkdir -p dist
	zip dist/fintrack.zip src/*.c include/*.h logs/*.txt report/*.pdf Makefile

