FILES = minishell.c \
		display/display_prompt.c \
		error/error.c \
		utils/display_env_vars.c \
		parsing/env_utils.c \
		parsing/env_vars_parsing.c \
		parsing/token_insert_var.c \
		parsing/token_split.c \
		parsing/token_utils.c \
		parsing/token.c \
		utils/utils_1.c \
		utils/clear.c \
		parsing/ast_builder.c \
		parsing/build_leaf_ast.c \
		parsing/build_node_ast.c \
		utils/print_tree.c \
		parsing/create_pipes.c \
		executor/builtin/export.c \
		executor/builtin/unset.c \
		executor/builtin/env.c \
		executor/builtin/cd.c \
		executor/execute_ast.c \
		executor/execute_command.c \
		executor/is_execve.c \
		executor/signals.c \
		executor/redirections.c \

SUB_DIR	=	parsing display error utils executor executor/builtin

BLACK	=	\033[0;30m
RED		=	\033[0;31m
GREEN	=	\033[0;32m
YELLOW	=	\033[0;33m
BLUE	=	\033[0;34m
PURPLE	=	\033[0;35m
CYAN	=	\033[0;36m
WHITE	=	\033[0;37m
END		=	\033[m