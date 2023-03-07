#include "shell.h"

char	*expand_string(char *command, char **env);
char	*get_env_value(char *var, char **env);
char	**expand_options(char **options, char **env);

t_list	*expand(t_list *command_table, char **env)
{
	t_list		*res;
	t_list		*del;
	t_command	*temp;

	res = ft_lstnew(NULL);
	while (command_table != NULL)
	{
		temp = command_table->content;
		temp->command = expand_string(temp->command, env);
		temp->options = expand_options(temp->options, env);
		ft_lstadd_back(&res, ft_lstnew(temp));
		command_table = command_table->next;
	}
	del = res;
	res = res->next;
	ft_lstdelone(del, free);
	return (res);
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
