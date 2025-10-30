#include "bigerrno.h"

int	firstocc(char *s, char c)
{
	int	i;

	i = 0;
	if (!s || !c)
		return (-1);
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		++i;
	}
	return (-1);
}
