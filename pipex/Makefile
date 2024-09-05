SRC	  =		src/pipex.c						\
			src/cmd_exec.c					\
			mini_libft/mini_libft.c 		\
			mini_libft/mini_libft1.c 		\
			mini_libft/mini_libft2.c		\
			gnl/get_next_line_utils.c 		\



BONUS =		bonus/pipex.c					\
			bonus/bonus.c					\
			bonus/fork.c					\
			mini_libft/mini_libft.c 		\
			mini_libft/mini_libft1.c 		\
			mini_libft/mini_libft2.c		\
			src/cmd_exec.c					\
			gnl/get_next_line.c 			\
			gnl/get_next_line_utils.c 		\
			

	


NAME =		pipex

NAME_BONUS =	pipex_bonus

CFLAGS =	-Wall -Werror -Wextra -g3 -I./inc

CC =		cc

OBJ = $(SRC:.c=.o)

OBJ_BONUS = $(BONUS:.c=.o)

all:		$(NAME)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) -o $@ $^

$(NAME_BONUS): $(OBJ_BONUS)
		$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
		rm -f $(OBJ)
		rm -f $(OBJ_BONUS)


fclean: clean
		rm -f $(NAME)
		rm -f $(NAME_BONUS	)

bonus: $(NAME_BONUS)

re: fclean all

.PHONY: clean fclean all re bonus