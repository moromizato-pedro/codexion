NAME := codexion

SRC_DIR := ./src
INCLUDE_DIR := ./include

CC := cc
CFLAGS := -Wall -Wextra -Werror

SRC_FILE_NAME := parser.c hub.c threads.c
SRC_FILES := $(SRC_FILE_NAME:%.c=$(SRC_DIR)/%.o)

CFILES := main.c $(SRC_FILES)
COBJECTS := $(CFILES:%.c=%.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $^ -c -o $@ -I $(INCLUDE_DIR)

$(NAME): $(COBJECTS)
	$(CC) $(CFILES) -o $(NAME)

clean:
	rm -f $(COBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all
