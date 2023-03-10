#include "shell.h"

static char	**expand_options(char **options, char **env);
static char	*ft_decrustify_str(char *str);

void	expand(t_list **command_table, char **env)
{
	t_list		*tmp;
	t_command	*current;

	tmp = *command_table;
	while (tmp != NULL)
	{
		current = tmp->content;
		current->command = expand_string(current->command, env);
		current->command = ft_decrustify_str(current->command);
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

char	*expand_string(char *str, char **env)
{
	size_t		i;
	size_t		j;
	char		*res;
	t_state_lex	state;

	i = 0;
	j = 0;
	res = NULL;
	state = (t_state_lex){0, 0, 0, 0, 0};
	while (str[i])
	{
		if (str[i] == '$' && !state.is_squoted && !state.is_escaped)
		{
			res = append_str(str, res, i, j);
			j = i + 1;
			while (str[j] && !find_var_end(str[j]))
				j++;
			res = append_value(res, ft_substr(str, i + 1, j - i - 1), env);
			i = j - 1;
		}
		state_change(str[i], &state);
		i++;
	}
	return (free(str), append_str(str, res, i, j));
}

static char	*ft_decrustify_str(char *str)
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
