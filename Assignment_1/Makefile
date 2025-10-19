CC = gcc
CFLAGS = -I. -g -w
DEPS = pa1.h
OBJ = pattern_checker.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

pattern_finder: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean: //clean up the object files and the executable
	rm -f *.o pattern_finder 
