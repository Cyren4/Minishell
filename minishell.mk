FILES = minishell.c \
		display/display_prompt.c \
		error/error.c \
		executor/builtin/echo.c \
		executor/builtin/export.c \
		executor/builtin/unset.c \
		executor/builtin/env.c \
		executor/builtin/cd.c \
		executor/builtin/pwd.c \
		executor/builtin/exit.c \
		executor/builtin_monitor.c \
		executor/calculate_commands.c \
		executor/execute_ast.c \
		executor/execute_command.c \
		executor/is_execve.c \
		executor/redirections.c \
		executor/signals.c \
		executor/close_pipes.c \
		parsing/env_vars_parsing.c \
		parsing/token_insert_var.c \
		parsing/token_split.c \
		parsing/token.c \
		parsing/ast_monitor/ast_builder.c \
		parsing/ast_monitor/build_leaf_ast.c \
		parsing/ast_monitor/build_node_ast.c \
		parsing/ast_monitor/create_pipes.c \
		utils/clear.c \
		utils/env_utils.c \
		utils/getter.c \
		utils/print_tree.c \
		utils/token_utils.c \
		utils/utils_1.c 


SUB_DIR	=	parsing display error utils executor executor/builtin parsing/ast_monitor

BLACK	=	\033[0;30m
RED		=	\033[0;31m
GREEN	=	\033[0;32m
YELLOW	=	\033[0;33m
BLUE	=	\033[0;34m
PURPLE	=	\033[0;35m
CYAN	=	\033[0;36m
WHITE	=	\033[0;37m
END		=	\033[m