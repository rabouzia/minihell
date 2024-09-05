NAME     =		minihell

SRC	     =		src/main.c	\

CC       =	    cc

CFLAGS   =	    -Wall -Wextra -Werror -g3 -I./inc -lreadline

OBJ_DIR	 =	    obj/

SRCS     =      $(SRC)

OBJ 	 =      $(patsubst src/%.c, $(OBJ_DIR)%.o, $(SRCS))

MAKE_DIR =      mkdir -p

SMAKE	 =      make --no-print-directory

all:	        $(NAME)

$(NAME):        $(OBJ)
				@$(CC) $(CFLAGS) $(OBJ) -o $@ -pthread
				
$(OBJ_DIR)%.o:  src/%.c
			    @mkdir -p $(OBJ_DIR)
			    @$(CC) $(CFLAGS) -c $< -o $@ 

clean:
				@rm -rf $(OBJ_DIR)
				@echo "\033[1;31m======== object files removed ========\033[0m"

fclean:         clean
				@$(RM) $(NAME)
				@echo "\033[1;31m========  executable removed  =======\033[0m"

re:             fclean
				@$(SMAKE)

.PHONY: clean fclean all re