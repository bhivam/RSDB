# RSDB
A simple database server that clients can connect to remotely to read and write data.

## Initial Plans
### Client Server Communication 
- Format the command from the client to have the size of the string at the beggining. Use a '|' to delimit this. We need to do this server-side and client-side;
  - ex. "5|hello"
### Database Capabilities
- Create a database file
- Create various tables in a DB file
  - Support integer and string datatypes
- CREATE, READ operations
- we want to have a WHERE condition
  - Only have equal.
### Interpreting Commands
- Tokenize commands from the client
- create a command using the tokens
- act on the command

## Future Goals
To be determined...
