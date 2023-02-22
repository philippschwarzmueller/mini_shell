#include "shell.h"

static void		whitespcs_format(char *str, t_list **lst);
static size_t	check_whitespcs(char *str);
static char		*str_format(char **str, int i);

t_list	*lexing(char *str)
{
	t_list	*lst;

	lst = ft_lstnew(NULL);
	whitespcs_format(str, &lst);
	tokenize_lst(&lst);
	return (lst);
}

static void	whitespcs_format(char *str, t_list **lst)
{
	size_t	len;
	t_list	*del;

	len = 0;
	while (str[len])
	{
		len = check_whitespcs(str);
		ft_lstadd_back(lst, ft_lstnew(str_format(&str, len + 1)));
		len = 0;
	}
	free(str);
	del = *lst;
	*lst = (*lst)->next;
	ft_lstdelone(del, free);
}

static size_t	check_whitespcs(char *str)
{
	size_t	i;

	i = 0;
	if (str[i] == '\"')
	{
		while (str[i] && str[++i] != '\"')
		{
			if (str[i] == '\\')
				i++;
		}
		if (!str[i])
			return (0);
		return (++i);
	}
	while (str[i] && !((str[i] >= 8 && str[i] <= 13) || str[i] == 32))
		i++;
	return (i);
}

static char	*str_format(char **str, int i)
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
