#ifndef LEX_H
# define LEX_H

# include "../lib/libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>

void	print_lst(t_list *lst);
t_list	*lexing(char *str);
void	tokenize_lst(t_list *lst);

#endif
