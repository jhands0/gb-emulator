CC = g++
CFLAGS = -Wall -Wextra -Wpedantic -std=c99 -Iinclude -Iruntime_x86
LDFLAGS = -lm -lSDL3
SRCDIR = src
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES: .cpp=.o)
TARGET = build/out

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(TARGET)

release: CFLAGS += -O3 -flto -march=native
release: LDFLAGS += -flto
release: clean $(TARGET)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< .o $@

clean:
	rm -f $(SRCDIR)/*.o $(TARGET)
