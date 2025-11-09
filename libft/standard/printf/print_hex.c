#include "ft_printf.h"

static char	*get_hex_lower(unsigned int nbr, t_format *curr);
static char	*add_prefix(char *str);

int	print_hex_lower(unsigned int nbr, t_format *curr)
{
	int		len;
	char	*str;

	str = get_hex_lower(nbr, curr);
	len = ft_strlen(str);
	ft_putstr(1, str);
	free(str);
	return (len);
}

int	print_hex_upper(unsigned int nbr, t_format *curr)
{
	int		i;
	int		len;
	char	*str;

	str = get_hex_lower(nbr, curr);
	i = 0;
	while (str[i])
	{
		str[i] = ft_toupper(str[i]);
		++i;
	}
	len = ft_strlen(str);
	ft_putstr(1, str);
	free(str);
	return (len);
}

int	print_hex_address(unsigned long nbr, t_format *curr)
{
	int		len;
	char	sign;
	char	*str;

	if (!nbr)
		str = add_spaces_and_sign(ft_strdup("(nil)"), 0, curr);
	else
	{
		if (curr->mfw >= 2)
			curr->mfw -= 2;
		sign = get_integer_sign(nbr, curr);
		if (sign == '-')
			sign = 0;
		str = add_zeros(ft_ultoa_base(nbr, "0123456789abcdef"), sign, curr);
		str = add_spaces_and_sign(str, sign, curr);
		str = add_prefix(str);
	}
	len = ft_strlen(str);
	ft_putstr(1, str);
	free(str);
	return (len);
}

static char	*get_hex_lower(unsigned int nbr, t_format *curr)
{
	char	*str;

	if (nbr == 0)
		curr->has_hash = 0;
	if (nbr == 0 && curr->prec == 0)
		str = ft_strdup("");
	else
	{
		if (curr->has_hash && curr->mfw >= 2)
			curr->mfw -= 2;
		str = add_zeros(ft_uitoa_base(nbr, "0123456789abcdef"), 0, curr);
	}
	str = add_spaces_and_sign(str, 0, curr);
	if (curr->has_hash)
		str = add_prefix(str);
	return (str);
}

static char	*add_prefix(char *str)
{
	int		i;
	char	*dup;

	dup = malloc((ft_strlen(str) + 2 + 1) * sizeof(char));
	if (!dup)
		return (str);
	i = 0;
	while (str[i] == ' ' || str[i] == '+')
		++i;
	ft_strlcpy(dup, str, i + 1);
	ft_strlcat(dup, "0x", i + 2 + 1);
	ft_strlcat(dup, str + i, ft_strlen(str) + 2 + 1);
	free(str);
	return (dup);
}
