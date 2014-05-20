OO=crt_que.o daemon.o dir_file.o main.o
OT=crt_que.o daemon.o dir_file.o test.o
CC=gcc
LD=-Wall -g
all:mydaemon test
mydaemon:$(OO)
	$(CC) $(LD) $(OO) -o mydaemon
%.o:%.c
	$(CC) -c $< -o $@
test:$(OT)
	$(CC) $(LD) $(OT) -o test
%.o:%.c
	$(CC) -c $< -o $@
clean::
	rm -f *.o daemon test 

