#include "shell.h"

char	*remove_whitespaces(char *str)
{
	size_t	i;
	size_t	j;
	char	*res;

	i = 0;
	j = 0;
	if (str == NULL)
		return (NULL);
	res = ft_calloc(ft_strlen(str), sizeof(char *));
	while (str[i])
	{
		if (str[i] == 9)
			res[j++] = ' ';
		else
			res[j++] = str[i];
		if (str[i] == 32 || str[i] == 9)
			while (str[i] == 32 || str[i] == 9)
				i++;
		else
			i++;
	}
	free(str);
	str = res;
	res = ft_strdup(str);
	return (free(str), res);
}

char	*trim_front(char *s1, const char *set)
{
	char	*res;
	int		start;
	int		len;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	len = ft_strlen(s1);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	res = ft_calloc((len - start + 1), sizeof(*s1));
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1 + start, len - start + 1);
	return (free(s1), res);
}

char	*trim_back(char *s1, const char *set)
{
	char	*res;
	int		end;

	if (!s1 || !set)
		return (NULL);
	end = ft_strlen(s1);
	while (end > 0 && ft_strchr(set, s1[end - 1]))
		end--;
	res = ft_calloc((end + 1), sizeof(*s1));
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1, end + 1);
	return (free(s1), res);
}
