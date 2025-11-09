#include "bigerrno.h"

int	g_signum;

int	main(int argc, char **argv)
{
	t_sh	sh;

	ft_bzero(&sh, sizeof(t_sh));
	if (argc > 1)
		return (output_error(EPERM,
				compose_err_msg(SHELL, 0, 0, "Too many arguments")));
	if (!set_signals(0))
		return (1);
	init_shell(&sh, argv);
	if (sh.is_tty)
		handle_default_background_color(0);
	run_shell(&sh);
	free_shell(&sh);
	if (sh.is_tty && sh.subshell == 0)
	{
		reset_title();
		handle_default_background_color(1);
	}
	return (sh.exit_code);
}
