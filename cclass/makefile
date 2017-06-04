CC=gcc
CFLAGS=-Wall -s

test: main.o cclass.o cclsString.o err.o
	$(CC) $^ -o $@.exe $(CFLAGS)

main.o: main.c
	$(CC) -c $< -o $@ $(CFLAGS)
	
err.o: err.c err.h
	$(CC) -c $< -o $@ $(CFLAGS)
	
cclass.o: cclass.c cclass.h
	$(CC) -c $< -o $@ $(CFLAGS)
	
cclsString.o: cclsString.c cclsString.h
	$(CC) -c $< -o $@ $(CFLAGS)
	
clean:
	rm *.o
	rm *.exe