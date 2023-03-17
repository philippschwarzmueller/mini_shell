#include "shell.h"

void	err(char *mess, int e_code, t_list *commands)
{
	char	*err;

	ft_lstclear(&commands, free_cmd);
	err = ft_strjoin("sigmashell: ", mess);
	ft_putendl_fd(err, 2);
	free(mess);
	free(err);
	exit(e_code);
}

char	**join_cmd(char *command, char **cmd)
{
	char	**res;
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_stra_len(cmd);
	res = ft_calloc((len + 2), sizeof(char *));
	res[0] = command;
	while (i++ < len)
		res[i] = cmd[i - 1];
	return (res);
}

void	dup_back(int orig_in, int orig_out, int *pip, int size)
{
	dup2(orig_in, 0);
	dup2(orig_out, 1);
	close(orig_in);
	close(orig_out);
	if (size == 0)
		return ;
	close(pip[1]);
	close(pip[0]);
}

void	wait_for_processes(pid_t last_pid, t_list *commands)
{
	if (!commands)
		return ;
	if ((runs_in_parent((t_command *)commands->content)
			&& ft_lstsize(commands) == 1) || ft_lstsize(commands) == 0)
		return ;
	waitpid(last_pid, &g_exit_code, 0);
	g_exit_code = WEXITSTATUS(g_exit_code);
	while (commands && commands->next)
	{
		wait(NULL);
		commands = commands->next;
	}
}

t_bool	runs_in_parent(t_command *command)
{
	char	*str;

	str = command->command;
	if (str == NULL)
		return (0);
	if (!ft_strncmp(str, "cd", 3))
		return (true);
	if (!ft_strncmp(str, "export", 7))
		return (true);
	if (!ft_strncmp(str, "unset", 6))
		return (true);
	if (!ft_strncmp(str, "exit", 5))
		return (true);
	return (false);
}
