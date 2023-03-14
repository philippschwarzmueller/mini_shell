#include "shell.h"

static char	**expand_options(char **options, char **env);
char		*ft_decrustify_str(char *str);
static void	restruct_opts(t_command **current, char **spl);

void	expand(t_list **command_table, char **env)
{
	t_list		*tmp;
	t_command	*current;
	char		**expanded_cmd;

	tmp = *command_table;
	while (tmp != NULL)
	{
		current = tmp->content;
		current->command = expand_string(current->command, env);
		current->command = ft_decrustify_str(current->command);
		expanded_cmd = ft_split(current->command, ' ');
		if (ft_stra_len(expanded_cmd) > 1)
			restruct_opts(&current, expanded_cmd);
		else
			ft_free_stra(expanded_cmd);
		current->options = expand_options(current->options, env);
		tmp = tmp->next;
	}
}

static char	**expand_options(char **options, char **env)
{
	size_t	i;

	i = 0;
	while (options && options[i] && i < ft_stra_len(options))
	{
		options[i] = expand_string(options[i], env);
		options[i] = ft_decrustify_str(options[i]);
		i++;
	}
	return (options);
}

char	*ft_decrustify_str(char *str)
{
	size_t		i;
	size_t		j;
	t_state_lex	state;
	char		*res;

	i = 0;
	j = 0;
	state = (t_state_lex){0, 0, 0, 0, 0};
	res = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	while (str[i])
	{
		if ((str[i] != '\"' || state.is_squoted || state.is_escaped)
			&& (str[i] != '\'' || state.is_dquoted || state.is_escaped)
			&& (str[i] != '\\' || state.is_escaped))
			res[j++] = str[i];
		state_change(str[i], &state);
		i++;
	}
	free(str);
	str = res;
	res = ft_strdup(str);
	return (free(str), res);
}

static void	restruct_opts(t_command **current, char **spl)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	**new_opts;

	i = 0;
	j = 0;
	len = ft_stra_len(spl) + ft_stra_len((*current)->options);
	new_opts = malloc(len * sizeof(char *));
	free((*current)->command);
	(*current)->command = spl[i];
	while (spl[++i] != NULL)
		new_opts[i - 1] = spl[i];
	i--;
	while ((*current)->options != NULL && ((*current)->options)[j] != NULL)
		new_opts[i++] = ((*current)->options)[j++];
	new_opts[i] = NULL;
	free((*current)->options);
	(*current)->options = new_opts;
	free(spl);
}
