#include "shell.h"

int	ft_exit(t_command *cmd, t_list *commands, char ***env)
{
	int	exit_code;

	if (ft_lstsize(commands) > 1)
		return (EXIT_SUCCESS);
	if (cmd->options)
	{
		if (cmd->options[0] && ft_strlen(cmd->options[0]) == 0)
		{
			ft_putendl_fd("exit: numeric argument required", STDERR_FILENO);
			exit(255);
		}
		else if (ft_stra_len(cmd->options) > 1)
		{
			ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
		exit_code = ft_atoi(cmd->options[0]);
		if (exit_code >= 0 && exit_code < 256)
			exit(exit_code);
	}
	ft_lstclear(&commands, free_cmd);
	ft_free_stra(*env);
	exit(EXIT_SUCCESS);
}
