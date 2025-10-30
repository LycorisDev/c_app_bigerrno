#include "bigerrno.h"

char	*extract_key(int separator, char *key_value)
{
	if (separator > 0 && key_value[separator - 1] == '+')
		return (ft_substr(key_value, 0, separator - 1));
	else if (separator > 0)
		return (ft_substr(key_value, 0, separator));
	return (ft_strdup(key_value));
}
