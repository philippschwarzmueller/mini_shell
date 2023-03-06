#include "shell.h"

void	err(char *mess, int exit_code, t_list *commands)
{
	char	*err;

	ft_lstclear(&commands, free_cmd);
	err = ft_strjoin("sigmashell: ", mess);
	ft_putendl_fd(err, 2);
	free(mess);
	free(err);
	exit(exit_code);
}

void	exit_builtin(t_list *commands)
{
	ft_lstclear(&commands, free_cmd);
	exit(1);
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

void	dup_back(int orig_in, int orig_out, int *pip)
{
	close(pip[0]);
	close(pip[1]);
	dup2(orig_in, 0);
	dup2(orig_out, 1);
	close(orig_in);
	close(orig_out);
}

t_bool	runs_in_parent(t_command *command)
{
	int	res;

	res = false;
	if (command == NULL)
		return (res);
	else if (!ft_strncmp(command->command, "cd", 3))
		res = true;
	else if (!ft_strncmp(command->command, "export", 7))
		res = true;
	else if (!ft_strncmp(command->command, "unset", 6))
		res = true;
	else if (!ft_strncmp(command->command, "env", 4))
		res = true;
	else if (!ft_strncmp(command->command, "exit", 5))
		res = true;
	return (res);
}
