#include "shell.h"

static int	is_token(char *str, size_t i, t_state_lex *state, size_t *len);
static void	check_if_quoted(char c, t_state_lex *state);
static void	change_state(char c, t_state_lex *state);
static int	check_next_char(char c, t_state_lex *state);

t_list	*analyzer(char *str)
{
	size_t		i;
	size_t		len;
	t_list		*lst;
	t_state_lex	state;

	i = 0;
	len = 0;
	state = (t_state_lex){0, 0, 0, 0, 0};
	lst = ft_lstnew(NULL);
	while (str[i])
	{
		if (is_token(str, i, &state, &len))
			ft_lstadd_back(&lst, ft_lstnew(tokenize(str, i, &len)));
		i++;
	}
	if (state.is_dquoted || state.is_squoted)
	{
		ft_lstclear(&lst, del_token);
		ft_putendl_fd("error: unclosed quote", 2);
		return (free(str), NULL);
	}
	remove_val(&lst, NULL);
	return (free(str), lst);
}

static int	is_token(char *str, size_t i, t_state_lex *state, size_t *len)
{
	check_if_quoted(str[i], state);
	change_state(str[i], state);
	if (!(str[i] == 32 || (str[i] >= 8 && str[i] <= 13))
		|| (state->is_squoted) || (state->is_dquoted))
		*len += 1;
	if (state->is_escaped)
		str[i] = ' ';
	return (check_next_char(str[i + 1], state));
}

static void	check_if_quoted(char c, t_state_lex *state)
{
	if (state->is_escaped)
		state->is_escaped = 0;
	else if (c == '\\')
		state->is_escaped = 1;
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
}

static void	change_state(char c, t_state_lex *state)
{
	if ((c == '|' || c == '<' || c == '>' && !(state->is_escaped)))
	{
		state->is_operator = 1;
		state->is_word = 0;
	}
	if (!(c == 32 || (c >= 8 && c <= 13))
		&& (c != '|' && c != '<' && c != '>'))
	{
		state->is_operator = 0;
		state->is_word = 1;
	}
	if ((c == 32 || (c >= 8 && c <= 13)))
	{
		state->is_operator = 0;
		state->is_word = 0;
	}
}

static int	check_next_char(char c, t_state_lex *state)
{
	if (c == 0)
		return (1);
	if (state->is_dquoted || state->is_squoted)
		return (0);
	if ((c == '|' || c == '<' || c == '>') && state->is_word)
		return (1);
	if (!(c == 32 || (c >= 8 && c <= 13))
		&& !(c == '|' || c == '<' || c == '>') && state->is_operator)
		return (1);
	if ((c == 32 || (c >= 8 && c <= 13))
		&& (state->is_word || state->is_operator))
		return (1);
	return (0);
}
