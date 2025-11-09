#include "ft_printf.h"

static int	print_formatted(const char *format, va_list args, t_format *curr);
static int	print_current_format(t_format *curr, va_list args);

/*
	- Like the standard printf, it prints to stdout and returns the amount of 
	printed characters or a negative number if an error is encountered.
	- Unlike the standard printf, it must not do buffer management.
	- It handles the following conversions: `cspdiuxX%`.
	- It handles the following flags: `# +-0`.
	- It handles the minimum field width and the precision.
*/

int	ft_printf(const char *format, ...)
{
	int			len_printed;
	va_list		args;
	t_format	*curr;

	len_printed = -1;
	if (!format)
		return (len_printed);
	va_start(args, format);
	curr = malloc(sizeof(t_format));
	if (curr)
		len_printed = print_formatted(format, args, curr);
	free(curr);
	va_end(args);
	return (len_printed);
}

static int	print_formatted(const char *format, va_list args, t_format *curr)
{
	int	i;
	int	len_printed;

	i = 0;
	len_printed = 0;
	while (format[i])
	{
		if (format[i] != '%')
		{
			write(1, format + i, 1);
			++len_printed;
			++i;
		}
		else
		{
			++i;
			set_current_format(curr, format + i);
			if (curr->length < 0)
				return (-1);
			len_printed += print_current_format(curr, args);
			i += curr->length;
		}
	}
	return (len_printed);
}

static int	print_current_format(t_format *curr, va_list args)
{
	if (curr->specifier == 'c')
		return (print_char((unsigned char)va_arg(args, int), curr));
	else if (curr->specifier == 's')
		return (print_string(va_arg(args, char *), curr));
	else if (curr->specifier == 'p')
		return (print_hex_address(va_arg(args, unsigned long), curr));
	else if (curr->specifier == 'd' || curr->specifier == 'i')
		return (print_dec_signed(va_arg(args, int), curr));
	else if (curr->specifier == 'u')
		return (print_dec_unsigned(va_arg(args, unsigned int), curr));
	else if (curr->specifier == 'x')
		return (print_hex_lower(va_arg(args, unsigned int), curr));
	else if (curr->specifier == 'X')
		return (print_hex_upper(va_arg(args, unsigned int), curr));
	else if (curr->specifier == '%')
		return (print_char('%', 0));
	return (0);
}
