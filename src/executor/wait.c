#include "bigerrno.h"

void	wait_for_subprocesses(t_sh *sh, int *pid, int options)
{
	size_t	i;
	int		status;
	int		signum;

	i = 0;
	status = 0;
	while (pid[i])
	{
		while (waitpid(pid[i], &status, options) < 0 && errno == EINTR)
			errno = 0;
		++i;
	}
	if (sh->ex->pl.exit_code || !status)
		return ;
	else if (WIFEXITED(status))
		sh->ex->pl.exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		signum = WTERMSIG(status);
		sh->ex->pl.exit_code = 128 + signum;
		ft_putstr(2, get_sig_flavor_text(signum));
	}
	return ;
}
