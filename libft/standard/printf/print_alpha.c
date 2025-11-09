#include "ft_printf.h"

static char	*get_substring(char *str, t_format *curr);

int	print_char(unsigned char c, t_format *curr)
{
	int		len;
	char	*spaces;

	len = 1;
	if (!curr)
	{
		write(1, &c, 1);
		return (len);
	}
	spaces = get_padding(' ', curr->mfw - len);
	if (spaces)
		len += ft_strlen(spaces);
	if (!curr->has_dash)
	{
		ft_putstr(1, spaces);
		write(1, &c, 1);
	}
	else
	{
		write(1, &c, 1);
		ft_putstr(1, spaces);
	}
	free(spaces);
	return (len);
}

int	print_string(char *str, t_format *curr)
{
	int		len;
	char	*substr;
	char	*spaces;

	substr = get_substring(str, curr);
	if (!substr)
		return (0);
	len = ft_strlen(substr);
	spaces = get_padding(' ', curr->mfw - len);
	if (spaces)
		len += ft_strlen(spaces);
	if (!curr->has_dash)
	{
		ft_putstr(1, spaces);
		ft_putstr(1, substr);
	}
	else
	{
		ft_putstr(1, substr);
		ft_putstr(1, spaces);
	}
	free(substr);
	free(spaces);
	return (len);
}

static char	*get_substring(char *str, t_format *curr)
{
	int	len;

	if (!str)
	{
		if (curr->prec >= 0 && curr->prec < (int)ft_strlen("(null)"))
			return (ft_strdup(""));
		return (ft_strdup("(null)"));
	}
	len = ft_strlen(str);
	if (curr->prec >= 0 && curr->prec < len)
		len = curr->prec;
	return (ft_substr(str, 0, len));
}
