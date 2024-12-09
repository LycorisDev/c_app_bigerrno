#include "bigerrno.h"

int	is_shell(const char *shells, const char *cmd)
{
	char	*p_slash;
	char	**sh_lst;
	size_t	i;

	if (!shells | !cmd)
		return (0);
	p_slash = ft_strrchr(cmd, '/');
	sh_lst = ft_split(shells, ':');
	i = 0;
	while (sh_lst && sh_lst[i])
	{
		if (!ft_strcmp(cmd, sh_lst[i])
			|| (p_slash && !ft_strcmp(p_slash + 1, sh_lst[i])))
		{
			free_entire_array((void **)sh_lst, free);
			return (1);
		}
		i++;
	}
	free_entire_array((void **)sh_lst, free);
	return (0);
}
