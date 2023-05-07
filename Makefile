CC = gcc
CFLAGS = -W -Wall
TARGET = menu
OBJECTS = main.c manager.o product.o
all : $(TARGET)
$(TARGET) : $(OBJECTS)
        $(CC) $(CFLAGS) -o $@ $^
clean:
        rm *.o menu
