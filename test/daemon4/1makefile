mydaemon.so:crt_que.o daemon.o dir_file.o
	gcc -shared crt_que.o daemon.o dir_file.o -olibmydaemon.so
%.o:%.c
	$(CC) -c $< -o $@ -fpic
clean::
	rm -f *.o *.so 

