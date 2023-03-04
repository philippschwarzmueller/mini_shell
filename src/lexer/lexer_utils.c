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

	i = -1;
	str = new->token;
	while (str[++i])
		if (str[i] != '|' && str[i] != '<' && str[i] != '>')
			return ;
	if (ft_strchr(str, '|') && !ft_strchr(str, '<') && !ft_strchr(str, '>'))
		return ((void)(new->type = piping));
	if (ft_strchr(str, '<') && !ft_strchr(str, '|') && !ft_strchr(str, '>')
		&& ft_strlen(str) == 1)
		return ((void)(new->type = infile));
	if (ft_strchr(str, '<') && !ft_strchr(str, '|') && !ft_strchr(str, '>')
		&& ft_strlen(str) == 2)
		return ((void)(new->type = here_doc));
	if (ft_strchr(str, '>') && !ft_strchr(str, '|') && !ft_strchr(str, '<')
		&& ft_strlen(str) == 1)
		return ((void)(new->type = outfile));
	if (ft_strchr(str, '>') && !ft_strchr(str, '|') && !ft_strchr(str, '<')
		&& ft_strlen(str) == 2)
		return ((void)(new->type = append));
	new->type = syntax;
}
