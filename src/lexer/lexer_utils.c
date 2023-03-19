#include "shell.h"

void	quotation_error(t_list *lst, char *str)
{
	free(str);
	ft_lstclear(&lst, del_token);
	ft_putstr_fd("May I interject for a moment, but twenty ", STDERR_FILENO);
	ft_putstr_fd("years\nafter the publication of the first ", STDERR_FILENO);
	ft_putstr_fd("Posix shell\nstandard, members of the ", STDERR_FILENO);
	ft_putstr_fd("standards working group\nare still debating", STDERR_FILENO);
	ft_putendl_fd(" the proper behavior of obscure quoting.", STDERR_FILENO);
	g_exit_code = 1;
}

int	check_token_syntax(t_list *token_list)
{
	t_token	*temp_t;
	t_token	*temp_next_t;

	while (token_list != NULL)
	{
		temp_t = (t_token *) token_list->content;
		if (token_list->next)
			temp_next_t = (t_token *) token_list->next->content;
		if ((temp_t->type == infile || temp_t->type == outfile)
			&& (!temp_next_t || temp_next_t->type != word))
		{
			ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
			if (!temp_next_t)
				ft_putstr_fd("newline", STDERR_FILENO);
			else
				ft_putstr_fd(temp_t->token, STDERR_FILENO);
			ft_putstr_fd("'", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
		token_list = token_list->next;
		temp_next_t = NULL;
	}
	return (EXIT_SUCCESS);
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
