LD=-Wall -lssl -ldl -pthread 
CFLAGS=-g
SO=ssl_server.o server_openssl.o server_socket.o server_rdwr.o
all:server
server:$(SO)
	gcc $(SO) $(LD) -o server 
%.o:%.c
	gcc -c $< -o $@ $(CFLAGS)
clean::
	rm -f *.o server
