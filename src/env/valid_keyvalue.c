#include "bigerrno.h"

int	valid_keyvalue(char *key_value)
{
	char	*p_end;

	if (!key_value || ft_isdigit(key_value[0]))
		return (0);
	p_end = ft_strchr(key_value, '=');
	if (!p_end)
		p_end = ft_strchr(key_value, '\0');
	else if (p_end > key_value && *(p_end - 1) == '+')
		--p_end;
	if (p_end == key_value)
		return (0);
	else if (p_end == key_value + 1 && key_value[0] == '_')
		return (0);
	while (key_value < p_end)
	{
		if (*key_value != '_' && !ft_isalnum(*key_value))
			return (0);
		++key_value;
	}
	return (1);
}
