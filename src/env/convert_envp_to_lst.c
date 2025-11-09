#include "bigerrno.h"

static void	create_basic_env(t_env **lst, const char *sh_first_arg);
static void	copy_to_lst(const char **env, t_env **lst);

t_env	*convert_envp_to_lst(const char **envp, const char *sh_first_arg)
{
	t_env	*lst;

	lst = 0;
	if (!envp[0])
		create_basic_env(&lst, sh_first_arg);
	else
		copy_to_lst(envp, &lst);
	return (lst);
}

static void	create_basic_env(t_env **lst, const char *sh_first_arg)
{
	int		i;
	int		success;
	t_env	*new[5];

	new[0] = lst_new("PWD", getcwd(0, 0));
	new[1] = lst_new("PROMPT_COMMAND", "RETRN_VAL=$?;logger -p local6.debug"
			" \"$(history 1 | sed \"s/^[ ]*[0-9]\\+[ ]*//\" ) [$RETRN_VAL]\"");
	new[2] = lst_new("SHLVL", "1");
	new[3] = lst_new("_", sh_first_arg);
	new[4] = lst_new("TERM", "xterm-256color");
	i = -1;
	success = 0;
	while (++i < 5)
	{
		success += !!new[i];
		if (new[i])
			lstadd_back(lst, new[i]);
	}
	if (success != 5)
		lst_clear(lst);
	return ;
}

static void	copy_to_lst(const char **envp, t_env **lst)
{
	int		i;
	t_env	*new;
	char	*key;
	char	*value;

	i = 0;
	while (envp[i])
	{
		key = ft_substr(envp[i], 0, ft_strchrnul(envp[i], '=') - envp[i]);
		if (!key)
			return (lst_clear(lst));
		value = ft_strdup(getenv(key));
		new = lst_new(key, value);
		free(key);
		free(value);
		if (!new)
			return (lst_clear(lst));
		lstadd_back(lst, new);
		++i;
	}
	return ;
}
