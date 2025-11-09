#include "bigerrno.h"

static char	*get_input(t_sh *sh, const char *prompt);
static void	extract_first_line(t_sh *sh);

void	add_input_to_buffer(t_sh *sh, const char *prompt)
{
	static int	prev_signum;
	int			stdin_dup;

	prev_signum = g_signum;
	g_signum = 0;
	stdin_dup = dup(0);
	if (stdin_dup < 0)
		return ;
	set_signal_handling(SIGINT, signal_handler);
	sh->input = get_input(sh, prompt);
	set_signal_handling(SIGINT, SIG_IGN);
	dup2(stdin_dup, 0);
	close(stdin_dup);
	if (!sh->input && !g_signum)
		g_signum = EOF;
	else if (g_signum == SIGINT)
	{
		sh->exit_code = g_signum + 128;
		if (sh->is_tty && (!prev_signum || !sh->valid_term))
			ft_putstr(1, "\n");
		free_entire_array((void **)sh->rl.buf, free);
		sh->rl.buf = 0;
	}
	extract_first_line(sh);
	return ;
}

static char	*get_input(t_sh *sh, const char *prompt)
{
	char	*input;
	size_t	len;

	if (sh->input)
		return (sh->input);
	else if (sh->is_tty)
		return (readline(prompt));
	input = ft_gnl(0);
	if (input)
	{
		len = ft_strlen(input);
		if (len && input[len - 1] == '\n')
			input[len - 1] = 0;
	}
	return (input);
}

static void	extract_first_line(t_sh *sh)
{
	char	*p_nl;
	char	*left;
	char	*right;

	if (!sh->input)
		return ;
	p_nl = ft_strchrnul(sh->input, '\n');
	left = ft_substr(sh->input, 0, p_nl - sh->input);
	right = 0;
	if (p_nl[0])
		right = ft_substr(p_nl, 1, ft_strlen(p_nl + 1));
	if (right && !right[0])
	{
		free(right);
		right = 0;
	}
	free(sh->input);
	sh->input = right;
	insert_array_element((void ***)&sh->rl.buf, (void *)left,
		get_array_length((void **)sh->rl.buf));
	return ;
}
