#include "shell.h"

char	*expand_string(char *command, char **env);
char	*get_env_value(char *var, char **env);
char	**expand_options(char **options, char **env);

void	expand(t_list **command_table, char **env)
{
	t_list		*tmp;
	t_command	*current;

	tmp = *command_table;
	while (tmp != NULL)
	{
		current = tmp->content;
		current->command = expand_string(current->command, env);
		current->options = expand_options(current->options, env);
		tmp = tmp->next;
	}
}

char	**expand_options(char **options, char **env)
{
	size_t	i;

	i = 0;
	while (options && options[i] && i < ft_stra_len(options))
	{
		options[i] = expand_string(options[i], env);
		i++;
	}
	return (options);
}

char	*expand_string(char *command, char **env)
{
	char	*var;
	char	*temp;

	var = ft_strchr(command, '$');
	if (var == 0)
		return (command);
	var++;
	var = ft_strdup(var);
	temp = command;
	command = get_env_value(var, env);
	if (command != NULL)
		free(temp);
	else
		command = temp;
	free(var);
	return (command);
}

char	*get_env_value(char *varname, char **env)
{
	char	*res;
	size_t	i;
	char	*value;

	i = 0;
	while (env && env[i] && i < ft_stra_len(env))
	{
		if (ft_strncmp(varname, env[i], ft_strlen(varname)) == 0)
		{
			value = ft_strchr(env[i], '=') + 1;
			res = ft_strdup(value);
			return (res);
		}
		i++;
	}
	return (NULL);
}
