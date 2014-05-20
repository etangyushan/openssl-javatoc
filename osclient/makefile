LD=-Wall -lssl -ldl -pthread -lcurl -L ./
CO1=rate_cpu.o rate_memory.o rate_net.o rate_disk.o computerstate.o
CO2=client_openssl.o client_socket.o client_rdwr.o
CO3=curlhttps.o seekkey.o judgeftype.o my_syslog.o
CO=$(CO1) $(CO2) $(CO3)
all:libdetetorfun.so
libdetetorfun.so:$(CO)
	gcc -shared $(CO) -olibdetetorfun.so $(LD)
%.o:%.c
	gcc -c $< -o $@ -fpic
clean::
	rm -f *.o libdetetorfun.so
