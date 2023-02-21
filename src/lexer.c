#include "lex.h"

char	*str_format(char **str, int i)
{
	char	*content;
	char	*tmp;

	tmp = ft_calloc(i + 1, sizeof(char));
	ft_strlcpy(tmp, *str, i);
	content = ft_strtrim(tmp, " ");
	free(tmp);
	tmp = *str;
	*str = ft_strdup(tmp + i);
	free(tmp);
	return (content);
}

void	whitespcs_format(char *str, t_list **lst)
{
	size_t	i;
	t_list	*del;

	i = 0;
	while (str[i])
	{
		while (str[i] && !((str[i] >= 8 && str[i] <= 13) || str[i] == 32))
			i++;
		while (str[i + 1] && ((str[i + 1] >= 8 && str[i + 1] <= 13)
				|| str[i + 1] == 32))
			i++;
		ft_lstadd_back(lst, ft_lstnew(str_format(&str, i + 1)));
		i = 0;
	}
	del = *lst;
	*lst = (*lst)->next;
	ft_lstdelone(del, free);
}

t_list	*lexing(char *str)
{
	t_list	*lst;

	lst = ft_lstnew(NULL);
	whitespcs_format(str, &lst);
	tokenize_lst(lst);
	//free(str);
	return (lst);
}
