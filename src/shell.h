#ifndef SHELL_H
# define SHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <signal.h>
# include <fcntl.h>
# include <errno.h>
# include <termios.h>
# include "../lib/libft/libft.h"

t_list	*lexing(char *str);
void	tokenize_lst(t_list **lst);
void	print_lst(t_list *lst);

#endif
