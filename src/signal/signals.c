#include "bigerrno.h"

int	set_signals(int reset)
{
	if (reset)
		return (set_signal_handling(SIGQUIT, SIG_DFL)
			&& set_signal_handling(SIGINT, SIG_DFL));
	return (set_signal_handling(SIGQUIT, SIG_IGN)
		&& set_signal_handling(SIGINT, SIG_IGN));
}

int	set_signal_handling(int signum, void (*handler)(int))
{
	struct sigaction	sa;
	char				*str_sig;

	sa.sa_handler = handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(signum, &sa, 0) < 0)
	{
		str_sig = ft_itoa(signum);
		output_error(errno, compose_err_msg(SHELL, "sigaction", str_sig,
				strerror(errno)));
		free(str_sig);
		return (0);
	}
	return (1);
}

void	signal_handler(int signum)
{
	g_signum = signum;
	if (signum == SIGINT)
		close(0);
	return ;
}
