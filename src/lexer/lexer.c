#include "shell.h"

static int		is_token(char c, t_state *state);
static void		analyse_char(char c, t_state *state);
static t_token	*tokenize(char *str, size_t i, size_t len);

t_list	*analyzer(char *str)
{
	size_t	i;
	size_t	len;
	t_list	*lst;
	t_list	*del;
	t_state	state;

	i = 0;
	len = 0;
	state = (t_state){0, 0, 0, 0, 0};
	lst = ft_lstnew(NULL);
	while (str[i])
	{
		if (is_token(str[i], &state))
			ft_lstadd_back(&lst, ft_lstnew(tokenize(str, i, len)));
		if (is_token(str[i], &state))
			len = 0;
		len++;
		i++;
	}
	free(str);
	del = lst;
	lst = lst->next;
	ft_lstdelone(del, free);
	return (lst);
}

static int	is_token(char c, t_state *state)
{
	int	cmp_word;
	int	cmp_operator;

	cmp_word = state->is_word;
	cmp_operator = state->is_operator;
	analyse_char(c, state);
	if (state->is_word != cmp_word || state->is_operator != cmp_operator)
		return (1);
	return (0);
}

static void	analyse_char(char c, t_state *state)
{
	if (state->is_escaped == 1)
		state->is_escaped = 0;
	if (c == '\\')
		state->is_escaped = 1;
	if ((c == '\"' && !(state->is_escaped) && !(state->is_squoted)))
		state->is_dquoted = 1;
	if ((c == '\"' && !(state->is_escaped) && state->is_dquoted))
		state->is_dquoted = 0;
	if ((c == '\'' && !(state->is_escaped) && !(state->is_dquoted)))
		state->is_squoted = 1;
	if ((c == '\'' && !(state->is_escaped) && state->is_squoted))
		state->is_squoted = 0;
	if ((c == '|' || c == '<' || c == '>') && !(state->is_escaped)
		&& !(state->is_squoted || state->is_dquoted))
		state->is_operator = 1;
	if (!(c == 32 || (c >= 8 && c <= 13)) && !(state->is_operator))
		state->is_word = 1;
	if ((c == 32 || (c >= 8 && c <= 13)) && state->is_operator)
		state->is_operator = 0;
	if (((c == 32 || (c >= 8 && c <= 13)) || state->is_operator)
		&& !(state->is_dquoted) && !(state->is_squoted))
		state->is_word = 0;
}

static t_token	*tokenize(char *str, size_t i, size_t len)
{
	t_token	*new;
	char	*pre_token;

	new = malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	pre_token = ft_substr(str, (i - len), len);
	new->token = ft_strtrim(str, " \f\t\n\r\v");
	if ((ft_strchr(str, '|') || ft_strchr(str, '<') || ft_strchr(str, '>'))
		&& (!ft_strchr(str, '\"') && !ft_strchr(str, '\'')))
		new->type = operation;
	else
		new->type = word;
	free(pre_token);
	return (new);
}
