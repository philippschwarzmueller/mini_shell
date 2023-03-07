#include "shell.h"

int	ft_exit(t_list *commands, char ***env)
{
	ft_lstclear(&commands, free_cmd);
	ft_free_stra(*env);
	exit(0);
}
