#include "libft.h"

static int	get_num_len(unsigned long n, int base_len);

char	*ft_ultoa_base(unsigned long n, char *base)
{
	int		num_len;
	int		base_len;
	char	*str;

	if (!base)
		return (0);
	base_len = ft_strlen(base);
	if (base_len < 2)
		return (0);
	num_len = get_num_len(n, base_len);
	str = ft_calloc(num_len + 1, sizeof(char));
	if (!str)
		return (0);
	str[--num_len] = base[0];
	while (n > 0)
	{
		str[num_len--] = base[n % base_len];
		n /= base_len;
	}
	return (str);
}

static int	get_num_len(unsigned long n, int base_len)
{
	int	num_len;

	num_len = 0;
	if (!n)
		return (1);
	while (n > 0)
	{
		++num_len;
		n /= base_len;
	}
	return (num_len);
}
