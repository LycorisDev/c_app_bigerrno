#include "libft.h"

ssize_t	ft_putstr(int fd, const char *s)
{
	if (s)
		return (write(fd, s, ft_strlen(s)));
	return (-1);
}
