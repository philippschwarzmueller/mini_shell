#include "shell.h"

static char	*get_prompt(void);

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
		input = get_prompt();
	else
		input = read_input(STDIN_FILENO);
	add_history(input);
	if (input == NULL)
	{
		clear_history();
		ft_free_stra(env);
		exit(g_exit_code);
	}
	return (input);
}

static char	*get_prompt(void)
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

char	*read_input(int fd)
{
	char	*input;
	char	buf;
	int		bytes;

	input = NULL;
	buf = 0;
	bytes = read(fd, &buf, 1);
	if (bytes < 1)
		return (NULL);
	while (bytes && buf != '\n')
	{
		input = str_append(input, buf);
		bytes = read(fd, &buf, 1);
		if (bytes < 0)
			return (free(input), NULL);
	}
	return (input);
}

char	*str_append(char *s1, char c)
{
	char	*ret;

	if (!c)
		return (s1);
	if (!s1)
		return (ret = ft_calloc(2, sizeof(char)), ret[0] = c, ret);
	ret = ft_calloc(ft_strlen(s1) + 1 + 1, sizeof(char));
	ft_memcpy(ret, s1, ft_strlen(s1));
	ret[ft_strlen(s1)] = c;
	free(s1);
	return (ret);
}

char	**get_environment(void)
{
	size_t		i;
	char		**res;
	extern char	**environ;

	i = 0;
	if (environ == NULL)
		return (NULL);
	res = malloc((ft_stra_len(environ) + 1) * sizeof(char *));
	while (environ[i] != NULL)
	{
		res[i] = ft_strdup(environ[i]);
		i++;
	}
	res[i] = NULL;
	return (res);
}
