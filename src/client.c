#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

#include "err.h"

#define BUFLEN 256

int connect_inet(char *host, char *service)
{
	struct addrinfo hints, *info_list, *info;
	int sock, error;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	error = getaddrinfo(host, service, &hints, &info_list);
	if (error)
	{
		err("error loocking up %s:%s: %s\n", 0, host, service, gai_strerror(error));
		return -1;
	}
	
	for (info = info_list; info != NULL; info = info->ai_next)
	{
		sock = socket(info->ai_family, info->ai_socktype, info->ai_protocol);
		if (sock < 0) continue;

		error = connect(sock, info->ai_addr, info->ai_addrlen);
		if (error)
		{
			close(sock);
			continue;
		}

		break;
	}
	freeaddrinfo(info_list);

	if (info == NULL)
	{
		err("Unable to connect to %s:%s\n", 0, host, service);
		return -1;
	}

	return sock;
}

void server_print(char *str, char *host, char *service)
{
	printf("[%s:%s] %s", host, service, str);
}

char *read_line(int fd)
{
    char read_buffer[BUFSIZ];
    memset(read_buffer, 0, BUFSIZ);

    char *line = malloc(1);

    int bytes_read = 0;
    int offset = lseek(fd, 0, SEEK_CUR);
    int line_size = 0;

    int nl = 0;

    while (nl == 0 && (bytes_read = read(fd, read_buffer, BUFSIZ - 1)) > 0)
    {
        for (int charidx = 0; charidx < bytes_read; charidx++)
        {
            if (read_buffer[charidx] == '\n')
            {
                lseek(fd, offset + charidx + 1, SEEK_SET);
                bytes_read = charidx + 1;
                nl = 1;
                break;
            }
        }

        line = realloc(line, (line_size + bytes_read));
        memmove(line + line_size, read_buffer, bytes_read);
        offset = offset + bytes_read;
        line_size = line_size + bytes_read;

        memset(read_buffer, 0, BUFSIZ);
    }

    if (line_size == 0) return NULL;

    line = realloc(line, (line_size + 1));
    line[line_size] = 0;
    return line;
}

int main(int argc, char **argv)
{
	int sock, bytes;
	char *host, *service, buf[10], *line;


	if (argc != 3)
	{
		err("Usage: ./[hostname] [service]\n", 0);
		exit(EXIT_FAILURE);
	}

	host = argv[1];
	service = argv[2];

	sock = connect_inet(host, service);
	if (sock < 0) exit(EXIT_FAILURE);
	
	while (1)
	{
		line = read_line(STDIN_FILENO);
		if (line == (char *) 0)
		{
			err("Read line failed", 0);
			exit(EXIT_FAILURE); 
		}

		if (strcmp(line, "exit\n") == 0)
		{
			//TODO look at this
			break;
		}
		
		//TODO make this into a loop for saftey
		bytes = write(sock, line, strlen(line));
		if (bytes <= 0) exit(EXIT_FAILURE);


		bytes = read(sock, buf, 7);
		if (bytes <= 0) exit(EXIT_FAILURE);

		server_print(buf, host, service);
		
		free(line);
	}

	return 0;

}
