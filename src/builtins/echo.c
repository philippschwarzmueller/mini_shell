#include "shell.h"

int	ft_echo(char **stra)
{
	size_t	i;

	i = 0;
	if (stra == NULL)
		return (printf("\n"));
	while (stra[i] && !ft_strncmp(stra[i], "-n", 3))
		i++;
	while (stra && stra[i + 1] != NULL)
		printf("%s ", stra[i++]);
	if (stra[i] != NULL)
		printf("%s", stra[i]);
	if (!ft_strncmp(stra[0], "-n", 3))
		return (1);
	printf("\n");
	return (EXIT_SUCCESS);
}
