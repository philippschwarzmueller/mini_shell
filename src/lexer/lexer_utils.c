#include "shell.h"

void	print_lexed_lst(t_list *lst)
{
	while (lst != NULL)
	{
		if (((t_token *)(lst->content))->type == word)
			printf("\033[0;94mword\033[0m\t");
		if (((t_token *)(lst->content))->type == piping)
			printf("\033[0;94mpipe\033[0m\t");
		if (((t_token *)(lst->content))->type == infile)
			printf("\033[0;94minfile\033[0m\t");
		if (((t_token *)(lst->content))->type == outfile)
			printf("\033[0;94moutfile\033[0m\t");
		if (((t_token *)(lst->content))->type == here_doc)
			printf("\033[0;94mheredoc\033[0m\t");
		if (((t_token *)(lst->content))->type == append)
			printf("\033[0;94mappend\033[0m\t");
		if (((t_token *)(lst->content))->type == syntax)
			printf("\033[0;94msyntax\033[0m\t");
		printf("%s\n", ((t_token *)(lst->content))->token);
		lst = lst->next;
	}
}

void	del_first(t_list **lst)
{
	t_list	*del;

	del = *lst;
	*lst = (*lst)->next;
	ft_lstdelone(del, free);
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
