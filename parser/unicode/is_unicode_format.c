#include "parser.h"

int	is_unicode_format(const char *s)
{
	if (!s || (s[0] && s[0] != 'u' && s[0] != 'U') || !s[1])
		return (0);
	return (is_hex_digit(s[1]));
}

int	is_hex_digit(char c)
{
	return (ft_isdigit(c) || (ft_isalpha(c) && ft_toupper(c) <= 'F'));
}
