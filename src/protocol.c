#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#include "err.h"
#include "protocol.h"

#define BUFLEN 256


int send_message(int sock, char *unformatted_message)
{
  int unformatted_message_length = strlen(unformatted_message) + 1;
  
  char *length_string = malloc((int) log10((double) unformatted_message_length) + 2);
  sprintf(length_string, "%d", unformatted_message_length);
 
  char *message = malloc(2 + strlen(length_string) + unformatted_message_length);

  memcpy(message, length_string, strlen(length_string));
  message[strlen(length_string)] = '|';
  memcpy(message + strlen(length_string) + 1,
         unformatted_message,
         unformatted_message_length);
  message[1 + strlen(length_string) + unformatted_message_length] = 0;
  
  int bytes = write(sock, message, strlen(message) + 1);
  if (bytes < 0) return -1;
  
  free(message);
  free(length_string);
  return 0;
}

char *recv_message(int sock)
{
  char *message, *length_string;
  int bytes, message_length;
  length_string = malloc(1);
  
  int i = 0;
  // read byte by bytes
  while (1)
  {
    // TODO check for having only numeric

    length_string = realloc(length_string, i + 1);
    bytes = read(sock, length_string + i, 1);
    if (bytes < 0) return NULL;

    if (length_string[i] == '|')
      break;

    i++;
  }
  
  length_string[i] = 0;
  
  message_length = atoi(length_string);
  message = malloc(message_length);

  bytes = read(sock, message, message_length);
  if (bytes < 0) return NULL;
    
  return message;
}

