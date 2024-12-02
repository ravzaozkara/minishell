NAME = minishell
CC			= cc
CFLAGS = -Wall -Wextra -Werror -I $(READLINE)include/ # -g -fsanitize=address

LIBFT_PATH = inc/libft/
LIBFT_FLAGS = -L $(LIBFT_PATH) -lft
LIBFT = $(LIBFT_PATH)libft.a

READLINE = $(PWD)/inc/readline/
RL_FLAGS = -lreadline -L $(READLINE)lib -lhistory -I $(READLINE)include/

SRCS = $(shell find src -maxdepth 2 -name '*.c')

OBJS = $(SRCS:.c=.o)

all: $(READLINE) $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_FLAGS) $(RL_FLAGS) -o $(NAME)

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
	make -C $(LIBFT_PATH) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re test
