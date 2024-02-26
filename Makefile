CFLAGS := -Wall -Wextra -Werror
SERVER_CFILES := src/server.c
SERVER_OFILES := $(SERVER_CFILES:.c=.o)
SERVER_NAME := server
CLIENT_CFILES := src/client.c
CLIENT_OFILES := $(CLIENT_CFILES:.c=.o)
INCLUDE := include
LIBFT_PATH := libft/
LIBFT := libft.a
CLIENT_NAME := client

all: libft $(SERVER_NAME) $(CLIENT_NAME)

$(SERVER_NAME): $(SERVER_OFILES)
	$(CC) $(SERVER_OFILES) $(LIBFT_PATH)$(LIBFT) -o $(SERVER_NAME)

$(CLIENT_NAME): $(CLIENT_OFILES)
	$(CC) $(CLIENT_OFILES) $(LIBFT_PATH)$(LIBFT) -o $(CLIENT_NAME)

%.o: %.c
	$(CC) -c $(CFLAGS) -I$(INCLUDE) -I$(LIBFT_PATH)$(INCLUDE) $^ -o $@

libft:
	@make -C libft

clean:
	@make -C libft clean
	rm -f $(SERVER_OFILES)
	rm -f $(CLIENT_OFILES)

fclean: clean
	rm -f $(LIBFT)
	rm -f $(SERVER_NAME)
	rm -f $(CLIENT_NAME)

re: fclean all

.PHONY: clean fclean re libft
