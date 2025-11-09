#include "bigerrno.h"

int	builtin_set(t_env *env_hidden, char **arg)
{
	t_env	*sorted;
	t_env	*tmp;

	if (!env_hidden || get_array_length((void **)arg) > 1)
		return (0);
	sorted = alpha_order_lst(&env_hidden);
	tmp = sorted;
	while (tmp)
	{
		ft_printf("%s=", tmp->key);
		if (tmp->value)
			ft_printf("%s", tmp->value);
		ft_printf("\n");
		tmp = tmp->next;
	}
	lst_clear(&sorted);
	return (0);
}
