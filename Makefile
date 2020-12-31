CC = gcc
CFLAGS = -pedantic -Wall -ansi
LDFLAGS = -lMLV -lm -O2
SRC_PATH = src/
BIN_PATH = bin/
LDLIBS = $(subst .c,.o,$(notdir $(wildcard $(SRC_PATH)*)))
LDLIBS_PATH = $(addprefix $(BIN_PATH),$(LDLIBS))
EXEC = Main
current_dir=$(notdir $(shell pwd))

vpath %.o bin
vpath %.c src
vpath %.h include

$(EXEC): $(LDLIBS)
	$(CC) -o $@ $(LDLIBS_PATH) $(CFLAGS) $(LDFLAGS)

Main.o: Main.c 
	$(CC) -o $(BIN_PATH)$@ -c $< $(CFLAGS)

Color.o: Color.c Color.h
	$(CC) -o $(BIN_PATH)$@ -c $< $(CFLAGS)

Quadtree.o: Quadtree.c Quadtree.h Color.h Pixel.h
	$(CC) -o $(BIN_PATH)$@ -c $< $(CFLAGS)

Graphic.o: Graphic.c Graphic.h
	$(CC) -o $(BIN_PATH)$@ -c $< $(CFLAGS)

Test.o: Test.c Test.h Quadtree.h Color.h Compression.h Decompression.h Display_qt.h BitFile.h Graphic.h
	$(CC) -o $(BIN_PATH)$@ -c $< $(CFLAGS)

Compression.o: Compression.c Compression.h Quadtree.h Extension.h BitFile.h
	$(CC) -o $(BIN_PATH)$@ -c $< $(CFLAGS)

Decompression.o: Decompression.c Decompression.h Quadtree.h Extension.h BitFile.h Color.h 
	$(CC) -o $(BIN_PATH)$@ -c $< $(CFLAGS)

BitFile.o: BitFile.c BitFile.h  
	$(CC) -o $(BIN_PATH)$@ -c $< $(CFLAGS)

Menu.o: Menu.c Menu.h  
	$(CC) -o $(BIN_PATH)$@ -c $< $(CFLAGS)

Input_img.o: Input_img.c Input_img.h Quadtree.h 
	$(CC) -o $(BIN_PATH)$@ -c $< $(CFLAGS)
	
Pixel.o: Pixel.c Pixel.h Color.h 
	$(CC) -o $(BIN_PATH)$@ -c $< $(CFLAGS)

Extension.o: Extension.c Extension.h  
	$(CC) -o $(BIN_PATH)$@ -c $< $(CFLAGS)

Display_qt.o: Display_qt.c Display_qt.h Quadtree.h 
	$(CC) -o $(BIN_PATH)$@ -c $< $(CFLAGS)

Calcul.o: Calcul.c Calcul.h Color.h 
	$(CC) -o $(BIN_PATH)$@ -c $< $(CFLAGS)

Hashtable.o: Hashtable.c Hashtable.h Quadtree.h 
	$(CC) -o $(BIN_PATH)$@ -c $< $(CFLAGS)

clean:
	rm -f tmp.*
	rm -f $(BIN_PATH)*.o

mrproper: clean
	rm -f $(EXEC)

zip:
	cd ..; zip -FSr $(current_dir) $(current_dir) -x $(current_dir)/.\*
