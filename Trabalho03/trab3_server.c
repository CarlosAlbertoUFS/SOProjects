

/*Para compilar este programa use:
Compilar:  gcc -o server.out server.c
Executar: ./server.out [nome do socket]
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

/* Leia o texto do socket e imprima na saida principal.
  Continue até o socket fechar.  Retorne um numero diferente de 0 
  se o cliente mandar uma mensagem "quit", se não retorne 0.  */

int server (int client_socket) {
  while (1) {
    int length;
    char* text;
/* Primeiro, leia o tamanho da mensagem do socket.
Se o valor for 0, o cliente fecha a conexão.  */
  if (read (client_socket, &length, sizeof (length)) == 0){
        return 0;
  }
             /* Alocar um buffer para manipular um texto.  */
             text = (char*) malloc (length);
             /* Leia o texto vc mesmo, e implima-o.  */
            read (client_socket, text, length);
             printf ("%s\n", text);

       /* Se o cliente mandar a mensagem "quit", nós terminaremos.  */
       if (!strcmp(text, "quit")){
          return 1;
       }
         /* Libere o buffer.  */
             free (text);

      }
}

int main (int argc, char* const argv[]) {
  const char* const socket_name = argv[1];

int socket_fd; struct sockaddr_un name;
  int client_sent_quit_message;
/* Cria o socket.  */
  socket_fd = socket (PF_LOCAL, SOCK_STREAM, 0);
  /* Indica que este é um servidor  */
  name.sun_family = AF_LOCAL;
  strcpy (name.sun_path, socket_name);
  bind (socket_fd, &name, SUN_LEN (&name));
  /* Ouve a conexão  */
  listen (socket_fd, 5);
/* Aceite conexões repetidamente, execute todas as tarefas para cada cliente.
  Continue até o cliente mandar uma mensagem com o nome “quit”.  */
  do {
    struct sockaddr client_name;
    socklen_t client_name_len;
    int client_socket_fd;
   /* Aceite uma conexão.  */
    client_socket_fd = accept (socket_fd, &client_name, &client_name_len);
    /* Manipule uma conexão  */
    client_sent_quit_message = server (client_socket_fd);
    /* Feche uma conexão.  */
    close (client_socket_fd);
} while (!client_sent_quit_message);

/* Remova o arquivo de socket.  */
  close (socket_fd);
  unlink (socket_name);
return 0;
}