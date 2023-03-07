#include "shell.h"

int	ft_env(char **env)
{
	size_t	i;

	i = 0;
	if (env == NULL)
		return (EXIT_FAILURE);
	while (env[i] != NULL)
	{
		if (ft_strchr(env[i], '='))
			printf("%s\n", env[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
