#include "bigerrno.h"

static t_env	*merge_lst(t_env *lst1, t_env *lst2);
static char		**convert_to_arr(t_env *env);

char	**convert_env_to_arr(t_sh *sh)
{
	t_env	*env_list;
	char	**env_arr;

	env_list = merge_lst(sh->env_local, sh->env);
	env_arr = convert_to_arr(env_list);
	lst_clear(&env_list);
	return (env_arr);
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

static char	**convert_to_arr(t_env *env)
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
