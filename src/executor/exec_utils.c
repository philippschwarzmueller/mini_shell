#include "shell.h"

void	err(char *mess, int exit_code, t_list *commands)
{
	char	*err;

	ft_lstclear(&commands, free_cmd);
	err = ft_strjoin("sigmashell: ", mess);
	ft_putendl_fd(err, 2);
	free(mess);
	free(err);
	exit(exit_code);
}

char	**join_cmd(char *command, char **cmd)
{
	char	**res;
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_arr_len(cmd);
	res = ft_calloc((len + 2), sizeof(char *));
	res[0] = command;
	while (i++ < (len))
		res[i] = cmd[i - 1];
	return (ft_freestra(cmd), res);
}

void	ft_free_arr(char **ptr)
{
	int	i;

	if (ptr == NULL)
		return ;
	i = 0;
	while (ptr[i] != NULL)
		free(ptr[i++]);
	free(ptr);
	ptr = NULL;
}

void	dup_back(int orig_in, int orig_out)
{
	dup2(orig_in, 0);
	dup2(orig_out, 1);
	close(orig_in);
	close(orig_out);
}

size_t	ft_arr_len(char **arr)
{
	int	i;

	if (arr == NULL)
		return (0);
	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}
