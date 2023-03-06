#include "shell.h"

int	ft_cd(char **options)
{
	if (!options || !options[0])
		return (EXIT_FAILURE);
	ft_printf("chdir return: %d\n", chdir(options[0]));
	ft_printf("hello from cd\n");
	return (EXIT_SUCCESS);
}
