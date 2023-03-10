#include "shell.h"

static int	get_error_message(char *path, int flag);

int	open_files(char *path, int flag)
{

	if (flag == 0 && access(path, F_OK) < 0)
		return (get_error_message(path, 0));
	if (flag == 0 && access(path, R_OK) < 0)
		return (get_error_message(path, 1));
	if (flag > 0 && access(path, W_OK) < 0)
		return (get_error_message(path, 1));
	if (flag == 0)
		return (open(path, O_RDONLY));
	if (flag == O_TRUNC)
		return (open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	if (flag == O_APPEND)
		return (open(path, O_WRONLY | O_CREAT | O_APPEND, 0644));
	return (-1);
}

static int	get_error_message(char *path, int flag)
{
	char	*tmp;
	char	*error;

	if (!flag)
		tmp = ft_strjoin(path, ": No such file or directory");
	else
		tmp = ft_strjoin("permission denied: ", path);
	error = ft_strjoin("sigmashell: ", tmp);
	ft_putendl_fd(error, 2);
	free(tmp);
	free(error);
	return (-1);
}
