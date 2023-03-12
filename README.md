# WTF

Files for laboratory work on Baget-PLK with Linux Debian 10

# Prepare environment

Need create Virtual machine with some additional softwares. Except Kubuntu 22.04 LTS, with additionay installedt utils:

* VSCode
* device-tree-compiler
* debootstrap
* qemu with support mipsel64 architecture
* scp tools
* mips64el-linux-gnu-gcc
* mips64el-linux-gnu-g++

Also need add initialization of BAGET env in bashrc file with value of path to /home/student/baget/

# UPD

## Lab 01

busybox от debian (со штатной libc, либо статический вариант)
Здесь самая интересная вещь для изучения: загрузочный скрипт. Можно начать с десятка строчек и наделать упражнений на расширение возможностей скрипта. При этом усваивается идея, что начальная загрузка может быть очень простой процедурой, а не как в современном дистрибутиве. Ну и в целом последовательность загрузки и состав окружения усваивается лучше, поскольку в этом варианте еще обозримо и усваиваемо.


на другом конце спектра находится минимальный образ, получаемый из стандартного дистрибутива. Скажем, установщик поставил пару десятков никому не нужных пакетов, их можно спокойно удалить или не ставить сразу. Выяснение, какие пакеты не нужны, даст намного больше информации о дистрибутиве нежели его установка.

## Lab 02

Use libgpiod (https://devdotnet.org/post/rabota-s-gpio-v-linux-chast-6-biblioteka-libgpiod/)
