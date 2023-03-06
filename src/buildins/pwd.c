#include "shell.h"

int	ft_pwd(char **options)
{
	char	*cwd;

	if (ft_stra_len(options) > 0)
		return (ft_printf("pwd: too many arguments\n"), EXIT_FAILURE);
	cwd = NULL;
	cwd = getcwd(cwd, 1);
	if (cwd == NULL)
		return (EXIT_FAILURE);
	ft_printf("%s\n", cwd);
	free(cwd);
	return (EXIT_SUCCESS);
}
