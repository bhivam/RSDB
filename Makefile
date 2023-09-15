SERVER_NAME=server
CLIENT_NAME=client
BIN=bin
APP_INCLUDES=-I./include

server: src/server.c src/err.c 
	clang $^ -o $(BIN)/$(SERVER_NAME) $(APP_INCLUDES)

client: src/client.c src/err.c
	clang $^ -o $(BIN)/$(CLIENT_NAME) $(APP_INCLUDES)
