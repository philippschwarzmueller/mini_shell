#include "shell.h"

void	remove_val(t_list **lst, void *content)
{
	t_list	*tmp;
	t_list	*prev;

	prev = NULL;
	if (!lst || !(*lst))
		return ;
	while (((t_token *)((*lst)->content)) == (t_token *)content)
	{
		prev = (*lst)->next;
		free(*lst);
		*lst = prev;
		if (*lst == NULL)
			break ;
	}
	tmp = *lst;
	while (tmp != NULL)
	{
		if (((t_token *)((tmp)->content)) == (t_token *)content)
		{
			prev->next = (tmp)->next;
			free(tmp);
		}
		prev = tmp;
		tmp = (tmp)->next;
	}
}

void	del_token(void *content)
{
	t_token	*del;

	if (content == NULL)
		return ;
	del = (t_token *)content;
	free(del->token);
	free(del);
}

void	set_type(t_token *new)
{
	size_t	i;
	char	*str;

	i = 0;
	str = new->token;
	new->type = word;
	while (str[i])
	{
		if (str[i] != '|' && str[i] != '<' && str[i] != '>')
			return ;
		i++;
	}
	if (ft_strchr(str, '|') && !ft_strchr(str, '<') && !ft_strchr(str, '>'))
		return ((void)(new->type = piping));
	if (ft_strchr(str, '<') && !ft_strchr(str, '|') && !ft_strchr(str, '>')
		&& ft_strlen(str) < 3)
		return ((void)(new->type = redirect));
	if (ft_strchr(str, '>') && !ft_strchr(str, '|') && !ft_strchr(str, '<')
		&& ft_strlen(str) < 3)
		return ((void)(new->type = redirect));
	new->type = syntax;
}

int	is_quoted(char *str, size_t i, char token)
{
	char	cmp;
	size_t	j;
	int		sv;

	j = i;
	sv = 0;
	if (token == '\"')
		cmp = '\'';
	else
		cmp = '\"';
	while (str[j] && str[j] != cmp)
		if (str[++j] == cmp)
			sv = 1;
	j = i;
	while (j && str[j] != cmp)
		if (str[--j] == cmp && sv)
			return (1);
	return (0);
}

char	*ft_decrustify_str(char *str)
{
	size_t	i;
	size_t	j;
	char	*res;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = ft_calloc(ft_strlen(str) + 1, sizeof(char *));
	while (str[j])
	{
		if (str[j] != '\"' && str[j] != '\'' && str[j] != '\\')
			tmp[i++] = str[j++];
		else if (j > 0 && (str[j - 1] == '\\' || is_quoted(str, j, str[j])))
			tmp[i++] = str[j++];
		else
			j++;
	}
	res = ft_calloc(i + 1, sizeof(char));
	ft_strlcpy(res, tmp, i + 1);
	return (free(str), free(tmp), res);
}
