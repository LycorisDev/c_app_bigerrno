#include "libft.h"

char	*ft_strchrnul(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return ((char *)s + i);
		++i;
	}
	return ((char *)s + i);
}
