#include "ft_printf.h"

static void	parse_flags(t_format *curr, const char *str);
static void	parse_minimum_field_width(t_format *curr, const char *str);
static void	parse_precision(t_format *curr, const char *str);
static void	parse_specifier(t_format *curr, const char *str);

void	set_current_format(t_format *curr, const char *str)
{
	ft_bzero(curr, sizeof(t_format));
	parse_flags(curr, str);
	parse_minimum_field_width(curr, str);
	parse_precision(curr, str);
	parse_specifier(curr, str);
	return ;
}

static void	parse_flags(t_format *curr, const char *str)
{
	int	i;

	i = curr->length;
	while (str[i] == '#' || str[i] == '+' || str[i] == ' ' || str[i] == '-'
		|| str[i] == '0')
	{
		if (str[i] == '#')
			curr->has_hash = 1;
		else if (str[i] == '+')
			curr->has_plus = 1;
		else if (str[i] == ' ')
			curr->has_space = 1;
		else if (str[i] == '-')
			curr->has_dash = 1;
		else if (str[i] == '0')
			curr->has_zero = 1;
		++i;
	}
	curr->length = i;
	return ;
}

static void	parse_minimum_field_width(t_format *curr, const char *str)
{
	int	i;

	i = curr->length;
	while (ft_isdigit(str[i]))
		++i;
	if (i > curr->length)
	{
		curr->mfw = ft_atoi(str + curr->length);
		if (curr->mfw < 0)
			curr->mfw = 0;
	}
	curr->length = i;
	return ;
}

/*
	Instead of using 0, it's clearer to use -1 to express a lack of precision. 
*/
static void	parse_precision(t_format *curr, const char *str)
{
	int	i;

	i = curr->length;
	if (str[i] == '.')
	{
		++i;
		curr->length += 1;
		while (ft_isdigit(str[i]))
			++i;
		if (i != curr->length)
		{
			curr->prec = ft_atoi(str + curr->length);
			if (curr->prec < 0)
				curr->prec = 0;
		}
	}
	else
		curr->prec = -1;
	curr->length = i;
	return ;
}

static void	parse_specifier(t_format *curr, const char *str)
{
	int	i;

	i = curr->length;
	if (str[i] == 'c' || str[i] == 's' || str[i] == 'p' || str[i] == 'd'
		|| str[i] == 'i' || str[i] == 'u' || str[i] == 'x' || str[i] == 'X'
		|| str[i] == '%')
	{
		curr->specifier = str[i];
		curr->length += 1;
	}
	else
		curr->length = -1;
	return ;
}
