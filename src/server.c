#include "protocol.h"
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <netdb.h>
#include <signal.h>
#include <errno.h>

#include "err.h"

#define QUEUE_SIZE 8

volatile int active = 1;

void exit_handler(int signum)
{
    while (waitpid(-1, NULL, WNOHANG) > 0) continue;
    active = 0;
}

void child_handler(int signum)
{
    while (waitpid(-1, NULL, WNOHANG) > 0) continue;
}

void install_handlers(void)
{
    struct sigaction exitact, chldact;
    exitact.sa_handler = exit_handler;
    exitact.sa_flags = 0;
    sigemptyset(&exitact.sa_mask);

    chldact.sa_handler = child_handler;
    chldact.sa_flags = 0;
    sigemptyset(&chldact.sa_mask);


    sigaction(SIGINT, &exitact, NULL);
    sigaction(SIGTERM, &exitact, NULL);
    sigaction(SIGCHLD, &chldact, NULL);

    
}

int open_listener(char *service, int queue_size)
{
    struct addrinfo hint, *info_list, *info;
    int error, sock;

    // initialize hints
    memset(&hint, 0, sizeof(struct addrinfo));
    hint.ai_family   = AF_UNSPEC;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_flags    = AI_PASSIVE;

    // obtain information for listening socket
    error = getaddrinfo(NULL, service, &hint, &info_list);
    if (error) {
        err("getaddrinfo: %s\n", 0, gai_strerror(error));
        return -1;
    }

    // attempt to create socket
    for (info = info_list; info != NULL; info = info->ai_next) {
        sock = socket(info->ai_family, info->ai_socktype, info->ai_protocol);

        // if we could not create the socket, try the next method
        if (sock == -1) continue;

        // bind socket to requested port
        error = bind(sock, info->ai_addr, info->ai_addrlen);
        if (error) {
            close(sock);
            continue;
        }

        // enable listening for incoming connection requests
        error = listen(sock, queue_size);
        if (error) {
            close(sock);
            continue;
        }

        // if we got this far, we have opened the socket
        break;
    }

    freeaddrinfo(info_list);

    // info will be NULL if no method succeeded
    if (info == NULL)
    {
        err("Binding Failed", 0);
        return -1;
    }

    return sock;
}

void client_print(char *host, char *service, char *str)
{
  printf("[%s:%s] %s\n", host, service, str);
}

void handle_client(int sock, struct sockaddr *remote_host, socklen_t remote_host_len)
{
	char host[100], service[10], *message, *err_msg;
	int error;

  err_msg = "INTERPRETER NOT IMPLEMENTED";

	error = getnameinfo(remote_host, remote_host_len, host, 100, service, 10, NI_NUMERICSERV);
	if (error) {
		err("getnameinfo: %s\n", 0, gai_strerror(error));
		strcpy(host, "??");
		strcpy(service, "??");
	}

	printf("Connection from %s:%s\n", host, service);

  while (1) {
    if ((message = recv_message(sock)) == NULL) exit(EXIT_FAILURE); 
    client_print(host, service, message);
    free(message);

    if (send_message(sock, err_msg) < 0) exit(EXIT_FAILURE);
  }
}

int main(int argc, char **argv)
{
	struct sockaddr_storage remote_host;
    socklen_t remote_host_len;
    char *service;
	pid_t pid;

    service = argc == 2 ? argv[1] : "15000";

    install_handlers();

	int listener = open_listener(service, QUEUE_SIZE);
    if (listener < 0)
        return EXIT_FAILURE;

    puts("Listening for incoming connections");

	while (active)
	{
		remote_host_len = sizeof(remote_host);

		int sock = accept(listener, (struct sockaddr *)  &remote_host, &remote_host_len);

		if (sock < 0) 
		{
			close(sock);
			continue;
		}
		
		pid = fork();
		
		if (pid == 0)
		{
			handle_client(sock, (struct sockaddr *)&remote_host, remote_host_len);

			close(sock);
			_exit(0);
		}
	}	
}


