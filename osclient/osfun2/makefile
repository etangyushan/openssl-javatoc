#LD=-Wall -lssl -ldl -pthread
LD=-Wall -lssl -ldl -pthread -lcurl -ldetetorfun -L ./
CO=ssl_client.o
LG=-g
all:client
client:$(CO)
	gcc $(CO) $(LD) -o client $(LG)
%.o:%.c
	gcc -c $< -o $@ $(LG)
clean::
	rm -f *.o client
