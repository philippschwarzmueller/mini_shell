#include "shell.h"

static char	*append_value(char *to_append, char *name, char **env);
static char	*append_str(char *str, char *to_append, size_t i, size_t j);
static int	is_variable(char *str, size_t i, t_state_lex state);
static int	find_var_end(char c);

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

static char	*append_str(char *str, char *to_append, size_t i, size_t j)
{
	char	*append;

	if (to_append == NULL)
		return (ft_substr(str, j, i - j));
	append = ft_substr(str, j, i - j);
	to_append = ft_strjoin_f(to_append, append);
	free(append);
	return (to_append);
}

static char	*append_value(char *to_append, char *name, char **env)
{
	char	*value;

	if (!ft_strncmp(name, "?", 1))
	{
		value = ft_itoa(g_exit_code);
		if (ft_strlen(name) > 1)
			value = ft_strjoin_f(value, name + 1);
		free(name);
	}
	else
		value = remove_whitespaces(get_env_value(name, env));
	if (value == NULL)
		return (to_append);
	if (to_append == NULL || *to_append == 0)
		return (trim_front(value, " \t\n\v"));
	to_append = ft_strjoin_f(to_append, value);
	return (free(value), to_append);
}

static int	is_variable(char *str, size_t i, t_state_lex state)
{
	int	is_var;
	int	is_whitespcs;
	int	is_cut;
	int	is_aboarted;

	is_var = (str[i] == '$' && !state.is_squoted && !state.is_escaped);
	is_whitespcs = (str[i + 1] == 32 || (str[i + 1] > 8 && str[i + 1] < 13));
	is_cut = (str[i + 1] == '\\');
	is_aboarted = (!(is_whitespcs || is_cut) && !state.is_dquoted);
	return (is_var && is_aboarted && str[i + 1]);
}

static int	find_var_end(char c)
{
	int	is_whitespace;
	int	is_symbol;

	is_whitespace = (c == 32 || (c > 8 && c < 13));
	is_symbol = (c == '$' || c == '\'' || c == '\"' || c == '\\' || c == '/');
	return (is_whitespace || is_symbol);
}
