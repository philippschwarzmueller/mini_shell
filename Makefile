
NAME		= minishell
CC			= cc
LIBFT		= lib/libft/libft.a
READLINE	= lib/readline/lib/libreadline.a
RL_VERSION	= readline-8.1.2
LINK_FLAGS	= -L ./lib/readline/lib -lreadline -lhistory #-fsanitize=address
INCLUDE		= -I ./lib/readline/include -I include/
CFLAGS		= -g -Wall -Werror -Wextra #-fsanitize=address

GREEN		= \033[0;32m
CYAN		= \033[0;36m
WHITE		= \033[0m

######## LEXER #############
LEXER_DIR		= src/lexer/
LEXER_SRC		= analyzer lexer_utils
LEXER			= $(addprefix $(LEXER_DIR), $(addsuffix .c, $(LEXER_SRC)))

######## PARSER ############
PARSER_DIR		= src/parser/
PARSER_SRC		= parser parser_utils state_utils file_error
PARSER			= $(addprefix $(PARSER_DIR), $(addsuffix .c, $(PARSER_SRC)))

######## EXPANDER #############
EXPANDER_DIR	= src/expander/
EXPANDER_SRC	= expander expander_utils expand_string
EXPANDER		= $(addprefix $(EXPANDER_DIR), $(addsuffix .c, $(EXPANDER_SRC)))

######## BUILDINS ############
BUILTINS_DIR	= src/builtins/
BUILTINS_SRC	= builtin_controller echo pwd cd env unset export exit
BUILTINS		= $(addprefix $(BUILTINS_DIR), $(addsuffix .c, $(BUILTINS_SRC)))

######## EXECUTOR ############
EXECUTOR_DIR	= src/executor/
EXECUTOR_SRC	= executor exec_utils
EXECUTOR		= $(addprefix $(EXECUTOR_DIR), $(addsuffix .c, $(EXECUTOR_SRC)))

######## SIGNAL ############
SIGNAL_DIR		= src/signal/
SIGNAL_SRC		= signal_handling
SIGNAL			= $(addprefix $(SIGNAL_DIR), $(addsuffix .c, $(SIGNAL_SRC)))

######## MAIN ##############
MAIN_DIR		= src/
MAIN_SRC		= main input
MAIN			= $(addprefix $(MAIN_DIR), $(addsuffix .c, $(MAIN_SRC)))

######## OBJ ###############
SRC_DIR			= src/
OBJ_DIR			= obj/
SRC				= $(MAIN) $(LEXER) $(SIGNAL) $(PARSER) $(EXECUTOR) $(BUILTINS) \
				  $(EXPANDER)
OBJ				= $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

all:		$(NAME)

$(NAME):	$(READLINE) $(LIBFT) $(OBJ_DIR) $(OBJ)
			@$(CC) $(LIBFT) $(OBJ) $(LINK_FLAGS) -o $(NAME)
			@echo "$(GREEN)minishell compiled!$(WHITE)"

LSANLIB = /LeakSanitizer/liblsan.a
lsan: CFLAGS += -ILeakSanitizer -Wno-gnu-include-next
lsan: LINK_FLAGS += -LLeakSanitizer -llsan -lc++
lsan: fclean $(LSANLIB)
lsan: all

$(LSANLIB):
	@if [ ! -d "LeakSanitizer" ]; then git clone https://github.com/mhahnFr/LeakSanitizer.git; fi
	@$(MAKE) -C LeakSanitizer

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
			@echo "$(CYAN)Compiling $(WHITE): $<"
			@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_DIR):
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
			@rm -rf lib/libft/.git
			@rm -rf lib/libft/.gitignore
			@rm -rf lib/libft/.github
			@echo "$(GREEN)minishell lib directory cleaned!$(WHITE)"

clean:
			@rm -rf $(OBJ_DIR)
			@echo "$(GREEN)minishell object files cleaned!$(WHITE)"

fclean:		clean
			@rm -f $(NAME)
			@echo "$(GREEN)minishell executable files cleaned!$(WHITE)"

re:			fclean all
			@echo "$(GREEN)Cleaned and rebuilt everything for minishell!$(WHITE)"

test:		$(NAME)
			cd tests && ./tester.sh m

.PHONY:		all clean fclean re
