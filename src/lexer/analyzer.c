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
	while (str[i])
	{
		if (is_token(str, i, &state, &len))
			ft_lstadd_back(&lst, ft_lstnew(tokenize(str, i, &len)));
		i++;
	}
	if (state.is_dquoted || state.is_squoted || state.is_escaped)
	{
		ft_lstclear(&lst, del_token);
		ft_putendl_fd("sigmashell: unclosed quote", 2);
		return (free(str), NULL);
	}
	del_first(&lst);
	return (free(str), lst);
}

static int	is_token(char *str, size_t i, t_state_lex *state, size_t *len)
{
	change_state(str[i], state);
	if (state->is_escaped)
		state->is_escaped = 0;
	else if (str[i] == '\\')
		state->is_escaped = 1;
	if (!(str[i] == 32 || (str[i] >= 8 && str[i] <= 13))
		|| (state->is_squoted) || (state->is_dquoted))
		*len += 1;
	return (check_next_char(str[i + 1], state));
}

static void	change_state(char c, t_state_lex *state)
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
	if ((c == '|' || c == '<' || c == '>') && !(state->is_escaped))
	{
		state->is_operator = 1;
		state->is_word = 0;
	}
	if (!(c == 32 || (c >= 8 && c <= 13)) && (c != '|' && c != '<' && c != '>'))
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
	if (ft_strchr(new->token, '\"') || ft_strchr(new->token, '\'')
		|| ft_strchr(new->token, '\\'))
		new->token = ft_decrustify_str(new->token);
	*len = 0;
	if (new->token[0] == 0)
		return (del_token(new), NULL);
	return (new);
}
