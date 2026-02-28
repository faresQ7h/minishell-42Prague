# **************************************************************************** #
#                                   CONFIG                                     #
# **************************************************************************** #

NAME		= minishell

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -I$(INC_DIR) -I$(LIBFT_DIR)
RM			= rm -f

# **************************************************************************** #
#                                   PATHS                                      #
# **************************************************************************** #

SRC_DIR		= srcs
INC_DIR		= includes
LIBFT_DIR	= libft

READLINE	= -lreadline -lhistory

# **************************************************************************** #
#                                   FILES                                      #
# **************************************************************************** #

SRCS		= main.c \
              builtins.c\
			  builtins_2.c\
              signals.c \
              utils.c \
              free.c \
              lexer.c \
              lexer_token.c \
              lexer_extract.c \
              parser.c \
              parser_utils.c \
              command_utils.c \
              expander.c \
              expander_utils.c \
              env.c \
              env_utils.c \
              path_finder.c \
              heredoc.c \
              redirections.c \
              executor.c \
              executor_utils.c \
              prompt.c \
              wait.c \
              heredoc_signals.c

SRCS		:= $(addprefix $(SRC_DIR)/, $(SRCS))
OBJS		:= $(SRCS:.c=.o)

# **************************************************************************** #
#                                   RULES                                      #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_DIR)/libft.a $(READLINE) -o $(NAME)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make clean -C $(LIBFT_DIR)
	$(RM) $(OBJS)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re