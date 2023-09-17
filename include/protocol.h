#ifndef _PROTOCOL_H
#define _PROTOCOL_H

/*
 * Returns
 *   -1 if sending message failed
 *   0 otherwise
 *
 *  int sock -- fd for socket
 *  char *unformatted_msg -- string being formatted and sent
 */
int send_message(int sock, char *unformatted_msg);

/*
 * Returns
 *   NULL if recieving message fails
 *   non-NULL otherwise
 *
 *  int sock -- fd for socket
 */
char *recv_message(int sock);

#endif
