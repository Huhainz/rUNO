CC = g++
CFLAGS = -W -Wall -Werror
TARGET = UNO
SRC= uno-main.cpp main.cpp
HEADERS= uno-main.h

all: $(TARGET)

$(TARGET): $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean: rm -f $(TARGET)