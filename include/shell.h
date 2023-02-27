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

typedef enum s_bool
{
	false,
	true,
}	t_bool;

struct s_state
{
	t_bool	pipe;
	t_bool	option;
	t_bool	command;
	t_bool	redirect;
	t_bool	last;
};

typedef struct s_command
{
	char	*path;
	char	*command;
	char	*options;
	int		in;
	int		out;
}	t_command;

t_list			*lexing(char *str);
void			tokenize_lst(t_list **lst);
void			print_lst(t_list *lst);
void			init_signalhandlers(void);
t_list			*parse(t_list *lexed_args);
struct s_state	init_state(void);
int				quote_count(char *str);
t_command		*create_cmd(char *command, char *options, int in, int out);
void			reset_cmd(char **command, char **options, int *in, int *out);
t_list			*analyzer(char *str);

#endif
