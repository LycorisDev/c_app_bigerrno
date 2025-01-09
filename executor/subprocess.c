#include "bigerrno.h"

static int		execute_subshell(t_sh *sh, t_pl *pl);
static void		run_cmd(t_sh *sh, t_pl *pl, char *cmd_fullpath);
static t_env	*merge_lst(t_env *lst1, t_env *lst2);

int	execute_subprocess(t_sh *sh, t_pl *pl)
{
	char	*cmd_fullpath;

	cmd_fullpath = 0;
	close_unused_pipes(pl->index, pl->fd_pipe, pl->fd_pipe_len);
	if (!redirect_io(pl))
		return (restore_io(pl));
	if (isbuiltin(pl->cmdl[pl->index]))
	{
		pl->exit_code = execute_builtin(sh);
		return (restore_io(pl));
	}
	if (!ft_strcmp(pl->cmdl[pl->index][0], SEP_STR))
		return (execute_subshell(sh, pl));
	extract_local_update(&pl->cmdl[pl->index], &sh->local);
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

static void	run_cmd(t_sh *sh, t_pl *pl, char *cmd_fullpath)
{
	t_env	*exec_env;
	char	**exec_arr;
	char	*p_slash;

	if (is_shell(sh->shells, cmd_fullpath))
	{
		update_shlvl(&sh->env, 0);
		p_slash = ft_strrchr(cmd_fullpath, '/');
		if (!ft_strcmp(cmd_fullpath, "bigerrno")
			|| (p_slash && !ft_strcmp(p_slash + 1, "bigerrno")))
			handle_default_background_color(1);
		else
			reset_title_and_background_color();
	}
	exec_env = merge_lst(sh->local, sh->env);
	exec_arr = convert_to_arr(exec_env);
	set_signals(1);
	execve(cmd_fullpath, pl->cmdl[pl->index], exec_arr);
	pl->exit_code = errno;
	pl->err_msg = compose_err_msg(0, pl->cmdl[pl->index][0], 0,
			strerror(pl->exit_code));
	lst_clear(&exec_env);
	free_entire_array((void **)exec_arr, free);
	return ;
}

static t_env	*merge_lst(t_env *lst1, t_env *lst2)
{
	t_env	*merge;
	t_env	*node;

	merge = 0;
	while (lst1)
	{
		node = lst_new(lst1->key, lst1->value);
		if (!node)
			lst_clear(&merge);
		lstadd_back(&merge, node);
		lst1 = lst1->next;
	}
	while (lst2)
	{
		if (!find_key(&merge, lst2->key))
		{
			node = lst_new(lst2->key, lst2->value);
			if (!node)
				lst_clear(&merge);
			lstadd_back(&merge, node);
		}
		lst2 = lst2->next;
	}
	return (merge);
}

char	**convert_to_arr(t_env *env)
{
	char	**env_arr;
	char	*tmp;
	int		size;
	int		i;

	if (!env)
		return (0);
	size = lst_size(&env);
	env_arr = ft_calloc(size + 1, sizeof(char *));
	i = 0;
	while (env)
	{
		tmp = ft_strjoin(env->key, "=");
		env_arr[i++] = ft_strjoin(tmp, env->value);
		free(tmp);
		env = env->next;
	}
	return (env_arr);
}
