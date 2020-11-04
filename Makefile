CC = gcc
CFLAGS = -pedantic -Wall -ansi
LDFLAGS = -lMLV -lm
SRC_PATH = src/
BIN_PATH = bin/
LDLIBS = $(subst .c,.o,$(notdir $(wildcard $(SRC_PATH)*)))
LDLIBS_PATH = $(addprefix $(BIN_PATH),$(LDLIBS))
EXEC = Main

vpath %.o bin
vpath %.c src
vpath %.h include

$(EXEC): $(LDLIBS)
	$(CC) -o $@ $(LDLIBS_PATH) $(CFLAGS) $(LDFLAGS)

Main.o: Main.c 
	$(CC) -o $(BIN_PATH)$@ -c $< $(CFLAGS)

Color.o: Color.c Color.h
	$(CC) -o $(BIN_PATH)$@ -c $< $(CFLAGS)

Quadtree.o: Quadtree.c Quadtree.h Color.h
	$(CC) -o $(BIN_PATH)$@ -c $< $(CFLAGS)

Graphic.o: Graphic.c Graphic.h
	$(CC) -o $(BIN_PATH)$@ -c $< $(CFLAGS)

Test.o: Test.c Test.h Quadtree.h Graphic.h Color.h
	$(CC) -o $(BIN_PATH)$@ -c $< $(CFLAGS)

Compression.o: Compression.c Compression.h Quadtree.h 
	$(CC) -o $(BIN_PATH)$@ -c $< $(CFLAGS)

Decompression.o: Decompression.c Decompression.h  
	$(CC) -o $(BIN_PATH)$@ -c $< $(CFLAGS)

BitFile.o: BitFile.c BitFile.h  
	$(CC) -o $(BIN_PATH)$@ -c $< $(CFLAGS)

Menu.o: Menu.c Menu.h  
	$(CC) -o $(BIN_PATH)$@ -c $< $(CFLAGS)

clean:
	rm -f $(BIN_PATH)*.o

mrproper: clean
	rm -f $(EXEC)
