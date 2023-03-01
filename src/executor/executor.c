#include "shell.h"

static void	create_processes(char *infile, char **argv, char **env);
static void	exec_cmd(char **argv, char **env, int *src, int i);
static char	*get_path(char **env, char *arg);

int	main(int argc, char *argv[], char *env[])
{
	char	*infile;


	create_processes(infile, argv, env);
	return (0);
}

static void	create_processes(char *infile, char **argv, char **env)
{
	int		i;
	pid_t	pid;
	int		src[2];

	i = 1;
	while (argv[++i + 1])
	{
		if (pipe(src))
			err(ft_strdup("failed to create pipe"), 1, NULL);
		pid = fork();
		if (pid == -1)
			err(ft_strdup("failed o create subprocess"), 1, NULL);
		if (pid == 0 && infile != NULL)
			err(infile, 0, NULL);
		if (pid == 0)
			exec_cmd(argv, env, src, i);
		dup2(src[0], 0);
		close(src[0]);
		close(src[1]);
		waitpid(pid, NULL, WNOHANG);
		if (infile != NULL)
			free(infile);
		infile = NULL;
	}
}

static void	exec_cmd(char **argv, char **env, int *src, int i)
{
	char	**cmd;
	char	*path;

	path = argv[i];
	dup2(src[1], 1);
	close(src[1]);
	close(src[0]);
	if (argv[i + 2] == NULL)
		change_src(argv[i + 1], 1);
	cmd = ft_split(format_cmd(argv[i]), ' ');
	if (ft_arr_len(cmd) > 3)
		cmd = join_cmd(cmd);
	if (access(argv[i], X_OK | F_OK) < 0)
		path = get_path(env, cmd[0]);
	if (execve(path, cmd, env) == -1)
		err(ft_strjoin(cmd[0], ": command not found"), 127, cmd);
}

static char	*get_path(char **env, char *arg)
{
	char	**paths;
	char	*res;
	int		i;

	i = 0;
	res = NULL;
	while (*env && ft_strncmp(*env, "PATH=", 5))
		env++;
	if (*env == NULL)
		return (NULL);
	paths = ft_split(*env + 5, ':');
	while (paths && paths[i])
	{
		res = ft_strjoin(paths[i++], "/");
		res = ft_strjoin_alt(res, arg);
		if (!access(res, X_OK | F_OK))
			return (ft_free_arr(paths), res);
		free(res);
	}
	return (ft_free_arr(paths), NULL);
}






