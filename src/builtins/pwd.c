#include "shell.h"

int	ft_pwd(char **options)
{
	char	*cwd;

	(void) options;
	cwd = NULL;
	cwd = getcwd(cwd, 1);
	if (cwd == NULL)
		return (EXIT_FAILURE);
	ft_printf("%s\n", cwd);
	free(cwd);
	return (EXIT_SUCCESS);
}
