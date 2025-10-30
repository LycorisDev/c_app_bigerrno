#include "bigerrno.h"

static void		manage_env(t_env **env_hidden, t_env *env_var, t_env *current,
					char **append_value);

void	update_env(t_env **env, t_env **env_hidden)
{
	t_env	*current;
	t_env	*next;
	t_env	*env_var;
	char	*append_value;

	if (!env_hidden || !*env_hidden)
		return ;
	current = *env_hidden;
	append_value = 0;
	while (current)
	{
		next = current->next;
		env_var = find_key(env, current->key);
		if (env_var && ft_strcmp(current->key, "_") != 0)
			manage_env(env_hidden, env_var, current, &append_value);
		current = next;
	}
	return ;
}

static void	manage_env(t_env **env_hidden, t_env *env_var, t_env *current,
				char **append_value)
{
	if (env_var->key[ft_strlen(env_var->key) - 1] == '+')
		*append_value = ft_strjoin(env_var->value, current->value);
	if (env_var->value)
	{
		free(env_var->value);
		env_var->value = 0;
	}
	if (*append_value)
		env_var->value = *append_value;
	else
		env_var->value = ft_strdup(current->value);
	env_var->withvalue = 1;
	if (current == *env_hidden)
		*env_hidden = current->next;
	clear_node(current);
}
