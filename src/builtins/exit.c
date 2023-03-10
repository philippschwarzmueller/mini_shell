#include "shell.h"

int	ft_exit(t_command *cmd, t_list *commands, char ***env)
{
	if (ft_lstsize(commands) > 1)
		return (EXIT_SUCCESS);
	if (cmd->options)
	{
		if (cmd->options[0] && ft_strlen(cmd->options[0]) == 0)
		{
			ft_putendl_fd("exit: numeric argument required", STDERR_FILENO);
			exit(255);
		}
	}
	ft_lstclear(&commands, free_cmd);
	ft_free_stra(*env);
	exit(EXIT_SUCCESS);
}
