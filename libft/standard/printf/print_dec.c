#include "ft_printf.h"

int	print_dec_signed(int nbr, t_format *curr)
{
	int		len;
	char	sign;
	char	*str;

	sign = 0;
	if (nbr == 0 && curr->prec == 0)
		str = ft_strdup("");
	else
	{
		sign = get_integer_sign(nbr, curr);
		if (sign == '-')
			nbr = -nbr;
		str = add_zeros(ft_itoa(nbr), sign, curr);
	}
	str = add_spaces_and_sign(str, sign, curr);
	len = ft_strlen(str);
	ft_putstr(1, str);
	free(str);
	return (len);
}

int	print_dec_unsigned(unsigned int nbr, t_format *curr)
{
	int		len;
	char	sign;
	char	*str;

	sign = 0;
	if (nbr == 0 && curr->prec == 0)
		str = ft_strdup("");
	else
	{
		sign = get_integer_sign(nbr, curr);
		str = add_zeros(ft_uitoa(nbr), sign, curr);
	}
	str = add_spaces_and_sign(str, sign, curr);
	len = ft_strlen(str);
	ft_putstr(1, str);
	free(str);
	return (len);
}
