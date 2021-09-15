FILES = minishell.c \
		display/display_prompt.c \
		parsing/env_vars_parsing.c \
		error/error.c \
		utils/display_env_vars.c \

SUB_DIR	=	executor parsing display error executor/e_util utils

BLACK	=	\033[0;30m
RED		=	\033[0;31m
GREEN	=	\033[0;32m
YELLOW	=	\033[0;33m
BLUE	=	\033[0;34m
PURPLE	=	\033[0;35m
CYAN	=	\033[0;36m
WHITE	=	\033[0;37m
END		=	\033[m