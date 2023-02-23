#include "shell.h"

int	main(void)
{
	char	*input;
	t_list	*lst;

	lst = NULL;
	while (1)
	{
		init_signalhandlers();
		input = readline("\033[0;31msigmashell \033[0;32m> \033[0;37m");
		add_history(input);
		if (input == NULL)
		{
			rl_replace_line("TEST", 0);
			rl_redisplay();
			clear_history();
			exit(EXIT_SUCCESS);
		}
		lst = lexing(input);
		print_lst(lst);
		ft_lstclear(&lst, free);
	}
	return (EXIT_SUCCESS);
}

void	print_lst(t_list *lst)
{
	while (lst != NULL)
	{
		printf("%s\n", (char *)(lst->content));
		lst = lst->next;
	}
}
