#include "shell.h"

int		update_env(char **env, char *varname, char *value);
char	**add_to_environment(char **env, char *varname, char *value);

int	ft_cd(char **options, char **env)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = getcwd(NULL, 1);
	if (!options || !options[0] || chdir(options[0]) != 0)
		return (EXIT_FAILURE);
	new_pwd = getcwd(NULL, 1);
	update_env(env, "OLDPWD=", old_pwd);
	update_env(env, "PWD=", new_pwd);
	free(old_pwd);
	free(new_pwd);
	return (EXIT_SUCCESS);
}

int	update_env(char **env, char *varname, char *value)
{
	size_t	i;

	i = 0;
	while (env && env[i] && i < ft_stra_len(env))
	{
		if (ft_strncmp(varname, env[i], ft_strlen(varname)) == 0)
			env[i] = ft_strdup(value);
		i++;
	}
	if (env && env[i] && ft_strncmp(varname, env[i], ft_strlen(varname)))
			env = add_to_environment(env, varname, value);
	return (EXIT_SUCCESS);
}

char	**add_to_environment(char **env, char *varname, char *value)
{
	size_t		i;
	char		**res;

	i = 0;
	if (env == NULL)
		return (NULL);
	res = malloc((ft_stra_len(env) + 2) * sizeof(char *));
	while (env[i] != NULL)
	{
		res[i] = ft_strdup(env[i]);
		free(env[i]);
		i++;
	}
	res[i] = ft_strjoin(varname, value);
	i++;
	res[i] = NULL;
	free(env);
	return (res);
}
