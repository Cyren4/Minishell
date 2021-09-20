# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/17 16:13:53 by vbaron            #+#    #+#              #
#    Updated: 2021/09/20 20:59:40 by vbaron           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DIR_S = ./
DIR_O = objs

SOURCES = ast_interpreter.c

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))
OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))
HEADERS = headers
LIBFT_DIR = ../lib/libft

NAME = my_interpreter

CC = gcc -g3 

LIBFT = $(addprefix $(LIBFT_DIR)/,libft.a)

all: $(LIBFT) $(NAME)

$(DIR_O)/%.o: $(DIR_S)/%.c
	mkdir -p $(DIR_O)	
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJS) $(LIBFT)
		$(CC) -lreadline $(CFLAGS) $^ -o $@

$(LIBFT):
		 make -C $(LIBFT_DIR)

clean:
		rm -f $(OBJS)		
	rm -f $(OBJS)/*.o
	rm -rf $(DIR_O)	
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -rf $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: re fclean all clean

