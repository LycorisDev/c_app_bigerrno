#include "bigerrno.h"

int	valid_keyvalue(char *key_value)
{
	int	i;
	int	separator;

	i = 0;
	separator = firstocc(key_value, '=');
	if (key_value[0] == '_' && (!key_value[1] || separator == 1))
		return (0);
	else if (ft_isdigit(key_value[0]))
		return (0);
	else if (ft_isalpha(key_value[i]) || key_value[i] == '_')
	{
		while (key_value[i] && (separator < 0 || i < separator - !!i))
		{
			if (!(ft_isalnum(key_value[i]) || key_value[i] == '_'))
				return (0);
			++i;
		}
		if (ft_isalnum(key_value[i])
			|| key_value[i] == '_' || key_value[i] == '+')
			return (!(separator < 0 && key_value[i] == '+'));
	}
	else
		return (0);
	return (1);
}
