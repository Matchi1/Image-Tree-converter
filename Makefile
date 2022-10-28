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

$(EXEC): bin_file show_file $(LDLIBS)
	$(CC) -o $@ $(LDLIBS_PATH) $(CFLAGS) $(LDFLAGS)

bin_file:
	mkdir -p $(BIN_PATH)

show_file:
	@echo $(LDLIBS)

Main.o: Main.c 

Color.o: Color.c Color.h

Quadtree.o: Quadtree.c Quadtree.h Color.h Pixel.h

Graphic.o: Graphic.c Graphic.h

Compression.o: Compression.c Compression.h Quadtree.h Extension.h BitFile.h

Decompression.o: Decompression.c Decompression.h Quadtree.h Extension.h BitFile.h Color.h 

BitFile.o: BitFile.c BitFile.h  

Input.o: Input.c Input.h Quadtree.h 

Pixel.o: Pixel.c Pixel.h Color.h 

Extension.o: Extension.c Extension.h  

Display_qt.o: Display_qt.c Display_qt.h Quadtree.h 

Calcul.o: Calcul.c Calcul.h Color.h 

Hashtable.o: Hashtable.c Hashtable.h Quadtree.h 

Buttons.o: Buttons.c Buttons.h  

Actions.o: Actions.c Actions.h  

Image.o: Image.c Image.h  

Menu.o: Menu.c Menu.h  

Minimisation.o: Minimisation.c Minimisation.h  

Test.o: Test.c Test.h Quadtree.h Color.h Compression.h Decompression.h Display_qt.h BitFile.h Graphic.h

%.o: %.c
	$(CC) -o $(BIN_PATH)$@ -c $< $(CFLAGS)

clean:
	rm -f tmp.dot
	rm -f compression_tmp.pdf
	rm -f decompression_tmp.pdf
	rm -rf $(BIN_PATH)

mrproper: clean
	rm -f $(EXEC)

zip:
	cd ..; zip -FSr $(current_dir) $(current_dir) -x $(current_dir)/.\*
