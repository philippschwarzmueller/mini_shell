#include "shell.h"

int	ft_cd(char **options, char ***env)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = getcwd(NULL, 1);
	if (!options || ft_strlen(options[0]) == 0)
	{
		new_pwd = ft_strdup("HOME");
		new_pwd = get_env_value(new_pwd, *env);
		if (chdir(new_pwd) != 0)
			return (free(old_pwd), EXIT_FAILURE);
		update_env(env, "OLDPWD=", old_pwd);
		update_env(env, "PWD=", new_pwd);
		return (free(old_pwd), EXIT_SUCCESS);
	}
	else if (chdir(options[0]) != 0)
	{
		ft_putstr_fd(options[0], STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		return (free(old_pwd), EXIT_FAILURE);
	}
	new_pwd = getcwd(NULL, 1);
	update_env(env, "OLDPWD=", old_pwd);
	update_env(env, "PWD=", new_pwd);
	return (free(old_pwd), free(new_pwd), EXIT_SUCCESS);
}
