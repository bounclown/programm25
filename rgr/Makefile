CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
LDFLAGS = -L. -lfreq

SRC = main.c
OBJS = main.o
LIBSRC = freq.c
LIBOBJS = freq.o

TARGET = analyzer
LIB = libfreq.so

all: $(TARGET)

$(TARGET): $(OBJS) $(LIB)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

$(LIB): $(LIBOBJS)
	$(CC) -shared -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS) $(LIBOBJS) $(LIB)