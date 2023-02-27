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

void	print_lexed_lst(t_list *lst)
{
	while (lst != NULL)
	{
		if (((t_token *)(lst->content))->type == word)
			printf("\033[0;94mword\033[0m\t");
		if (((t_token *)(lst->content))->type == piping)
			printf("\033[0;94mpipe\033[0m\t");
		if (((t_token *)(lst->content))->type == redirect)
			printf("\033[0;94mrdirect\033[0m\t");
		printf("%s\n", ((t_token *)(lst->content))->token);
		lst = lst->next;
	}
}

t_token	*tokenize(char *str, size_t i, size_t *len)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	new->token = ft_substr(str, ((i + 1) - *len), *len);
	if (ft_strchr(new->token, '|')
		&& !ft_strchr(new->token, '\"') && !ft_strchr(new->token, '\"'))
		new->type = piping;
	else if ((ft_strchr(new->token, '>') || ft_strchr(new->token, '<'))
		&& !ft_strchr(new->token, '\"') && !ft_strchr(new->token, '\"'))
		new->type = redirect;
	else
		new->type = word;
	return (*len = 0, new);
}
