# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/13 13:33:21 by cramdani          #+#    #+#              #
#    Updated: 2021/11/28 16:40:29 by cramdani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN	=	\033[0;32m
BLUE	=	\033[0;34m
END		=	\033[m

NAME 	=	lib.a

CC		=	clang
CFLAGS	=	-Wall -Wextra -Werror 

LIBFT_P	=	libft

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
