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
# include "expander.h"
# include "builtins.h"
# include "executor.h"

int	g_exit_code;

void	print_parsed_lst(t_list *lst);
void	print_lexed_lst(t_list *lst);
void	init_signalhandlers(void);
t_list	*analyzer(char *str);
t_list	*parse(t_list *lexed_arg, char **env);
void	expand(t_list **command_table, char **env);
int		builtin_controller_parent(t_list *cmds, t_command *cmd, char ***env);
int		builtin_controller_child(t_command *cmd, char **env);
void	executor(t_list	*commands, char ***env);

char	*expand_string(char *str, char **env);

#endif
