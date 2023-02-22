import socket
import os
import sys

SOCK = "/var/www/cgi-bin/led.soc"
GPIOS = ["464", "465", "466", "467"]
SYFS_GPIO = "/sys/class/gpio"

##
# Config selected GPIO as output
#
def cfg_as_led(gpio:int):
    if(gpio >= len(GPIOS)):
        return

    f = open(f"{SYFS_GPIO}/gpio{GPIOS[gpio]}/direction", 'w')
    f.write("out")
    f.close();

##
# Set output value for selected gpio
#
def set_led(gpio:int, val:str):
    if(gpio >= len(GPIOS)):
        return

    f = open(f"{SYFS_GPIO}/gpio{GPIOS[gpio]}/value", 'w')
    f.write(val)
    f.close()


##
# GPIO initialization
#
def init_gpio():
    for i in range(len(GPIOS)):
        if(os.path.exists(f"{SYFS_GPIO}/gpio{GPIOS[i]}") == False):
            f = open(f"{SYFS_GPIO}/export", 'w')
            f.write(GPIOS[i]);
            f.close();
        cfg_as_led(i)
        set_led(i, "0")


## Enter point

init_gpio()

# Create a TCP/IP socket
sock = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)

# Bind the socket to the port
print(f'starting up on {SOCK}')
sock.bind(SOCK)
os.chmod(SOCK, 0o666)
# Listen for incoming connections
sock.listen(1)

print('waiting for a connection')
try:
    while True:
        # Wait for a connection
        connection, client_address = sock.accept()
        try:
            #print('connection to', client_address)
            # Receive the data in small chunks and retransmit it
            while True:
                data = connection.recv(16)
                print(f"get data {data}")
                if data:
                    sp = data.decode().split(':')
                    if(len(sp) == 2):
                        sp[1] = sp[1].replace(';', '')
                        set_led(int(sp[0]), sp[1]);
                else:
                    #print('no data from', client_address)
                    break
        finally:
            # Clean up the connection
            connection.close()
except KeyboardInterrupt:
    os.unlink(SOCK)
    print("socket is closed")
