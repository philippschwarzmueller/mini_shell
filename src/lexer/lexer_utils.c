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

void	set_lst_start(t_list **lst)
{
	t_list	*del;

	del = *lst;
	*lst = (*lst)->next;
	ft_lstdelone(del, free);
}
