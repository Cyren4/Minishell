# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/07 10:38:04 by cramdani          #+#    #+#              #
#    Updated: 2021/09/21 11:22:52 by vbaron           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include libft_srcs.mk

SRCS_DIR	=	srcs
OBJS_DIR	=	objs

SRCS	=	$(addprefix $(SRCS_DIR)/, $(FILES))
OBJS 	=	$(addprefix $(OBJS_DIR)/, $(FILES:.c=.o))

NAME	=	libft.a
HEADER	=	libft.h
INC 	=	-I $(HEADER)

CC		= gcc

RM		= rm -rf

CFLAGS	= -Wall -Wextra -Werror

all:	${NAME}

$(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c | $(OBJS_DIR)
	    	@$(CC) $(INC) $(CFLAGS) -c $< -o $@

${NAME}: 	 ${OBJS}
			@ar rc ${NAME} ${OBJS}
			@ranlib $(NAME)

$(OBJS_DIR):
		@mkdir -p $@
		@mkdir $(OBJS_DIR)/srcs_printf

clean:
		@${RM}  $(OBJS_DIR)

fclean:		clean
			@${RM} ${NAME}

re:		fclean all

.PHONY:		all clean fclean re 
