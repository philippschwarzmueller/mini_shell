#include "shell.h"

static char	**get_environment(void);
static void	logic(char *input, char ***env);

int	main(void)
{
	char	*input;
	char	**env;

	env = get_environment();
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
			ft_free_stra(env);
			exit(EXIT_SUCCESS);
		}
		logic(input, &env);
		system("leaks minishell");
	}
	ft_free_stra(env);
	return (EXIT_SUCCESS);
}

static char	**get_environment(void)
{
	size_t		i;
	char		**res;
	extern char	**environ;

	i = 0;
	if (environ == NULL)
		return (NULL);
	res = malloc((ft_stra_len(environ) + 1) * sizeof(char *));
	while (environ[i] != NULL)
	{
		res[i] = ft_strdup(environ[i]);
		i++;
	}
	res[i] = NULL;
	return (res);
}

static void	logic(char *input, char ***env)
{
	t_list	*command_table;
	t_list	*lexed_args;
	t_list	*expanded_command_table;

	lexed_args = analyzer(input);
	print_lexed_lst(lexed_args);
	command_table = parse(lexed_args);
	ft_lstclear(&lexed_args, del_token);
	ft_printf("COMMAND TABLE\n");
	print_parsed_lst(command_table);
	expanded_command_table = expand(command_table, *env);
	ft_printf("EXPANDED COMMAND TABLE\n");
	print_parsed_lst(expanded_command_table);
	executor(expanded_command_table, env);
	executor(command_table, env);
	printf("%d\n", exit_code);
	ft_lstclear(&command_table, &free_cmd);
}

void	print_parsed_lst(t_list *command_table)
{
	t_command	*temp;
	int			i;

	i = 0;
	while (command_table != NULL)
	{
		temp = (t_command *)command_table->content;
		ft_printf("------------------\n");
		ft_printf("Command: %s\n", temp->command);
		ft_printf("Options: ");
		while (temp && temp->options != NULL && temp->options[i] != NULL)
		{
			ft_printf("%d: ", i);
			ft_printf("%s ", temp->options[i]);
			i++;
		}
		ft_printf("\n");
		ft_printf("In: %d\n", temp->in);
		ft_printf("Out: %d\n", temp->out);
		ft_printf("------------------\n");
		command_table = command_table->next;
		i = 0;
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
