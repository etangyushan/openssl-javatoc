OO=crt_que.o daemon.o dir_file.o main.o
CC=gcc
LD=-Wall -g
all:daemon test
daemon:$(OO)
	$(CC) $(LD) $(OO) -o daemon
%.o:%.c
	$(CC) -c $< -o $@
test:$(OO)
	$(CC) $(LD) $(OO) -o test
clean::
	rm -f *.o daemon test 

