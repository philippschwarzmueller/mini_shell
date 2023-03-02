#include "shell.h"

static void	dup_input(t_list *commands, int in, int *pip);
static void	dup_output(t_list *commands, int out, int *pip);
static void	exec_cmd(t_command *current, char **env);
static char	*get_path(char **env, char *arg);

void	executor(t_list	*commands, char **env)
{
	pid_t	pid;
	int		pip[2];
	int		orig_in;
	int		orig_out;

	orig_in = dup(0);
	orig_out = dup(1);
	while (commands != NULL)
	{
		dup_input(commands, orig_in, pip);
		pipe(pip);
		pid = fork();
		if (pid == 0)
		{
			dup_output(commands, orig_out, pip);
			exec_cmd((t_command *)commands->content, env);
		}
		waitpid(0, NULL, 0);
		commands = commands->next;
	}
	dup2(orig_in, 0);
	dup2(orig_out, 1);
	close(orig_in);
	close(orig_out);
}

static void	dup_input(t_list *commands, int in, int *pip)
{
	t_command	*current;
	static int	first = 1;

	current = (t_command *)commands->content;
	if (current->in == 0 && !first)
		dup2(pip[0], 0);
	else if (current->in == 0 && first)
		dup2(in, 0);
	else
		dup2(current->in, 0);
	if (current->in > 1)
		close(current->in);
	close(pip[0]);
	close(pip[1]);
	first = 0;
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
	if (current->in > 1)
		close(current->out);
	close(pip[0]);
	close(pip[1]);
}

static void	exec_cmd(t_command *current, char **env)
{
	char	**cmd;
	char	*path;

	path = current->command;
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
