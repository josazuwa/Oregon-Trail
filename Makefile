CC = gcc
CFLAGS = -Wall -std=c99
OUTFILE = HW3
OBJS = HW3.o
SRCS = HW3.c

$(OUTFILE): $(OBJS)
	$(CC) $(CFLAGS) -o $(OUTFILE) $(OBJS)
$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS)
valgrind:
	valgrind --tool=memcheck --leak-check=yes HW3
clean:
	rm -f *~ HW3 *.o *#
