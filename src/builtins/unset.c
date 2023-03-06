#include "shell.h"

static char	**remove_envvar(char **env, char *option);
static char	**realloc_env(char **env, size_t del);

int	ft_unset(char ***env, char **options)
{
	size_t	i;

	i = 0;
	if (!(*env) || !options)
		return (1);
	while (options[i] != NULL)
		*env = remove_envvar(*env, options[i++]);
	return (0);
}

static char	**remove_envvar(char **env, char *option)
{
	size_t	i;
	size_t	len;
	char	*var;

	i = 0;
	var = ft_strjoin(option, "=");
	len = ft_strlen(var);
	while (env[i] != NULL)
	{
		if (!ft_strncmp(env[i], var, len))
			return (free(var), realloc_env(env, i));
		i++;
	}
	free(var);
	return (env);
}

static char	**realloc_env(char **env, size_t del)
{
	size_t	i;
	size_t	j;
	char	**res;

	i = 0;
	j = 0;
	res = malloc(ft_stra_len(env) * sizeof(char *));
	while (env[i] != NULL)
	{
		if (i == del)
			free(env[i++]);
		else
			res[j++] = env[i++];
	}
	res[j] = NULL;
	free(env);
	return (res);
}
