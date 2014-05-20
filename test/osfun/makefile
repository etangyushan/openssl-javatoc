#LD=-Wall -lssl -ldl -pthread
LD=-Wall -lssl -ldl -pthread -lcurl
CO1=rate_cpu.o rate_memory.o rate_net.o rate_disk.o computerstate.o
CO2=ssl_client.o  client_openssl.o client_socket.o client_rdwr.o  
CO3=curlhttps.o seekkey.o judgeftype.o my_syslog.o
CO=$(CO1) $(CO2) $(CO3)
LG=-g
all:detetorfun.so
detetorfun.so:$(CO)
	gcc -shared $(CO) $(LD) -olibdetetorfun.so $(LG)
%.o:%.c
	gcc -c $< -o $@ $(LG) -fpic
clean::
	rm -f *.o client
