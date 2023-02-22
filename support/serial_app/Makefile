TARGET=serapp
CC=mips64el-linux-gnuabi64-gcc
CFLAGS=-I.
DEPS = 
OBJ = main.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	
clean: 
	rm *.o $(TARGET)
