#include "lex.h"

int	check(char *str, int i)
{
	if (i > 0 && str[i - 1] == '\\')
		return (0);
	if (str[i] == '|' || str[i] == '&')
		return (1);
	if (str[i] == '<' || str[i] == '>')
		return (1);
	return (0);
}

void	expand_lst(t_list *lst, char *str, int i)
{
	char	*tmp;
	t_list	*cntn;

	tmp = ft_calloc(i + 1, sizeof(char));
	ft_strlcpy(tmp, str, i);
	cntn = lst->next;
	lst->next = ft_lstnew(tmp);
	lst->next->next = cntn;
}

void	check_string(t_list *lst, t_list *prev)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *)(lst->content);
	while(*str)
	{
		printf("test\n");
		while (str[i] && !check(str, i))
			i++;
		if (i != 0)
			expand_lst(lst, str, i);
		str = str + i;
		i = 0;
		while (str[i] && check(str, i))
			i++;
		if (i != 0)
			expand_lst(lst, str, i);
		str = str + i;
		i = 0;
	}
	prev->next = lst->next;
	ft_lstdelone(lst, free);
}

void	tokenize_lst(t_list *lst)
{
	t_list	*prev;

	prev = lst;
	while (lst != NULL)
	{
		check_string(lst, prev);
		prev = lst;
		lst = lst->next;
	}
}

