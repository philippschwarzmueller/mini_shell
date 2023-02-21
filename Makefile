
NAME		= minishell
CC			= cc
LIBFT		= lib/libft/libft.a
READLINE	= lib/readline/lib/libreadline.a
RL_VERSION	= readline-8.1.2
CFLAGS		= -g -Wall -Werror -Wextra
LINK_FLAGS	= -L ./lib/readline/lib -lreadline -lhistory
INCLUDE		= -I ./lib/readline/include

GREEN		= \033[0;32m
CYAN		= \033[0;36m
WHITE		= \033[0m

SRC_FILES	= main lexer token
SRC_DIR		= src/
OBJ_DIR		= obj/
SRC			= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ			= $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
OBJD		= .cache_exists

all:		$(NAME)

$(NAME):	$(READLINE) $(LIBFT) $(OBJ)
			@$(CC) $(LIBFT) $(OBJ) $(LINK_FLAGS) -o $(NAME)
			@echo "$(GREEN)minishell compiled!$(WHITE)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJD)
			@echo "$(CYAN)Compiling $(WHITE): $<"
			@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJD):
			@mkdir -p $(OBJ_DIR)

$(LIBFT):
			@git submodule init
			@git submodule update
			@make -C lib/libft

$(READLINE):
			@curl -s https://ftp.gnu.org/gnu/readline/$(RL_VERSION).tar.gz --output lib/$(RL_VERSION).tar.gz
			@tar xfz lib/$(RL_VERSION).tar.gz -C lib
			@cd lib/$(RL_VERSION); ./configure --prefix=$(PWD)/lib/readline;
			@make install -C lib/$(RL_VERSION)
			@rm -rf lib/$(RL_VERSION)
			@rm -f lib/$(RL_VERSION).tar.gz
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
