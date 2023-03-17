#include "shell.h"

static void	dup_input(t_list *commands, t_list *cmp, int *pip);
static void	dup_output(t_list *commands, int out, int *pip, char **env);
static void	exec_cmd(t_list *commands, t_command *current, char **env);
static char	*get_path(char **env, char *arg);

void	executor(t_list	*commands, char ***env)
{
	pid_t	pid;
	t_list	*tmp;
	int		pip[2];
	int		orig_in;
	int		orig_out;

	orig_in = dup(0);
	orig_out = dup(1);
	tmp = commands;
	pid = 1;
	while (tmp != NULL)
	{
		dup_input(tmp, commands, pip);
		pipe(pip);
		if (!builtin_controller_parent(commands, tmp->content, env))
			pid = fork();
		if (pid == 0)
		{
			dup_output(tmp, orig_out, pip, *env);
			exec_cmd(commands, (t_command *)tmp->content, *env);
		}
		tmp = tmp->next;
	}
	dup_back(orig_in, orig_out, pip, ft_lstsize(commands));
	wait_for_processes(pid, commands);
}

static void	dup_input(t_list *commands, t_list *cmp, int *pip)
{
	t_command	*current;

	current = (t_command *)commands->content;
	if (current->in == 0 && commands == cmp)
		return ;
	if (current->in == 0)
		dup2(pip[0], 0);
	else if (current->in > 1)
		dup2(current->in, 0);
	if (current->in > 2)
		close(current->in);
	if (!(commands == cmp))
	{
		close(pip[0]);
		close(pip[1]);
	}
}

static void	dup_output(t_list *commands, int out, int *pip, char **env)
{
	t_command	*current;

	current = (t_command *)commands->content;
	if (current->out == -1 || current->in == -1)
	{
		ft_free_stra(env);
		ft_lstclear(&commands, free_cmd);
		exit(EXIT_FAILURE);
	}
	if (current->out == 1 && commands->next)
		dup2(pip[1], 1);
	else if (current->out == 1 && !commands->next)
		dup2(out, 1);
	else
		dup2(current->out, 1);
	if (current->out > 1)
		close(current->out);
	close(pip[1]);
	close(pip[0]);
	close(out);
}

static void	exec_cmd(t_list *ct, t_command *current, char **env)
{
	char	**cmd;
	char	*path;

	init_child_sig_handler();
	if (builtin_controller_child(current, env) || ft_strncmp(current->command,
			"unset", 6) == 0 || ft_strncmp(current->command, "export", 7) == 0)
	{
		ft_free_stra(env);
		ft_lstclear(&ct, free_cmd);
		exit(g_exit_code);
	}
	path = current->command;
	cmd = join_cmd(current->command, current->options);
	if (access(path, X_OK | F_OK) < 0
		&& ft_strncmp(current->command, "./", 2)
		&& ft_strncmp(current->command, "/", 1))
		path = get_path(env, path);
	if (execve(path, cmd, env) == -1)
	{
		free(cmd);
		ft_free_stra(env);
		if (!access(path, F_OK) && access(path, X_OK) < 0)
			err(ft_strjoin(current->command, ": permission denied"), 126, ct);
		err(ft_strjoin(current->command, ": command not found"), 127, ct);
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
		return (arg);
	paths = ft_split(*env + 5, ':');
	while (paths && paths[i])
	{
		res = ft_strjoin(paths[i++], "/");
		res = ft_strjoin_f(res, arg);
		if (!access(res, X_OK | F_OK))
			return (ft_free_stra(paths), res);
		free(res);
	}
	return (ft_free_stra(paths), arg);
}
