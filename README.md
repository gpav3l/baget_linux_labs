# WTF

Files for laboratory work on Baget-PLK with Linux Debian 10

# Prepare environment

* Create Virtual machine with Kubuntu 20.04 LTS with user student and password usrstudent (user must be add to sudo groups)
  * Virtual machine must contain 2 network adapter one is NAT for internet connection, and second is Bridge Adapter to network interface of Host machine, which will be used for communicate with board.
* Set static IP address 192.168.100.10 to interface for board communication.
* Select from menu Devices->Insert Guest Additional... after that `sudo ./VBoxLinuxAdditions.run` from guest OS, and reboot
* Copy support folder and vm_config.sh script to Download folder of user
* launch vm_config.sh as root
* Ready to use.

Additional tools used in labs:

* VSCode
* device-tree-compiler
* debootstrap
* qemu with support mipsel64 architecture
* scp tools
* mips64el-linux-gnu-gcc
* mips64el-linux-gnu-g++
