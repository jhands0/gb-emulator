CC = g++
CFLAGS = -Wall -Wextra -Wpedantic -std=c99 -Iinclude -D_GNU_SOURCE
LDFLAGS = -lm
SDL3 = -shared -fPIC -lSDL3
SRCDIR = src
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES: .cpp=.o)
TARGET = build/out

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(TARGET) $(SDL3)

release: CFLAGS += -O3 -flto -march=native
release: LDFLAGS += -flto
release: clean $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< .o $@

clean:
	rm -f $(SRCDIR)/*.o $(TARGET)