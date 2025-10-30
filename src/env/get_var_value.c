#include "bigerrno.h"

char	*get_var_value(t_sh *sh, char *key)
{
	t_env	*var;

	var = 0;
	if (sh->env_hidden)
		var = find_key(&sh->env_hidden, key);
	if (!var && sh->env)
		var = find_key(&sh->env, key);
	if (var)
		return (var->value);
	return (0);
}
