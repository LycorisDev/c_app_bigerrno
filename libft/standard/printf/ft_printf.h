#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

/* ft_printf Utilities ------------------------------------------------------ */

typedef struct s_format
{
	int		length;
	int		has_hash;
	int		has_plus;
	int		has_space;
	int		has_dash;
	int		has_zero;
	int		mfw;
	int		prec;
	char	specifier;
}	t_format;

void	set_current_format(t_format *curr, const char *str);

int		print_char(unsigned char c, t_format *curr);
int		print_string(char *str, t_format *curr);
int		print_dec_signed(int nbr, t_format *curr);
int		print_dec_unsigned(unsigned int nbr, t_format *curr);
int		print_hex_lower(unsigned int nbr, t_format *curr);
int		print_hex_upper(unsigned int nbr, t_format *curr);
int		print_hex_address(unsigned long nbr, t_format *curr);

char	get_integer_sign(long long int nbr, t_format *curr);
char	*get_padding(char c, int len);
char	*add_zeros(char *nbr, char sign, t_format *curr);
char	*add_spaces_and_sign(char *nbr, char sign, t_format *curr);

#endif
