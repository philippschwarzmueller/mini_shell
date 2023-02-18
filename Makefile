
NAME		= minishell
CC			= cc
LIBFT		= lib/libft/libft.a
READLINE	= lib/readline/lib
RL_VERSION	= readline-8.1.2
CFLAGS		= -Wall -Werror -Wextra
RL_FLAGS	= -lreadline -L ./lib/readline/lib -I lib/readline/include

GREEN		= \033[0;32m
CYAN		= \033[0;36m
WHITE		= \033[0m

SRC_FILES	=
SRC_DIR		= src/
OBJ_DIR		= obj/
SRC			= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ			= $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
OBJD		= .cache_exists

all:		$(NAME)

$(NAME):	$(READLINE) $(LIBFT) $(OBJ)
			@$(CC) $(CFLAGS) $(RL_FLAGS) $(LIBFT) $(OBJ) -o $(NAME)
			@echo "$(GREEN)minishell compiled!$(WHITE)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJD)
			@echo "$(CYAN)Compiling $(WHITE): $<"
			@$(CC) $(CFLAGS) $(RL_FLAGS) -c $< -o $@

$(OBJD):
			@mkdir -p $(OBJ_DIR)

$(LIBFT):
			@git submodule init
			@git submodule update
			@cd lib/libft && $(MAKE)

$(READLINE):
			@curl -s https://ftp.gnu.org/gnu/readline/$(RL_VERSION).tar.gz --output lib/$(RL_VERSION).tar.gz
			@tar xfz lib/$(RL_VERSION).tar.gz -C lib
			@cd lib/$(RL_VERSION); ./configure --prefix=$(PWD)/lib/readline_out;
			@make install -C lib/$(RL_VERSION)
			@rm -rf lib/$(RL_VERSION)
			@rm -f lib/$(RL_VERSION).tar.gz
			@mv lib/readline_out lib/readline
			@echo "$(GREEN)readline compiled$(WHITE)"

readline:	$(READLINE)

clean:
			@rm -rf $(OBJ_DIR)
			@echo "$(GREEN)minishell object files cleaned!$(WHITE)"

fclean:		clean
			@rm -f $(NAME)
			@echo "$(GREEN)minishell executable files cleaned!$(WHITE)"

re:			fclean all
			@echo "$(GREEN)Cleaned and rebuilt everything for minishell!$(WHITE)"

.PHONY:		all clean fclean re
