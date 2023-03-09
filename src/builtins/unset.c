#include "shell.h"

static char	**remove_envvar(char **env, char *option);
static char	**realloc_env(char **env, size_t del);

int	ft_unset(char ***env, char **options)
{
	size_t	i;
	char	*error;

	i = 0;
	error = NULL;
	if (!(*env) || !options)
		return (EXIT_FAILURE);
	while (options[i] != NULL)
	{
		if (ft_strchr(options[i], '='))
		{
			error = ft_strjoin("sigmashell: unset: `", options[i++]);
			error = ft_strjoin_f(error, "': not a valid identifier");
			ft_putendl_fd(error, 2);
			free(error);
		}
		else
			*env = remove_envvar(*env, options[i++]);
	}
	return (EXIT_SUCCESS);
}

static char	**remove_envvar(char **env, char *option)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(option);
	while (env[i] != NULL)
	{
		if (!ft_strncmp(env[i], option, len) && env[i][len - 1]
			&& (env[i][len] == '=' || env[i][len] == 0))
			return (printf("test\n"), realloc_env(env, i));
		i++;
	}
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
