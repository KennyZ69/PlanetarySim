CFLAGS = -Wall -O2 -Wextra
LDFLAGS = -lSDL2 -lm -lGL -lGLU

SRC = $(wildcard src/*.c) main.c
OBJ = $(patsubst %.c,%.o,$(SRC))
OUT = planets

all: $(OUT)

$(OUT): $(OBJ)
	gcc $(OBJ) -o $(OUT) $(LDFLAGS)

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OUT) $(OBJ)

run:
	./$(OUT)
