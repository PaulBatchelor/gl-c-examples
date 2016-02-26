LIBS= -lGL -lGLU -lglut -lm -lpthread -lcairo

OBJ=lodepng.o

BIN=simple.bin bitmap.bin zoom.bin cairo.bin circle.bin texture.bin\
	cairo_tex.bin gl_circ.bin font.bin grid.bin triangle.bin blend

default: $(BIN) $(OBJ)

blend: blend.c lodepng.o
	$(CC) $(LIBS) blend.c lodepng.o -o blend

example_decode: example_decode.c lodepng.o
	$(CC) $< -o $@ lodepng.o

%.o: %.c
	$(CC) -c $< -o $@

%.bin: %.c
	$(CC) $(LIBS) $^ -o $@

clean:
	rm -rf $(BIN) $(OBJ) blend
