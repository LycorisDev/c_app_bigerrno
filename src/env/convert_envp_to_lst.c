#include "bigerrno.h"

static void		get_small_env(t_env	**lst, const char *sh_first_arg);
static void		copy_to_lst(const char **env, t_env **lst);
static int		continued_occurrence(const char *s, char c);
static void		lst_in_p_order(t_env **env);
static t_env	*find_smallest_p(t_env **p_order);
static t_env	*find_biggest_p(t_env **p_order);
static t_env	*next_smallest(t_env **p_order, t_env *smallest);

t_env	*convert_envp_to_lst(const char **envp, const char *sh_first_arg)
{
	t_env	*lst;

	lst = 0;
	if (!envp[0])
		get_small_env(&lst, sh_first_arg);
	else
		copy_to_lst(envp, &lst);
	if (lst)
		lst_in_p_order(&lst);
	return (lst);
}

static void	get_small_env(t_env	**lst, const char *sh_first_arg)
{
	t_env	*new;

	new = lst_new("PWD", getcwd(0, 0));
	if (!new)
		lst_clear(lst);
	lstadd_back(lst, new);
	new = lst_new("PROMPT_COMMAND", "RETRN_VAL=$?;logger -p local6.debug"
			" \"$(history 1 | sed \"s/^[ ]*[0-9]\\+[ ]*//\" ) [$RETRN_VAL]\"");
	if (!new)
		lst_clear(lst);
	lstadd_back(lst, new);
	new = lst_new("SHLVL", "1");
	if (!new)
		lst_clear(lst);
	lstadd_back(lst, new);
	new = lst_new("_", sh_first_arg);
	if (!new)
		lst_clear(lst);
	lstadd_back(lst, new);
	new = lst_new("TERM", "xterm-256color");
	if (!new)
		lst_clear(lst);
	lstadd_back(lst, new);
	return ;
}

static void	copy_to_lst(const char **envp, t_env **lst)
{
	t_env	*new;
	char	*key;
	char	*value;
	int		size;
	int		i;

	i = 0;
	while (envp[i])
	{
		size = continued_occurrence(envp[i], '=');
		key = ft_substr(envp[i], 0, size);
		if (!key)
			break ;
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

static int	continued_occurrence(const char *s, char c)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		++i;
	}
	if (c == '\n')
		return (-1);
	return (i);
}

static void	lst_in_p_order(t_env **lst)
{
	t_env	*smallest;
	t_env	*next_small;
	t_env	*biggest;

	if (!lst || !*lst)
		return ;
	smallest = find_smallest_p(lst);
	biggest = find_biggest_p(lst);
	if (!smallest || !biggest)
		return ;
	while (smallest != biggest)
	{
		next_small = next_smallest(lst, smallest);
		if (!next_small)
			break ;
		swap_node_content(smallest, next_small);
		smallest = next_small;
	}
	return ;
}

static t_env	*find_smallest_p(t_env **p_order)
{
	t_env	*tmp;
	t_env	*smallest;

	tmp = *p_order;
	smallest = *p_order;
	while (tmp)
	{
		if (smallest > tmp)
			smallest = tmp;
		tmp = tmp->next;
	}
	return (smallest);
}

static t_env	*find_biggest_p(t_env **p_order)
{
	t_env	*tmp;
	t_env	*biggest;

	tmp = *p_order;
	biggest = *p_order;
	while (tmp)
	{
		if (biggest < tmp)
			biggest = tmp;
		tmp = tmp->next;
	}
	return (biggest);
}

static t_env	*next_smallest(t_env **p_order, t_env *smallest)
{
	t_env	*next_small;
	t_env	*tmp;

	tmp = *p_order;
	next_small = 0;
	if (!p_order)
		return (0);
	if (!smallest)
		return (0);
	while (tmp)
	{
		if (tmp > smallest && (!next_small || tmp < next_small))
			next_small = tmp;
		tmp = tmp->next;
	}
	return (next_small);
}
