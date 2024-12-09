#include "parser.h"

char	*circular_pipeline(t_sh *sh, const char *cmdl)
{
	char	*data;

	if (!sh || !cmdl)
		return (0);
	sh->rl.tokens = tokenize(cmdl, 1, ft_isspace);
	interpreter(sh);
	free_entire_array((void **)sh->rl.tokens, free);
	sh->rl.tokens = 0;
	if (!sh->ex)
		return (0);
	data = 0;
	sh->ex->pl.circular = 1;
	if (pipe(sh->ex->pl.fd_circ) >= 0)
	{
		execute_pipeline(sh);
		data = get_next_line(sh->ex->pl.fd_circ[0]);
		if (data && ft_strchr(data, '\n'))
			*ft_strchr(data, '\n') = 0;
		close(sh->ex->pl.fd_circ[0]);
	}
	destroy_all_ex(sh);
	return (data);
}

int	is_term_var_valid(t_sh *sh)
{
	char	*term;
	char	*tmp1;
	char	*tmp2;
	int		dup_err;
	int		result;

	term = getenv("TERM");
	if (!term)
		return (0);
	tmp1 = ft_strjoin("/bin/infocmp ", term);
	tmp2 = ft_strjoin(tmp1, " | /bin/head -c8");
	free(tmp1);
	dup_err = dup(STDERR_FILENO);
	close(STDERR_FILENO);
	tmp1 = circular_pipeline(sh, tmp2);
	dup2(dup_err, STDERR_FILENO);
	close(dup_err);
	free(tmp2);
	result = tmp1 && tmp1[0];
	free(tmp1);
	return (result);
}

int	get_pid(t_sh *sh, const char *first_arg)
{
	int		pid;
	char	*tmp1;
	char	*tmp2;

	if (!sh || !first_arg)
		return (0);
	tmp1 = ft_strjoin("/bin/ps aux | /bin/grep ", first_arg);
	tmp2 = ft_strjoin(tmp1, " | /bin/grep -v grep | /bin/awk '{print $2}'"
			" | /bin/tail -n 1");
	free(tmp1);
	if (!tmp2)
		return (0);
	tmp1 = circular_pipeline(sh, tmp2);
	free(tmp2);
	if (!tmp1)
		return (0);
	pid = ft_atoi(tmp1);
	free(tmp1);
	return (pid);
}

char	*get_home_path(t_sh *sh, const char *username)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strjoin("/bin/getent passwd ", username);
	tmp2 = ft_strjoin(tmp1, " | /bin/cut -d: -f6");
	free(tmp1);
	tmp1 = circular_pipeline(sh, tmp2);
	free(tmp2);
	return (tmp1);
}

char	*get_shells(t_sh *sh)
{
	return (circular_pipeline(sh, "/bin/cat /etc/shells | /bin/grep -v # "
			"| /bin/sed 's|.*/||' | /bin/sort "
			"| /bin/sed '$!N; /^\\(.*\\)\\n\\1$/!P; D' | /bin/tr '\\n' ':' "
			"| /bin/sed 's/$/bigerrno/'"));
}
