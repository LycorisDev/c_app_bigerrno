#include "ft_printf.h"

char	get_integer_sign(long long int nbr, t_format *curr)
{
	if (nbr < 0)
		return ('-');
	else if (curr->has_plus)
		return ('+');
	else if (curr->has_space)
		return (' ');
	return (0);
}

char	*get_padding(char c, int len)
{
	char	*pad;

	pad = 0;
	if (len > 0)
	{
		pad = malloc((len + 1) * sizeof(char));
		ft_memset(pad, c, len);
		pad[len] = 0;
	}
	return (pad);
}

char	*add_zeros(char *nbr, char sign, t_format *curr)
{
	char	*joined;
	char	*zeros;
	int		nbr_len;
	int		zeros_len;

	joined = 0;
	zeros = 0;
	zeros_len = 0;
	nbr_len = ft_strlen(nbr);
	if (curr->prec >= 0)
		zeros_len = (curr->mfw - nbr_len) - (curr->mfw - curr->prec);
	else if (!curr->has_dash && curr->has_zero)
		zeros_len = curr->mfw - nbr_len - (sign != 0);
	zeros = get_padding('0', zeros_len);
	joined = ft_strjoin(zeros, nbr);
	free(zeros);
	if (!joined)
		return (nbr);
	free(nbr);
	return (joined);
}

char	*add_spaces_and_sign(char *nbr, char sign, t_format *curr)
{
	char	*joined;
	char	*spaces;
	int		len;

	joined = 0;
	spaces = 0;
	len = ft_strlen(nbr);
	if (!curr->has_zero || curr->has_dash || curr->prec >= 0)
		spaces = get_padding(' ', curr->mfw - len - (sign != 0));
	len += (sign != 0) + ft_strlen(spaces);
	joined = ft_calloc(len + 1, sizeof(char));
	if (joined)
	{
		if (spaces && !curr->has_dash)
			ft_strlcat(joined, spaces, len + 1);
		joined[ft_strlen(spaces) * !curr->has_dash] = sign;
		ft_strlcat(joined, nbr, len + 1);
		if (spaces && curr->has_dash)
			ft_strlcat(joined, spaces, len + 1);
	}
	free(spaces);
	if (!joined)
		return (nbr);
	free(nbr);
	return (joined);
}
