#include "bigerrno.h"

int	builtin_unset(t_sh *sh, char **arg)
{
	int		n;
	t_env	*node;

	n = 1;
	while (arg[n])
	{
		node = find_key(&sh->env, arg[n]);
		if (node == sh->env)
			sh->env = node->next;
		if (!node && !ft_strcmp(arg[n], "OLDPWD"))
		{
			node = find_key(&sh->hidden, arg[n]);
			if (node && node == sh->hidden)
				sh->hidden = node->next;
		}
		if (node)
			clear_node(node);
		++n;
	}
	return (0);
}
