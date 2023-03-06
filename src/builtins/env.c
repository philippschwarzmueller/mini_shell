#include "shell.h"

int	ft_env(char **env)
{
	size_t	i;

	i = 0;
	if (env == NULL)
		return (1);
	while (env[i] != NULL)
	{
		if (ft_strchr(env[i], '='))
			printf("%s\n", env[i]);
		i++;
	}
	return (0);
}
