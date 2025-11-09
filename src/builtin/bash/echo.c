#include "bigerrno.h"

static int	echo_option(char **arg, int *skip_newline, int *with_backlash,
				int *count);

int	builtin_echo(char **arg)
{
	int		to_be_echoed;
	int		skip_nl;
	int		with_backlash;
	int		count;
	char	*parsed;

	to_be_echoed = echo_option(arg, &skip_nl, &with_backlash, &count) - 1;
	while (arg[++to_be_echoed])
	{
		if (to_be_echoed != count)
			ft_putstr(1, " ");
		if (with_backlash > 0)
		{
			parsed = get_echo_escaped_token(arg[to_be_echoed], &skip_nl);
			ft_putstr(1, parsed);
			free(parsed);
		}
		else
			ft_putstr(1, arg[to_be_echoed]);
	}
	if (!skip_nl)
		ft_putstr(1, "\n");
	return (0);
}

static int	echo_option(char **arg, int *skip_newline, int *with_backlash,
				int *count)
{
	int	i;

	*skip_newline = 0;
	*with_backlash = 0;
	*count = 1;
	while (arg[*count] && arg[*count][0] == '-' && arg[*count][1])
	{
		i = 1;
		while (arg[*count][i] && (arg[*count][i] == 'n'
			|| arg[*count][i] == 'e'))
			++i;
		if (arg[*count][i] != '\0')
			break ;
		if (ft_strchr(arg[*count], 'n'))
			*skip_newline = 1;
		if (ft_strchr(arg[*count], 'e'))
			*with_backlash = 1;
		++*count;
	}
	return (*count);
}
