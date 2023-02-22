TARGET=app
CC=mips64el-linux-gnuabi64-gcc
CFLAGS=-I.
DEPS = i2c.h
OBJ = i2c.o appi2c.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	
clean: 
	rm *.o $(TARGET)
