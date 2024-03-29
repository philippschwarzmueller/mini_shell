#include "shell.h"

static int		is_token(char *str, size_t i, t_state_lex *state, size_t *len);
static void		change_state(char c, t_state_lex *state);
static int		check_next_char(char c, t_state_lex *state);
static t_token	*tokenize(char *str, size_t i, size_t *len);

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
	while (str && str[i])
	{
		if (is_token(str, i, &state, &len))
			ft_lstadd_back(&lst, ft_lstnew(tokenize(str, i, &len)));
		i++;
	}
	if (state.is_dquoted || state.is_squoted || state.is_escaped)
		return (quotation_error(lst, str), NULL);
	del_first(&lst);
	free(str);
	if (check_token_syntax(lst) == EXIT_FAILURE)
		return (g_exit_code = 2, ft_lstclear(&lst, del_token), NULL);
	return (lst);
}

static int	is_token(char *str, size_t i, t_state_lex *state, size_t *len)
{
	change_state(str[i], state);
	if (state->is_escaped)
		state->is_escaped = false;
	else if (str[i] == '\\')
		state->is_escaped = true;
	if (!(str[i] == 32 || (str[i] >= 8 && str[i] <= 13))
		|| (state->is_squoted) || (state->is_dquoted))
		*len += 1;
	return (check_next_char(str[i + 1], state));
}

static void	change_state(char c, t_state_lex *state)
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
	if ((c == '|' || c == '<' || c == '>') && !(state->is_escaped))
	{
		state->is_operator = true;
		state->is_word = false;
	}
	if (!(c == 32 || (c >= 8 && c <= 13)) && (c != '|' && c != '<' && c != '>'))
	{
		state->is_operator = false;
		state->is_word = true;
	}
	if ((c == 32 || (c >= 8 && c <= 13)))
	{
		state->is_operator = false;
		state->is_word = false;
	}
}

static int	check_next_char(char c, t_state_lex *state)
{
	if (c == 0 && (state->is_word || state->is_operator))
		return (1);
	if (state->is_dquoted || state->is_squoted)
		return (0);
	if ((c == '|' || c == '<' || c == '>') && state->is_word
		&& !(state->is_escaped))
		return (1);
	if (!(c == 32 || (c >= 8 && c <= 13))
		&& !(c == '|' || c == '<' || c == '>') && state->is_operator)
		return (1);
	if ((c == 32 || (c >= 8 && c <= 13))
		&& (state->is_word || state->is_operator))
		return (1);
	return (0);
}

static t_token	*tokenize(char *str, size_t i, size_t *len)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	new->token = ft_substr(str, ((i + 1) - *len), *len);
	new->type = word;
	set_type(new);
	*len = 0;
	if (new->token[0] == 0)
		return (del_token(new), NULL);
	return (new);
}
