#include "shell.h"

void	del_token(void *content)
{
	t_token	*del;

	if (content == NULL)
		return ;
	del = (t_token *)content;
	free(del->token);
	free(del);
}

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

