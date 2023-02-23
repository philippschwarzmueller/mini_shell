#include "shell.h"

static void	iterate_str(char *str, t_list *lst);
static void	expand_lst(t_list *lst, char *str, int i);
static int	check_for_tokens(char *str, int i);
static int	check_if_quoted(char *str, int i, char token);

void	tokenize_lst(t_list **lst)
{
	char	*str;
	t_list	*prev;
	size_t	max;
	size_t	i;

	i = 0;
	max = ft_lstsize(*lst);
	while (i++ < max)
	{
		str = (char *)((*lst)->content);
		iterate_str(str, *lst);
		prev = *lst;
		*lst = (*lst)->next;
		ft_lstdelone(prev, free);
	}
}

static void	iterate_str(char *str, t_list *lst)
{
	size_t	i;

	i = 0;
	while (*str)
	{
		while (str[i] && !check_for_tokens(str, i))
			i++;
		if (i != 0)
			expand_lst(lst, str, i);
		str = str + i;
		i = 0;
		while (str[i] && check_for_tokens(str, i))
			i++;
		if (i != 0)
			expand_lst(lst, str, i);
		str = str + i;
		i = 0;
	}
}

static int	check_for_tokens(char *str, int i)
{
	if (i > 0 && str[i - 1] == '\\')
		return (0);
	if (str[i] != '|' && str[i] != '&'
		&& str[i] != '<' && str[i] != '>')
		return (0);
	if (!ft_strchr(str, '\"') && !ft_strchr(str, '\''))
		return (1);
	if (ft_strchr(str, '\"') && !ft_strchr(str, '\''))
		return (check_if_quoted(str, i, '\"'));
	if (!ft_strchr(str, '\"') && ft_strchr(str, '\''))
		return (check_if_quoted(str, i, '\''));
	if (ft_strchr(str, '\"') && ft_strchr(str, '\''))
		return (check_if_quoted(str, i, '\"') || check_if_quoted(str, i, '\''));
	return (0);
}

static int	check_if_quoted(char *str, int i, char token)
{
	int	j;
	int	left;
	int	right;

	j = i;
	left = 0;
	right = 0;
	while (str[j])
		if (str[j++] == token)
			right++;
	j = i;
	while (j >= 0)
		if (str[j--] == token)
			left++;
	return ((left % 2 == 0) && (right % 2 == 0));
}

static void	expand_lst(t_list *lst, char *str, int i)
{
	char	*tmp;

	tmp = ft_calloc(i + 1, sizeof(char));
	if (tmp != NULL)
		ft_strlcpy(tmp, str, i + 1);
	ft_lstadd_back(&lst, ft_lstnew(tmp));
}
