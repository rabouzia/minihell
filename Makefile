NAME     =		minihell

DIR 	 =      src/

SRC	     =		src/main.c							\
				src/parsing/parsing.c     			\
				src/parsing/syntax_analysis.c		\
				src/parsing/tidying.c				\
				src/parsing/tokenization.c			\
				src/parsing/tokenization_utils.c	\
				src/exec/exec.c						\
				src/expand/expand.c					\
				src/lib/char.c						\
				src/lib/command.c					\
				src/lib/debug.c						\
				src/lib/redir.c						\
				src/lib/string.c					\
				src/lib/tab.c						\
				src/lib/token.c						\


CC       =	    cc

CFLAGS   =	    -Wall -Wextra -Werror -g3 -I./inc 

OBJ_DIR	 =	    obj/

SRCS     =      $(SRC)

# Adjust the pattern to keep subdirectory structure
OBJ 	 =      $(patsubst src/%.c, $(OBJ_DIR)%.o, $(SRCS))

MAKE_DIR =      mkdir -p

SMAKE	 =      make --no-print-directory

# Ensure all directories are created before compiling object files
$(OBJ_DIR)%.o:  src/%.c
				@$(MAKE_DIR) $(dir $@)
				@$(CC) $(CFLAGS) -c $< -o $@

all:	        $(NAME)

$(NAME):        $(OBJ)
				@$(CC) $(CFLAGS) $(OBJ) -o $@ -lreadline

clean:
				@rm -rf $(OBJ_DIR)
				@echo "\033[1;31m======== object files removed ========\033[0m"

fclean:         clean
				@$(RM) $(NAME)
				@echo "\033[1;31m========  executable removed  =======\033[0m"

re:             fclean all

.PHONY: clean fclean all re

