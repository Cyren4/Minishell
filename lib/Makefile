# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/13 13:33:21 by cramdani          #+#    #+#              #
#    Updated: 2021/10/18 11:54:40 by vbaron           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN	=	\033[0;32m
BLUE	=	\033[0;34m
END		=	\033[m

NAME 	=	lib.a

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror 
RM		=	rm -f

LIBFT_P	= libft

LIB		= $(LIBFT_P)/libft.a 

all		:	${NAME}

$(NAME) : ${OBJS} 
		@make -C ${LIBFT_P}
		@cp $(LIBFT_P)/libft.a .
		@printf "$(GREEN)Libraries are ready to run\n$(END)"

clean	:
		@make fclean -C ${LIBFT_P}

fclean	:	clean
			@${RM} libft.a 
			@printf "$(BLUE)Libraries are cleaned\n$(END)"

re		:	fclean all

.PHONY	:	all clean fclean re
