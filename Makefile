NAME = minishell

CFLAGS = -Wall -Wextra -Werror -I $(READLINE)include/ # -g -fsanitize=address

LIBFT_PATH = inc/libft/
LIBFT_FLAGS = -L $(LIBFT_PATH) -lft
LIBFT = $(LIBFT_PATH)libft.a

READLINE = $(PWD)/inc/readline/
RL_FLAGS = -lreadline -L $(READLINE)lib -lhistory -I $(READLINE)include/

SRC_PATH = src/

B_PATH = $(SRC_PATH)builtins/
B_SRC = $(B_PATH)ctrl_builtins.c $(B_PATH)cd.c $(B_PATH)pwd.c $(B_PATH)echo.c $(B_PATH)env.c \
$(B_PATH)export.c $(B_PATH)export_helpers.c $(B_PATH)unset.c $(B_PATH)exit.c $(B_PATH)exit_helpers.c

EX_PATH = $(SRC_PATH)executor/
EX_SRC = $(EX_PATH)executor.c $(EX_PATH)executor_helpers1.c $(EX_PATH)executor_helpers2.c $(EX_PATH)executor_helpers3.c

EXP_PATH = $(SRC_PATH)expander/
EXP_SRC = $(EXP_PATH)expander.c $(EXP_PATH)expander_helpers_1.c $(EXP_PATH)expander_helpers_2.c

FREE_PATH = $(SRC_PATH)free/
FREE_SRC = $(FREE_PATH)free_helpers_1.c $(FREE_PATH)free_helpers_2.c

H_PATH = $(SRC_PATH)helpers/
H_SRC = $(H_PATH)helpers.c

PARSER_PATH = $(SRC_PATH)parser/
PARSER_SRC = $(PARSER_PATH)parser.c $(PARSER_PATH)parser_helpers1.c $(PARSER_PATH)parser_helpers2.c $(PARSER_PATH)word_split.c

RED_PATH = $(SRC_PATH)redir/
RED_SRC = $(RED_PATH)get_fd.c $(RED_PATH)get_fd_helpers.c $(RED_PATH)error_ctrl.c $(RED_PATH)heredoc.c

SIG_PATH = $(SRC_PATH)signal/
SIG_SRC = $(SIG_PATH)signal_handle.c

SRCS = src/main.c src/env/env_handle1.c src/env/env_handle2.c src/syntax_check.c \
$(B_SRC) $(EX_SRC) $(EXP_SRC) $(FREE_SRC) $(H_SRC) $(PARSER_SRC) $(RED_SRC) $(SIG_SRC)

OBJS = $(SRCS:.c=.o)

all: $(READLINE) $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	cc $(CFLAGS) $(OBJS) $(LIBFT_FLAGS) $(RL_FLAGS) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_PATH)

$(READLINE):
	curl -O https://ftp.gnu.org/gnu/readline/readline-8.2.tar.gz
	tar -xvf readline-8.2.tar.gz
	cd readline-8.2 && ./configure --prefix=$(READLINE)
	cd readline-8.2 && make install
	@rm -fr readline-8.2 readline-8.2.tar.gz

clean:
	make -C $(LIBFT_PATH) clean
	$(RM) $(OBJS)

fclean: clean
	$(RM) -r inc/readline
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re test
