#include "shell.h"

int	ft_exit(t_list *commands, char ***env)
{
	if (ft_lstsize(commands) > 1)
		return (EXIT_SUCCESS);
	ft_lstclear(&commands, free_cmd);
	ft_free_stra(*env);
	exit(EXIT_SUCCESS);
}
