#include "shell.h"

static void	print_error(char **env);
static void	reset_loop(char *var_name, char **var_value, size_t *j);
static int	premature_exit(char *var_name, char *var_value);

int	ft_export(char ***env, char **options)
{
	size_t	i;
	size_t	j;
	char	*var_name;
	char	*var_value;

	i = -1;
	j = 0;
	var_name = NULL;
	var_value = NULL;
	if (!(*env) || !options)
		return (print_error(*env), EXIT_FAILURE);
	while (options[++i] != NULL)
	{
		while (options[i][j] && options[i][j] != '=')
			j++;
		var_name = ft_substr(options[i], 0, j + 1);
		if (ft_strncmp(var_name, "?", 1) == 0 || !ft_strncmp(var_name, "=", 1))
			return (premature_exit(var_name, var_value));
		if (ft_strlen(options[i]) > (j + 1))
			var_value = ft_substr(options[i], j + 1, ft_strlen(options[i]));
		update_env(env, var_name, var_value);
		reset_loop(var_name, &var_value, &j);
	}
	return (EXIT_SUCCESS);
}

static int	premature_exit(char *var_name, char *var_value)
{
	char	*error_msg;

	error_msg = ft_strjoin(var_name, " : not a valid identifier");
	ft_putendl_fd(error_msg, STDERR_FILENO);
	free(error_msg);
	free(var_name);
	free(var_value);
	return (EXIT_FAILURE);
}

static void	reset_loop(char *var_name, char **var_value, size_t *j)
{
	free(var_name);
	free(*var_value);
	*var_value = NULL;
	*j = 0;
}

static void	print_error(char **env)
{
	size_t	i;
	char	*str;

	i = 0;
	str = NULL;
	if (env == NULL)
		return ;
	while (env[i] != NULL)
	{
		str = ft_strjoin("declare -x ", env[i++]);
		ft_putendl_fd(str, 2);
		free(str);
	}
}
