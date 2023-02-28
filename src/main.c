#include "shell.h"

//following does not free all the struct properties of command_table properly
int	main(void)
{
	char	*input;
	t_list	*command_table;
	t_list	*lexed_args;

	command_table = NULL;
	while (1)
	{
		init_signalhandlers();
		input = readline("\033[0;31msigmashell \033[0;32m> \033[0;37m");
		add_history(input);
		if (input == NULL)
		{
			rl_replace_line("TEST", 0);
			rl_redisplay();
			clear_history();
			exit(EXIT_SUCCESS);
		}
		lexed_args = analyzer(input);
		print_lexed_lst(lexed_args);
		// command_table = parse(lexed_args);
		// print_parsed_lst(command_table);
		// ft_lstclear(&command_table, free);
		ft_lstclear(&lexed_args, del_token);
		system("leaks minishell");
	}
	return (EXIT_SUCCESS);
}

void	print_parsed_lst(t_list *command_table)
{
	t_command	*temp;

	while (command_table != NULL)
	{
		temp = (t_command *)command_table->content;
		ft_printf("------------------\n");
		ft_printf("%p\n", command_table);
		ft_printf("Command: %s\n", temp->command);
		ft_printf("Path: %s\n", temp->path);
		ft_printf("Option: %s\n", temp->options);
		ft_printf("In: %d\n", temp->in);
		ft_printf("Out: %d\n", temp->out);
		ft_printf("next: %p\n", command_table->next);
		ft_printf("------------------\n");
		command_table = command_table->next;
	}
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
		if (((t_token *)(lst->content))->type == syntax)
			printf("\033[0;94msyntax\033[0m\t");
		printf("%s\n", ((t_token *)(lst->content))->token);
		lst = lst->next;
	}
}
