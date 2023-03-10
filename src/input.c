#include "shell.h"

char	*get_input(char **env)
{
	char	*input;

	if (isatty(STDIN_FILENO))
		input = readline("\033[0;31msigmashell \033[0;32m> \033[0;37m");
	else
		input = get_next_line(STDIN_FILENO);
	add_history(input);
	if (input == NULL)
	{
		ft_putstr_fd("\x1b[1A", STDOUT_FILENO);
		ft_putstr_fd("\033[13C", STDOUT_FILENO);
		ft_putendl_fd("exit", STDOUT_FILENO);
		clear_history();
		ft_free_stra(env);
		exit(EXIT_SUCCESS);
	}
	return (input);
}
