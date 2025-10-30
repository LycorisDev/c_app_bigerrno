#include "bigerrno.h"

int	only_var(char **arg)
{
	int		i;

	i = 0;
	if (!arg || !*arg)
		return (0);
	while (arg[i])
	{
		if (!ft_strchr(arg[i], '='))
			return (0);
		else if (!valid_keyvalue(arg[i]))
			return (0);
		++i;
	}
	return (1);
}
