CFLAGS = -I include -L lib -l SDL2-2.0.0 -O2 -Wall -Wextra -pedantic -Wfloat-equal -ansi
INCS = neillsdl2.h
TARGET = blocks
SOURCES =  $(TARGET).c neillsdl2.c 
CC = gcc


all: $(TARGET)

$(TARGET): $(SOURCES) $(INCS)
	$(CC) $(SOURCES) -o $(TARGET) $(CFLAGS)

clean:
	rm -f $(TARGET)

run: all
	./$(TARGET) 
