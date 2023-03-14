#include "shell.h"

static char	**get_environment(void);
static void	logic(char *input, char ***env, t_bool debug);
static int	check_parsed_syntax(t_list *command_table);

int	main(int argc, char **argv)
{
	char	*input;
	char	**env;
	t_bool	debug;

	if (argc > 2)
		exit(EXIT_FAILURE);
	if (argc == 2 && argv[1][0] == 'd')
		debug = true;
	else
		debug = false;
	env = get_environment();
	while (1)
	{
		init_signalhandlers();
		input = get_input(env);
		logic(input, &env, debug);
	}
	ft_free_stra(env);
	return (EXIT_SUCCESS);
}

static void	logic(char *input, char ***env, t_bool debug)
{
	t_list	*command_table;
	t_list	*lexed_args;

	lexed_args = analyzer(input);
	if (check_token_syntax(lexed_args) == EXIT_FAILURE)
		return (ft_lstclear(&lexed_args, del_token), exit(2));
	if (debug)
		print_lexed_lst(lexed_args);
	command_table = parse(lexed_args, *env);
	ft_lstclear(&lexed_args, del_token);
	if (check_parsed_syntax(command_table) == EXIT_FAILURE)
		return (ft_lstclear(&command_table, &free_cmd), exit(2));
	if (debug)
		print_parsed_lst(command_table);
	expand(&command_table, *env);
	if (debug)
		print_parsed_lst(command_table);
	executor(command_table, env);
	if (debug)
		printf("\033[0;32mexit_code: \033[0m%d\n", g_exit_code);
	ft_lstclear(&command_table, &free_cmd);
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

static int	check_parsed_syntax(t_list *command_table)
{
	t_command	*temp_c;

	while (command_table != NULL)
	{
		temp_c = (t_command *) command_table->content;
		if (!temp_c)
		{
			ft_putstr_fd("Syntax error, missing a command\n", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
		command_table = command_table->next;
	}
	return (EXIT_SUCCESS);
}
