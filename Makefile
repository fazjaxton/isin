TARGET:=isin
SOURCES:=isin.c
CFLAGS:=-Wall -g -O2

OBJECTS:=$(SOURCES:%.c=%.o)

$(TARGET): $(OBJECTS)
	gcc -o $(TARGET) $^

%.o: %.c
	gcc $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(OBJECTS)
