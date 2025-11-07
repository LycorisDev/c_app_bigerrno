#include "bigerrno.h"

static int		subprocess_body(t_sh *sh, t_pl *pl);
static int		execute_subshell(t_sh *sh, t_pl *pl);
static void		run_cmd(t_sh *sh, t_pl *pl, char *cmd_fullpath);

void	execute_subprocess(t_sh *sh, int fd_pipe[2], int fd_input, int *pid)
{
	int	child_exit_code;

	free(pid);
	++sh->subshell;
	update_shlvl(&sh->env, 1);
	dup2(fd_input, STDIN_FILENO);
	close(fd_input);
	if (sh->ex->pl.index < sh->ex->pl.len - 1)
	{
		close(fd_pipe[0]);
		dup2(fd_pipe[1], STDOUT_FILENO);
		close(fd_pipe[1]);
	}
	child_exit_code = subprocess_body(sh, &sh->ex->pl);
	destroy_all_ex(sh);
	free_shell(sh);
	exit(child_exit_code);
	return ;
}

static int	subprocess_body(t_sh *sh, t_pl *pl)
{
	char	*cmd_fullpath;

	cmd_fullpath = 0;
	if (!redirect_io(pl))
		return (restore_io(pl));
	if (is_builtin(pl->cmdl[pl->index]))
	{
		pl->exit_code = execute_builtin(sh);
		return (restore_io(pl));
	}
	if (!ft_strcmp(pl->cmdl[pl->index][0], SEP_STR))
		return (execute_subshell(sh, pl));
	extract_env_local_update(&pl->cmdl[pl->index], &sh->env_local);
	if (!resolve_command(pl, pl->cmdl[pl->index][0], &cmd_fullpath))
		return (restore_io(pl));
	if (cmd_fullpath)
	{
		run_cmd(sh, pl, cmd_fullpath);
		free(cmd_fullpath);
	}
	return (restore_io(pl));
}

static int	execute_subshell(t_sh *sh, t_pl *pl)
{
	size_t	last;
	int		fd_std[2];

	remove_array_elements((void **)pl->cmdl[pl->index], 0, 0, free);
	last = get_array_length((void **)pl->cmdl[pl->index]) - 1;
	remove_array_elements((void **)pl->cmdl[pl->index], last, last, free);
	sh->rl.tokens = (char **)extract_array_elements(
			(void **)pl->cmdl[pl->index], 0, last - 1);
	fd_std[0] = pl->fd_std[0];
	fd_std[1] = pl->fd_std[1];
	destroy_all_ex(sh);
	interpret_and_process_cmd(sh);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	dup2(fd_std[0], STDIN_FILENO);
	close(fd_std[0]);
	dup2(fd_std[1], STDOUT_FILENO);
	close(fd_std[1]);
	return (sh->exit_code);
}

/*
	TODO:
	If you do `handle_default_background_color(1)`, there's a flash of the 
	default color before becoming purple again. But if you don't, then even 
	bash will keep the purple instead of resetting.

	The goal is simply to tell the shell what the default color is. But since 
	the entire process is overwritten, we don't have any memory. The only thing 
	we have is the environment. So, store the original background (and prompt?) 
	colors within the env.
*/
static void	run_cmd(t_sh *sh, t_pl *pl, char *cmd_fullpath)
{
	char	**envp;

	if (is_shell(sh->shells, cmd_fullpath))
	{
		update_shlvl(&sh->env, 0);
		if (!is_our_shell(cmd_fullpath))
			reset_title();
		handle_default_background_color(1);
	}
	envp = convert_env_to_arr(sh);
	set_signals(1);
	execve(cmd_fullpath, pl->cmdl[pl->index], envp);
	pl->exit_code = errno;
	pl->err_msg = compose_err_msg(0, pl->cmdl[pl->index][0], 0,
			strerror(pl->exit_code));
	free_entire_array((void **)envp, free);
	return ;
}
