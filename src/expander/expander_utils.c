#include "shell.h"

char	*append_str(char *str, char *to_append, size_t i, size_t j)
{
	char	*append;

	if (to_append == NULL)
		return (ft_substr(str, j, i - j));
	append = ft_substr(str, j, i - j);
	to_append = ft_strjoin_f(to_append, append);
	free(append);
	return (to_append);
}

char	*append_value(char *to_append, char *name, char **env)
{
	char	*value;

	value = get_env_value(name, env);
	if (value == NULL)
		return (to_append);
	if (to_append == NULL)
		return (value);
	to_append = ft_strjoin_f(to_append, value);
	return (free(value), to_append);
}

char	*get_env_value(char *varname, char **env)
{
	char	*res;
	size_t	i;
	size_t	len;
	char	*value;

	i = 0;
	len = ft_strlen(varname);
	while (env && env[i] && i < ft_stra_len(env))
	{
		if (!ft_strncmp(varname, env[i], len)
			&& env[i][len] && env[i][len] == '=')
		{
			value = ft_strchr(env[i], '=') + 1;
			res = ft_strdup(value);
			return (free(varname), res);
		}
		i++;
	}
	return (free(varname), NULL);
}

void	state_change(char c, t_state_lex *state)
{
	if (c == '\"' && !(state->is_escaped)
		&& !(state->is_squoted) && !(state->is_dquoted))
		return ((void)(state->is_dquoted = true));
	if (c == '\'' && !(state->is_escaped)
		&& !(state->is_dquoted) && !(state->is_squoted))
		return ((void)(state->is_squoted = true));
	if ((c == '\'' && !(state->is_escaped) && !(state->is_dquoted)))
		state->is_squoted = false;
	if ((c == '\"' && !(state->is_escaped) && !(state->is_squoted)))
		state->is_dquoted = false;
	if (state->is_escaped)
		state->is_escaped = false;
	else if (c == '\\')
		state->is_escaped = true;
}

int	find_var_end(char c)
{
	int	is_whitespace;
	int	is_symbol;

	is_whitespace = (c == 32 || (c > 8 && c < 13));
	is_symbol = (c == '$' || c == '\'' || c == '\"' || c == '\\');
	return (is_whitespace || is_symbol);
}
