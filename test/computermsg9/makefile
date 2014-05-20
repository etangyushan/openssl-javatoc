GDB=-g
OO=test.o cpu.o eth0.o memory.o computermsg.o
computermsg:$(OO)
	gcc $(OO) -o computermsg $(GDB) 
%.o:%.c
	gcc -c $< -o $@ $(GDB)
clean::
	rm -rf *.o computermsg
