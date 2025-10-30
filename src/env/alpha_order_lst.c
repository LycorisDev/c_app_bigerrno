#include "bigerrno.h"

static t_env	*lst_dup(t_env *src);

t_env	*alpha_order_lst(t_env **env)
{
	t_env	*start;
	t_env	*ordered;
	int		swapped;

	if (!*env)
		return (0);
	start = lst_dup(*env);
	if (!start)
		return (0);
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		ordered = start;
		while (ordered->next)
		{
			if (ft_strcmp(ordered->key, ordered->next->key) > 0)
			{
				swap_node_content(ordered, ordered->next);
				swapped = 1;
			}
			ordered = ordered->next;
		}
	}
	return (start);
}

static t_env	*lst_dup(t_env *src)
{
	t_env	*to_copy;
	t_env	*dup;
	t_env	*node;
	int		len;
	int		i;

	to_copy = src;
	dup = 0;
	len = lst_size(&src);
	i = 0;
	while (to_copy && i < len)
	{
		node = add_node(&dup, to_copy->key, to_copy->value);
		if (!node)
		{
			lst_clear(&dup);
			return (0);
		}
		to_copy = to_copy->next;
		++i;
	}
	return (dup);
}
