#include "shell.h"

static char	**expand_options(char **options, char **env);
static char	*ft_decrustify_str(char *str);
static int	is_variable(char *str, size_t i, t_state_lex state);
static int	find_var_end(char c);

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
		if (is_variable(str, i, state))
		{
			res = append_str(str, res, i, j);
			j = i + 1;
			while (str[j] && !find_var_end(str[j]))
				j++;
			res = append_value(res, ft_substr(str, i + 1, j - i - 1), env);
			i = j - 1;
			if (!str[i + 1])
				res = trim_back(res, " \t\n\v");
		}
		state_change(str[i++], &state);
	}
	return (free(str), append_str(str, res, i, j));
}

static int	is_variable(char *str, size_t i, t_state_lex state)
{
	int	is_var;
	int	is_whitespcs;
	int	is_cut;
	int is_aboarted;

	is_var = str[i] == '$' && !state.is_squoted && !state.is_escaped;
	is_whitespcs = (str[i + 1] == 32 || (str[i + 1] > 8 && str[i + 1] < 13));
	is_cut = (str[i + 1] == '\\');
	is_aboarted = !(is_whitespcs || is_cut) && !state.is_dquoted;
	return (is_var && is_aboarted && str[i + 1]);
}

static int	find_var_end(char c)
{
	int	is_whitespace;
	int	is_symbol;

	is_whitespace = (c == 32 || (c > 8 && c < 13));
	is_symbol = (c == '$' || c == '\'' || c == '\"' || c == '\\');
	return (is_whitespace || is_symbol);
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
