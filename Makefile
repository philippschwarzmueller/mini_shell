
NAME		= minishell
CC			= cc
LIBFT		= lib/libft/libft.a
READLINE	= lib/readline/lib/libreadline.a
RL_VERSION	= readline-8.1.2
LINK_FLAGS	= -L ./lib/readline/lib -lreadline -lhistory
INCLUDE		= -I ./lib/readline/include -I include/
CFLAGS		= -g -Wall -Werror -Wextra

GREEN		= \033[0;32m
CYAN		= \033[0;36m
WHITE		= \033[0m

######## LEXER ############
LEXER_SRC	= lexer token quotes
LEXER_DIR	= src/lexer/
LEXER		= $(addprefix $(LEXER_DIR), $(addsuffix .c, $(LEXER_SRC)))

######## PARSER ############
PARSER_SRC	= parser
PARSER_DIR	= src/parser/
PARSER		= $(addprefix $(PARSER_DIR), $(addsuffix .c, $(PARSER_SRC)))

######## SIGNAL ############
SIGNAL_SRC	= signal_handling
SIGNAL_DIR	= src/signal/
SIGNAL		= $(addprefix $(SIGNAL_DIR), $(addsuffix .c, $(SIGNAL_SRC)))

######## MAIN ##############
MAIN_SRC	= main
MAIN_DIR	= src/
MAIN		= $(addprefix $(MAIN_DIR), $(addsuffix .c, $(MAIN_SRC)))

######## OBJ ###############
SRC_DIR		= src/
OBJ_DIR		= obj/
SRC			= $(MAIN) $(LEXER) $(SIGNAL) $(PARSER)
OBJ			= $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))
OBJD		= .cache_exists

all:		$(NAME)

$(NAME):	$(READLINE) $(LIBFT) $(OBJ)
			@$(CC) $(LIBFT) $(OBJ) $(LINK_FLAGS) -o $(NAME)
			@echo "$(GREEN)minishell compiled!$(WHITE)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJD)
			@echo "$(CYAN)Compiling $(WHITE): $<"
			@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJD):
			@mkdir -p $(dir $(OBJ))

$(LIBFT):
			@git submodule init
			@git submodule update
			@make -C lib/libft
			@echo "$(GREEN)libft compiled!$(WHITE)"

$(READLINE):
			@curl -s https://ftp.gnu.org/gnu/readline/$(RL_VERSION).tar.gz --output lib/$(RL_VERSION).tar.gz
			@tar xfz lib/$(RL_VERSION).tar.gz -C lib
			@cd lib/$(RL_VERSION); ./configure --prefix=$(PWD)/lib/readline;
			@make install -C lib/$(RL_VERSION)
			@rm -rf lib/$(RL_VERSION)
			@rm -f lib/$(RL_VERSION).tar.gz
			@echo "$(GREEN)readline compiled!$(WHITE)"

readline:	$(READLINE)

libclean:
			@rm -rf lib/readline
			@rm -rf lib/libft/*

clean:
			@rm -rf $(OBJ_DIR)
			@echo "$(GREEN)minishell object files cleaned!$(WHITE)"

fclean:		clean
			@rm -f $(NAME)
			@echo "$(GREEN)minishell executable files cleaned!$(WHITE)"

re:			fclean all
			@echo "$(GREEN)Cleaned and rebuilt everything for minishell!$(WHITE)"

.PHONY:		all clean fclean re
