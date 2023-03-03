#include "shell.h"

int	echo(char **stra)
{
	size_t	i;
	int		is_flagged;

	i = 0;
	is_flagged = ft_strncmp(stra[i], "-n", 3);
	if (stra == NULL)
		return (printf("\n"));
	if (!is_flagged)
		i++;
	while (stra && stra[i + 1] != NULL)
		printf("%s ", stra[i++]);
	if (stra[i] != NULL)
		printf("%s", stra[i]);
	if (!is_flagged)
		return (1);
	printf("\n");
	return (1);
}
