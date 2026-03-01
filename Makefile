CC=gcc

CFLAGS=-W -Wall -std=gnu99 -O2 -pedantic
LDFLAGS=-lm

TARGET=main
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)


%.o: %.c
	$(CC) -c $< $(CFLAGS) -o $@


clean:
	rm -f $(OBJ) $(TARGET) $(DOBJ) $(DTARGET)