#ifndef _DATABASE_H
#define _DATABASE_H

/*
 * Returns
 *   0 upon success
 *   -1 upon failure to create db
 *
 * Will create a new db folder in the data folder. Maybe
 * path to data folder should be configurable by server
 * user.
 */
int create_database(char *name);

#endif
