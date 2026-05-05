CC=gcc

CFLAGS=-W -Wall -std=gnu99 -O2 -pedantic `pkg-config --cflags MLV`
LDFLAGS=-lm `pkg-config --libs-only-other --libs-only-L MLV`
LDLIBS=`pkg-config --libs-only-l MLV`

TARGET=main
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

GENERATOR_TARGET=generator
GENERATOR_SRC=$(wildcard create/*.c)
GENERATOR_OBJ=$(GENERATOR_SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS)

$(GENERATOR_TARGET) : $(GENERATOR_OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)


%.o: %.c
	$(CC) -c $< $(CFLAGS) -o $@


clean:
	rm -rf $(OBJ) $(TARGET) $(GENERATOR_TARGET) $(GENERATOR_OBJ) *.txt results