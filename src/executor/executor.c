#include "shell.h"

static void	change_src(int fd, int src);
static void	exec_cmd(t_command *current, char **env, int *pip, t_list *c);
static char	*get_path(char **env, char *arg);

void	executor(t_list	*commands, char **env)
{
	t_command	*current;
	pid_t		pid;
	int			pip[2];
	int			in;

	in = dup(0);
	while (commands != NULL)
	{
		current = (t_command *)commands->content;
		pipe(pip);
		if (current->in == 0 && commands->next)
			dup2(pip[0], 0);
		else if (commands->next)
			change_src(current->in, 0);
		else
			change_src(in, 0);
		pid = fork();
		if (pid == 0)
			exec_cmd(current, env, pip, commands);
		waitpid(0, NULL, WNOHANG);
		close(pip[0]);
		close(pip[1]);
		commands = commands->next;
	}
}

static void	change_src(int fd, int src)
{
	if (fd == src)
		return ;
	dup2(fd, src);
	close(fd);
}

static void	exec_cmd(t_command *current, char **env, int *pip, t_list *c)
{
	char	**cmd;
	char	*path;

	path = current->command;
	if (current->out == 1 && c->next != NULL)
		dup2(pip[1], 1);
	else
		change_src(current->out, 1);
	close(pip[1]);
	close(pip[0]);
	cmd = join_cmd(current->command, current->options);
	if (access(path, X_OK | F_OK) < 0)
		path = get_path(env, path);
	if (execve(path, cmd, env) == -1)
		err(ft_strjoin(current->command, ": command not found"), 127, cmd);
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
