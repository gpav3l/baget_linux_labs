#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>


// Application constants
#define TTY_NAME  ("/dev/ttyS2")
#define BUFF_SIZE (256)
#define FIFO_SIZE (16) // can't be more than hardware size is 

// Function prototypes
int tty_init(char *port, int speed);


/** Application enter point **/
int main() 
{
    uint8_t tx_buff[BUFF_SIZE];
    uint8_t rx_buff[BUFF_SIZE];
    
    // Try connect to tty
    int tty_id = tty_init(TTY_NAME, B115200);
    
    if(tty_id < 0) {
        printf("ERROR: tty can't be open\n");
        return -1;
    }

    // Prepare test buffer
    for(int i=0; i<BUFF_SIZE; i++) {
        tx_buff[i] = i%10 + 0x30; // Fill with digit from 0 to 9
    }
    
    // try send and get back data
    int byte_cnt = 0;
    for(int i=0; i<BUFF_SIZE; i+=FIFO_SIZE) {
        byte_cnt = write(tty_id, &tx_buff[i], FIFO_SIZE);
        if(byte_cnt != FIFO_SIZE) {
            printf("WARNING: send %d from %d\n", byte_cnt, FIFO_SIZE);
        }

        byte_cnt = read(tty_id, &rx_buff[i], FIFO_SIZE);
        if(byte_cnt != FIFO_SIZE) {
            printf("WARNING: get %d from %d\n", byte_cnt, FIFO_SIZE);
        }
    }
    close(tty_id);

    // Compare buffers
    if(memcmp(tx_buff, rx_buff, BUFF_SIZE) != 0) 
        printf("ERROR: rx and tx buffer is diff\n");
    else 
        printf("SUCCESS: rx and tx buffer is some\n");

    return 0;
}


/**
 * Initialize tty controller.
 * 
 * @param port is name of connected tty
 * @param speed set speed of tty, use one from termios.h defines
 * 
 * @return 
*/
int tty_init(char *port, int speed)
{
    int _tty_id;
    struct termios tty;

    _tty_id = open(port, O_RDWR);
    if(_tty_id < 0)
        return _tty_id;

    if(tcgetattr(_tty_id, &tty) != 0) {
        close(_tty_id);
        _tty_id = -1;
        return _tty_id;
    }

    tty.c_cflag &= ~PARENB; // No parity
    tty.c_cflag &= ~CSTOPB; // 1 stop bit
    // Set 8 bit data length
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;
    tty.c_cflag &= ~CRTSCTS; // Disable RTS/CTS
    tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)
    tty.c_lflag &= ~ICANON; // Disabel chanonical read
    tty.c_lflag &= ~ECHO; // Disable echo
    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
    tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes
    tty.c_lflag &= ~ISIG;  // Disable interpretation of INTR, QUIT and SUSP
    tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
    tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed
    tty.c_cc[VTIME] = 2;
    tty.c_cc[VMIN] = 0;

    cfsetispeed(&tty, speed);
    cfsetospeed(&tty, speed);

    if (tcsetattr(_tty_id, TCSANOW, &tty) != 0) {
        close(_tty_id);
        _tty_id = -1;
        return _tty_id;
    }

    return _tty_id;
}
