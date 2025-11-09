#include "bigerrno.h"

void	init_shell(t_sh *sh, char **argv)
{
	if (!sh)
		return ;
	sh->first_arg = argv[0];
	sh->valid_term = is_term_var_valid(sh);
	sh->is_tty = isatty(0) && isatty(1);
	sh->pid = ft_itoa(get_pid(sh, sh->first_arg));
	sh->user = circular_pipeline(sh, "/bin/whoami");
	sh->host = circular_pipeline(sh, "/bin/uname -n | /bin/cut -d. -f1");
	sh->home = get_home_path(sh, sh->user);
	sh->shells = get_shells(sh);
	sh->color_scheme = E_COLOR_GNOME;
	sh->rl.user = get_prompt_user(sh);
	sh->env = convert_envp_to_lst((const char **)environ, sh->first_arg);
	sh->pwd = getcwd(0, 0);
	update_shlvl(&sh->env, 0);
	return ;
}

void	free_shell(t_sh *sh)
{
	if (!sh)
		return ;
	rl_clear_history();
	lst_clear(&sh->env);
	lst_clear(&sh->env_hidden);
	lst_clear(&sh->env_local);
	free(sh->pwd);
	free(sh->pid);
	free(sh->user);
	free(sh->host);
	free(sh->home);
	free(sh->shells);
	free(sh->input);
	free(sh->rl.user);
	free(sh->rl.prompt);
	free_entire_array((void **)sh->rl.buf, free);
	free_entire_array((void **)sh->rl.arr, free_rl_arr_element);
	free_entire_array((void **)sh->rl.tokens, free);
	free_entire_array((void **)sh->rl.hd, free);
	if (!sh->keep_running)
		builtin_disco_stop(sh);
	return ;
}
