#include "shell.h"

static void	print_error(char **env);

int	ft_export(char ***env, char **options)
{
	size_t	i;
	size_t	j;
	char	*var_name;
	char	*var_value;

	i = 0;
	j = 0;
	var_name = NULL;
	var_value = NULL;
	if (!(*env) || !options)
		return (print_error(*env), 1);
	while (options[i] != NULL)
	{
		while (options[i][j] && options[i][j] != '=')
			j++;
		var_name = ft_substr(options[i], 0, j + 1);
		if (ft_strlen(options[i]) > (j + 1))
			var_value = ft_substr(options[i], j + 1, ft_strlen(options[i]));
		update_env(env, var_name, var_value);
		free(var_name);
		free(var_value);
		var_value = NULL;
		j = 0;
		i++;
	}
	return (0);
}

static void	print_error(char **env)
{
	size_t	i;

	i = 0;
	if (env == NULL)
		return ;
	while (env[i] != NULL)
		printf("declare -x %s\n", env[i++]);
}
