LIBS= -lGL -lGLU -lglut -lm -lpthread -lcairo

BIN=simple.bin bitmap.bin zoom.bin cairo.bin

default: $(BIN)

%.bin: %.c
	$(CC) $(LIBS) $^ -o $@

clean:
	rm -rf $(BIN)
