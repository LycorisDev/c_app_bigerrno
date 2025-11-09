#include "libft.h"

static int	get_num_len(unsigned int n);

char	*ft_uitoa(unsigned int n)
{
	int		num_len;
	char	*str;

	num_len = get_num_len(n);
	str = malloc((num_len + 1) * sizeof(char));
	if (!str)
		return (0);
	str[num_len--] = 0;
	str[num_len] = '0';
	while (n > 0)
	{
		str[num_len--] = '0' + n % 10;
		n /= 10;
	}
	return (str);
}

static int	get_num_len(unsigned int n)
{
	int	num_len;

	num_len = 0;
	if (!n)
		return (1);
	while (n > 0)
	{
		++num_len;
		n /= 10;
	}
	return (num_len);
}
