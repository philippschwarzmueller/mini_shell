#include "shell.h"

int	ft_cd(char **options)
{
	ft_printf("chdir return: %d\n", chdir(options[0]));
	ft_printf("hello from cd\n");
	return (EXIT_SUCCESS);
}
