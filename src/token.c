#include "shell.h"

static void	iterate_str(char *str, t_list *lst);
static void	expand_lst(t_list *lst, char *str, int i);
static int	check_for_tokens(char *str, int i);

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
	if (str[0] == '\"')
		return (expand_lst(lst, str, ft_strlen(str)));
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
	if (str[i] == '|' || str[i] == '&')
		return (1);
	if (str[i] == '<' || str[i] == '>')
		return (1);
	return (0);
}

static void	expand_lst(t_list *lst, char *str, int i)
{
	char	*tmp;

	tmp = ft_calloc(i + 1, sizeof(char));
	if (tmp != NULL)
		ft_strlcpy(tmp, str, i + 1);
	ft_lstadd_back(&lst, ft_lstnew(tmp));
}
