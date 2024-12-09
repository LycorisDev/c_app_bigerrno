#include "bigerrno.h"

static int	is_only_digits(const char *s);

int	bigerrno_exit(t_sh *sh, char **arg)
{
	int	numb;

	sh->keep_running = 0;
	if (sh->subshell == 0)
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (get_array_length((void **)arg) > 2)
	{
		return (output_error(EPERM,
				compose_err_msg(SHELL, arg[0], 0, ERR_NB_ARGS)));
	}
	if (arg[1])
	{
		numb = 0;
		if (is_only_digits(arg[1]))
			numb = atoi(arg[1]);
		if (!(numb != 0 || !ft_strcmp(arg[1], "0")))
			return (output_error(ENOENT,
					compose_err_msg(SHELL, arg[0], arg[1], ERR_NONUM)));
		return (numb % 256);
	}
	return (sh->exit_code);
}

static int	is_only_digits(const char *s)
{
	if (!s || !*s)
		return (0);
	while (ft_isdigit(*s))
		++s;
	return (!*s);
}
