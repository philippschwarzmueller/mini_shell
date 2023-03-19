#include "shell.h"

int	main(void)
{
	char	*input;
	char	**env;
	t_list	*command_table;
	t_list	*lexed_args;

	env = get_environment();
	while (1)
	{
		init_signalhandlers();
		input = get_input(env);
		lexed_args = analyzer(input);
		command_table = parse(lexed_args, env);
		ft_lstclear(&lexed_args, del_token);
		expand(&command_table, env);
		executor(command_table, &env);
		ft_lstclear(&command_table, &free_cmd);
	}
	ft_free_stra(env);
	return (EXIT_SUCCESS);
}
