
/*Para este programa funcionar execute primeiro o trab3_server.c
Depois este.

Para compilar este programa:
gcc -o client.out client.c
Para executar :
./client.out [nome do socket] [texto para ser enviado]*/

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>


/* Escreve um TEXTO no socket nomeado pelo pelo descritor de arquivo que está em SOCKET_FD.  */
void write_text (int socket_fd, const char* text) {
/* Escreve o numero de bytes que estão no array incluindo a terminação em NULL */
 int length = strlen (text) + 1;
 write (socket_fd, &length, sizeof (length));
 /* Escreve a string.  */
 write (socket_fd, text, length);
}


int main (int argc, char* const argv[]) {
 const char* const socket_name = argv[1];
 const char* const message = argv[2];
 int socket_fd;
  struct sockaddr_un name;
/* Cria o socket.  */
  socket_fd = socket (PF_LOCAL, SOCK_STREAM, 0);
  /* Guarda o nome do servidor no endereço do socket.  */
  name.sun_family = AF_LOCAL;
  strcpy (name.sun_path, socket_name);
  /* Conecta o socket.  */
  connect (socket_fd, &name, SUN_LEN (&name));
  /* Escreve o texto no arquivo descritor do socket */
  write_text (socket_fd, message);
  close (socket_fd);
  return 0;
}