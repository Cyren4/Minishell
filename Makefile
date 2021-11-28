# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/20 12:16:14 by cramdani           #+#    #+#              #
#    Updated: 2021/11/16 15:33:30 by vbaron           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include minishell.mk

NAME		=	minishell

SRCS_DIR	=	srcs
OBJS_DIR	=	objs
INC_DIR		=	includes
HEADER		=	$(INC_DIR)/minishell.h

CC			=	clang
RM			=	/bin/rm -rf
INC			=	-include ./$(HEADER)
CC_FLAGS	=	-Wall -Wextra -Werror $(INC)
LIB_DIR			=	lib
LIB				=	$(LIB_DIR)/libft.a


SRCS	=	$(addprefix $(SRCS_DIR)/, $(FILES))
OBJS 	=	$(addprefix $(OBJS_DIR)/, $(FILES:.c=.o))

all:		$(NAME)

$(NAME):	$(OBJS) $(HEADER)
			@make -C $(LIB_DIR)
			@$(CC) $(CC_FLAGS) $(OBJS) -lreadline  $(LIB) -o $(NAME)
			@printf "$(GREEN)$(NAME) created with '$(CC_FLAGS)' flags\n$(END)"
			@printf "$(PURPLE)Minishell is ready to work!\n$(END)"

$(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c | $(OBJS_DIR)
	    	@$(CC) $(CC_FLAGS) -c $< -o $@

$(OBJS_DIR):
		@mkdir -p $@
		@mkdir $(addprefix $(OBJS_DIR)/, $(SUB_DIR))
		@printf "Create object directories : $(GREEN)$(OBJS_DIR)\n$(END)"
		@printf "Create object subdirectories : $(GREEN)$(SUB_DIR)\n$(END)"

clean:
			@make clean -C $(LIB_DIR)
			@$(RM) $(OBJS_DIR)
			@printf "$(RED)Cleaning is done!\n$(END)"

fclean:		clean
			@make fclean -C $(LIB_DIR)
			@$(RM) $(NAME)
			@printf "$(YELLOW)FCleaning is done!\n$(END)"

re:			fclean all

.PHONY: clean fclean re compile all