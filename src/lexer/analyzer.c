#include "shell.h"

static int		is_token(char c, t_state *state);
static void		word_or_operator(char c, t_state *state);
static void		check_if_quoted(char c, t_state *state);
static t_token	*tokenize(char *str, size_t i, size_t *len);

t_list	*analyzer(char *str)
{
	size_t	i;
	size_t	len;
	t_list	*lst;
	t_state	state;

	i = 0;
	len = 0;
	state = (t_state){0, 0, 0, 0, 0};
	lst = ft_lstnew(NULL);
	while (str[i])
	{
		if (is_token(str[i], &state) || !str[i + 1])
			ft_lstadd_back(&lst, ft_lstnew(tokenize(str, i, &len)));
		len++;
		i++;
	}
	if (state.is_dquoted || state.is_squoted)
	{
		ft_lstclear(&lst, del_token);
		ft_putendl_fd("error: unclosed quote", 2);
		return (free(str), NULL);
	}
	return (free(str), remove_val(&lst, NULL), lst);
}

static int	is_token(char c, t_state *state)
{
	int	cmp_word;
	int	cmp_operator;

	cmp_word = state->is_word;
	cmp_operator = state->is_operator;
	check_if_quoted(c, state);
	word_or_operator(c, state);
	if (state->is_dquoted || state->is_squoted)
		return (0);
	if (state->is_word != cmp_word || state->is_operator != cmp_operator)
		return (1);
	return (0);
}

static void	check_if_quoted(char c, t_state *state)
{
	if (state->is_escaped == 1)
		state->is_escaped = 0;
	if (c == '\\')
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

static void	word_or_operator(char c, t_state *state)
{
	if ((c == '|' || c == '<' || c == '>'))
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

static t_token	*tokenize(char *str, size_t i, size_t *len)
{
	t_token	*new;
	char	*pre_token;

	new = malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	if (!str[i + 1])
		i++;
	pre_token = ft_substr(str, (i - *len), *len);
	new->token = ft_strtrim(pre_token, " \f\t\n\r\v");
	free(pre_token);
	if (!(new->token)[0])
		return (free(new->token), free(new), NULL);
	if ((ft_strchr(str, '|') || ft_strchr(str, '<') || ft_strchr(str, '>'))
		&& (!ft_strchr(str, '\"') && !ft_strchr(str, '\'')))
		new->type = operation;
	else
		new->type = word;
	*len = 0;
	return (new);
}
