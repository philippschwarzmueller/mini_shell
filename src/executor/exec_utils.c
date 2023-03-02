#include "shell.h"

void	err(char *mess, int exit_code, char **cmd)
{
	char	*err;

	if (cmd != NULL)
		ft_free_arr(cmd);
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

	i = 1;
	len = ft_arr_len(cmd);
	res = ft_calloc((len + 2), sizeof(char *));
	res[0] = command;
	while (i < len)
		res[i] = cmd[i - 1];
	return (res);
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

char	*ft_strjoin_alt(char *s1, char *s2)
{
	char	*res;
	size_t	i;
	size_t	len;
	size_t	len_s1;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len = len_s1 + ft_strlen(s2) + 1;
	res = malloc(len * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (i < len_s1)
			res[i] = s1[i];
		else
			res[i] = s2[j++];
		i++;
	}
	return (free(s1), res);
}
