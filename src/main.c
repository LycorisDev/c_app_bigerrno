#include "bigerrno.h"

int	g_signum;

int	main(int argc, char **argv)
{
	t_sh	sh;

	ft_bzero(&sh, sizeof(t_sh));
	handle_no_tty();
	if (argc > 1)
		return (output_error(EPERM,
				compose_err_msg(SHELL, 0, 0, "Too many arguments")));
	if (!set_signals(0))
		return (1);
	handle_default_background_color(0);
	init_shell(&sh, argv);
	run_shell(&sh);
	free_shell(&sh);
	if (sh.subshell == 0)
	{
		reset_title();
		handle_default_background_color(1);
	}
	return (sh.exit_code);
}
