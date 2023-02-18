
NAME		= minishell
LIBFT		= lib/libft/libft.a
CC			= cc
CFLAGS		= -Wall -Werror -Wextra
RM			= rm -f

GREEN		= \033[0;32m
CYAN		= \033[0;36m
WHITE		= \033[0m

SRC_FILES	=
SRC_DIR		= src/
OBJ_DIR		= obj/
SRC			= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ			= $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
OBJF		= .cache_exists

all:		$(NAME)

$(NAME):	$(OBJ)
			@$(CC) $(CFLAGS) $(LIBFT) $(OBJ) -o $(NAME)
			@echo "$(GREEN)minishell compiled!$(WHITE)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJF)
			@echo "$(CYAN)Compiling $(WHITE): $<"
			@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJF):
			@mkdir -p $(OBJ_DIR)

$(LIBFT):
			@git submodule init
			@git submodule update
			@cd lib/libft && $(MAKE)

clean:
			@$(RM) -rf $(OBJ_DIR)
			@make clean -C $(LIBFT)
			@echo "$(GREEN)minishell object files cleaned!$(WHITE)"

fclean:		clean
			@$(RM) -f $(NAME)
			@echo "$(GREEN)minishell executable files cleaned!$(WHITE)"

re:			fclean all
			@echo "$(GREEN)Cleaned and rebuilt everything for minishell!$(WHITE)"

.PHONY:		all clean fclean re
