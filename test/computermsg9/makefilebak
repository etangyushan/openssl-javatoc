computermsg.so:cpu.o eth0.o memory.o computermsg.o
	gcc -shared cpu.o eth0.o memory.o computermsg.o -olibcomputermsg.so -g 
%.o:%.c
	gcc -c $< -o $@ -fpic
clean::
	rm -rf *.o *.so computermsg
