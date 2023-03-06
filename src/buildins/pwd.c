#include "shell.h"

int	ft_pwd(char **options)
{
	char	*cwd;

	if (ft_stra_len(options) > 0)
		return (ft_printf("pwd: too many arguments\n"), 1);
	cwd = NULL;
	cwd = getcwd(cwd, 1);
	ft_printf("%s\n", cwd);
	free(cwd);
	return (EXIT_SUCCESS);
}
