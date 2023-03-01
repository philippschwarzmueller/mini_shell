#ifndef SHELL_H
# define SHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
# include <errno.h>
# include <termios.h>
# include "../lib/libft/libft.h"
# include "lexer.h"
# include "parser.h"

t_list			*lexing(char *str);
void			print_parsed_lst(t_list *lst);
void			print_lexed_lst(t_list *lst);
void			init_signalhandlers(void);
t_list			*parse(t_list *lexed_args);
t_list			*analyzer(char *str);

#endif
