#!/bin/bash

# Set root password and switch to it
if [ "$EUID" -ne 0 ]; then
	echo "Script must be run by root"
	echo "Don't forgot set root password by command 'sudo passwd root', before launch that script"
	exit 0
fi

usermod -a -G dialout student
usermod -a -G vboxsf student

apt update
apt upgrade -y

apt install -y gcc-mipsel-linux-gnu \
g++-mipsel-linux-gnu \
gcc-mips64el-linux-gnuabi64 \
g++-mips64el-linux-gnuabi64 \
default-jre \
gtkterm \
make \
device-tree-compiler \
fakeroot \
fakechroot \
debootstrap \
gparted \
qemu-user-static

# Install VS code
apt-get install wget gpg
wget -qO- https://packages.microsoft.com/keys/microsoft.asc | gpg --dearmor > packages.microsoft.gpg
install -D -o root -g root -m 644 packages.microsoft.gpg /etc/apt/keyrings/packages.microsoft.gpg
sh -c 'echo "deb [arch=amd64,arm64,armhf signed-by=/etc/apt/keyrings/packages.microsoft.gpg] https://packages.microsoft.com/repos/code stable main" > /etc/apt/sources.list.d/vscode.list'
rm -f packages.microsoft.gpg

apt install apt-transport-https
apt update
apt install code

# Install Eclipse
cd /tmp
su student
wget https://ftp.fau.de/eclipse/oomph/epp/2022-06/R/eclipse-inst-jre-linux64.tar.gz
tar -xzf eclipse-inst-jre-linux64.tar.gz
./eclipse-installer/eclipse-inst
