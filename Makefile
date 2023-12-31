SERVER_NAME=server
CLIENT_NAME=client

BIN=bin

INCLUDES=-I./include
FLAGS=-Wextra -Wall -std=c99 -g -fsanitize=address


server: src/server.c src/err.c src/protocol.c
	clang $^ -o $(BIN)/$(SERVER_NAME) $(INCLUDES) $(FLAGS)

client: src/client.c src/err.c src/protocol.c
	clang $^ -o $(BIN)/$(CLIENT_NAME) $(INCLUDES) $(FLAGS)

tree_test: src/main.c src/btree.c
	clang $^ -o $(BIN)/tree_test $(INCLUDES) $(FLAGS)
