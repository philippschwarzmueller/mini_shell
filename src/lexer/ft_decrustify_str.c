#include "shell.h"

static void	state_change(char c, t_state_lex *state);

char	*ft_decrustify_str(char *str)
{
	size_t		i;
	size_t		j;
	t_state_lex	state;
	char		*res;

	i = 0;
	j = 0;
	state = (t_state_lex){0, 0, 0, 0, 0};
	res = ft_calloc(ft_strlen(str), sizeof(char));
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

static void	state_change(char c, t_state_lex *state)
{
	if (c == '\"' && !(state->is_escaped)
		&& !(state->is_squoted) && !(state->is_dquoted))
		return ((void)(state->is_dquoted = 1));
	if (c == '\'' && !(state->is_escaped)
		&& !(state->is_dquoted) && !(state->is_squoted))
		return ((void)(state->is_squoted = 1));
	if ((c == '\'' && !(state->is_escaped) && !(state->is_dquoted)))
		state->is_squoted = 0;
	if ((c == '\"' && !(state->is_escaped) && !(state->is_squoted)))
		state->is_dquoted = 0;
	if (state->is_escaped)
		state->is_escaped = 0;
	else if (c == '\\')
		state->is_escaped = 1;
}
