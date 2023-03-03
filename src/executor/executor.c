#include "shell.h"

static void	dup_input(t_list *commands, int *pip);
static void	dup_output(t_list *commands, int out, int *pip);
static void	exec_cmd(t_list *commands, t_command *current, char **env);
static char	*get_path(char **env, char *arg);

void	executor(t_list	*commands, char **env)
{
	pid_t	pid;
	t_list	*tmp;
	int		pip[2];
	int		orig_in;
	int		orig_out;

	orig_in = dup(0);
	orig_out = dup(1);
	tmp = commands;
	while (tmp != NULL)
	{
		dup_input(tmp, pip);
		pipe(pip);
		pid = fork();
		if (pid == 0)
		{
			close(orig_in);
			dup_output(tmp, orig_out, pip);
			exec_cmd(commands, (t_command *)tmp->content, env);
		}
		waitpid(0, NULL, 0);
		tmp = tmp->next;
	}
	close(pip[0]);
	close(pip[1]);
	dup_back(orig_in, orig_out);
}

static void	dup_input(t_list *commands, int *pip)
{
	t_command	*current;

	current = (t_command *)commands->content;
	if (current->in == 0)
		dup2(pip[0], 0);
	else
		dup2(current->in, 0);
	if (current->in > 1)
		close(current->in);
	close(pip[0]);
	close(pip[1]);
}

static void	dup_output(t_list *commands, int out, int *pip)
{
	t_command	*current;

	current = (t_command *)commands->content;
	if (current->out == 1 && commands->next)
		dup2(pip[1], 1);
	else if (current->out == 1 && !commands->next)
	{
		dup2(out, 1);
		close(out);
	}
	else
		dup2(current->out, 1);
	if (current->out > 1)
		close(current->out);
	//close(pip[0]);
	close(pip[1]);
}

static void	exec_cmd(t_list *commands, t_command *current, char **env)
{
	char	**cmd;
	char	*path;
	int		i;

	i = 0;
	if (buildin_controller(current, env))
		exit_buildin(commands);
	path = current->command;
	cmd = join_cmd(current->command, current->options);
	if (access(path, X_OK | F_OK) < 0)
		path = get_path(env, path);
	if (execve(path, cmd, env) == -1)
	{
		free(cmd);
		err(ft_strjoin(current->command, ": command not found"), 127, commands);
	}
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
		res = ft_strjoin_f(res, arg);
		if (!access(res, X_OK | F_OK))
			return (ft_free_stra(paths), res);
		free(res);
	}
	return (ft_free_stra(paths), NULL);
}
