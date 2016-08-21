/*
Para executar nos pcs do laboratório
Compila: gcc -o a untitled.c
Executa: ./a

[sabedoria@graduacao05-03 Área de trabalho]$ gcc -o a untitled.c
[sabedoria@graduacao05-03 Área de trabalho]$ ./a
total 52
lrwxrwxrwx   1 root root     7 set 30  2015 bin -> usr/bin
drwxr-xr-x   3 root root  4096 ago 11 09:02 boot
drwxr-xr-x  19 root root  3240 ago 15 13:03 dev
drwxr-xr-x  75 root root  4096 ago 11 09:55 etc
drwxr-xr-x   6 root root  4096 ago 11 17:14 home
lrwxrwxrwx   1 root root     7 set 30  2015 lib -> usr/lib
lrwxrwxrwx   1 root root     7 set 30  2015 lib64 -> usr/lib
drwx------   2 root root 16384 set 14  2015 lost+found
drwxr-xr-x   2 root root  4096 fev 15  2015 mnt
drwxr-xr-x   3 root root  4096 out 22  2015 opt
dr-xr-xr-x 157 root root     0 ago 15 10:03 proc
drwxr-x---  23 root root  4096 ago 11 09:22 root
drwxr-xr-x  20 root root   500 ago 15 13:17 run
lrwxrwxrwx   1 root root     7 set 30  2015 sbin -> usr/bin
drwxr-xr-x   4 root root  4096 fev 15  2015 srv
dr-xr-xr-x  13 root root     0 ago 15 13:48 sys
drwxrwxrwt  10 root root   240 ago 15 14:06 tmp
drwxr-xr-x   8 root root  4096 nov  6  2015 usr
drwxr-xr-x  12 root root  4096 nov  6  2015 var
[sabedoria@graduacao05-03 Área de trabalho]$ 

*/

#include <stdlib.h>
int main ()
{
int return_value;
return_value = system ("ls -l /");
return return_value;
}