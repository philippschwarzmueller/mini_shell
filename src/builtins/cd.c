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
