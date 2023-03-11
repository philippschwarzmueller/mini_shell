#include "shell.h"

static char	*ft_readline(void);

/*
 * for bash replication add
 * ft_putstr_fd("\x1b[1A", STDOUT_FILENO);
 * ft_putstr_fd("\033[35C", STDOUT_FILENO);
 * ft_putendl_fd("exit", STDOUT_FILENO);
 * to the input == NULL statement
 */

char	*get_input(char **env)
{
	char	*input;

	if (isatty(STDIN_FILENO))
		input = ft_readline();
	else
		input = get_next_line(STDIN_FILENO);
	add_history(input);
	if (input == NULL)
	{
		clear_history();
		ft_free_stra(env);
		exit(g_exit_code);
	}
	return (input);
}

static char	*ft_readline(void)
{
	char	*path;
	char	*dir;
	char	*prompt;
	char	*res;

	path = NULL;
	path = getcwd(path, 1);
	dir = ft_strrchr(path, '/');
	prompt = ft_strjoin("\033[0;31msigmashell\033[0;35m grinding@", dir);
	if (g_exit_code)
		prompt = ft_strjoin_f(prompt, " \033[0;31m> \033[0;37m");
	else
		prompt = ft_strjoin_f(prompt, " \033[0;32m> \033[0;37m");
	res = readline(prompt);
	free(path);
	free(prompt);
	return (res);
}
