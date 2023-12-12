# WTF

Files for laboratory work on Baget-PLK with Linux Debian 10

# Prepare environment

* Create Virtual machine with Kubuntu 20.04 LTS with user student and password usrstudent (user must be add to sudo groups)
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

# UPD

## Lab 01

добавить --variant=minbase (нужны тесты)
добавить ссылку на https://linux.die.net/man/8/debootstrap?__cf_chl_tk=k1Rn6ACsoytnA0aX1mJq53Hn67ZY4cUhSHFXGzG2EFM-1702404302-0-gaNycGzNDuU

busybox от debian (со штатной libc, либо статический вариант)
Здесь самая интересная вещь для изучения: загрузочный скрипт. Можно начать с десятка строчек и наделать упражнений на расширение возможностей скрипта. При этом усваивается идея, что начальная загрузка может быть очень простой процедурой, а не как в современном дистрибутиве. Ну и в целом последовательность загрузки и состав окружения усваивается лучше, поскольку в этом варианте еще обозримо и усваиваемо.


на другом конце спектра находится минимальный образ, получаемый из стандартного дистрибутива. Скажем, установщик поставил пару десятков никому не нужных пакетов, их можно спокойно удалить или не ставить сразу. Выяснение, какие пакеты не нужны, даст намного больше информации о дистрибутиве нежели его установка.

## Lab 02

Use libgpiod (https://devdotnet.org/post/rabota-s-gpio-v-linux-chast-6-biblioteka-libgpiod/)
