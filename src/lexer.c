#include "lex.h"

int	check(char *str, int i)
{
	if (i > 0 && str[i - 1] == '\\')
		return (0);
	if (str[i] == '|' || str[i] == '&')
		return (1);
	if (str[i] == '<' || str[i] == '>')
		return (1);
	if ((str[i] >= 8 && str[i] <= 13) || str[i] == 32)
		return (1);
	return (0);
}

char	*str_format(char **str, int i)
{
	char	*content;
	char	*tmp;

	tmp = ft_calloc(i + 1, sizeof(char));
	ft_strlcpy(tmp, *str, i);
	content = ft_strtrim(tmp, ">|&< ");
	free(tmp);
	tmp = *str;
	*str = ft_strdup(tmp + i);
	free(tmp);
	return (content);
}

t_list	*lexing(char *str)
{
	size_t	i;
	t_list	*res;
	t_list	*del;

	i = 0;
	res = ft_lstnew(NULL);
	while (str[i])
	{
		while (str[i] && !check(str, i))
			i++;
		while (str[i + 1] && check(str, i + 1))
			i++;
		ft_lstadd_back(&res, ft_lstnew(str_format(&str, i + 1)));
		i = 0;
	}
	free(str);
	del = res;
	res = res->next;
	ft_lstdelone(del, free);
	return (res);
}
