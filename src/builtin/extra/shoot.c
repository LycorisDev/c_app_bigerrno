#include "bigerrno.h"

static void	get_terminal_size(int *rows_cols);
static void	execute_in_child(int pipefd[2]);
static void	execute_in_parent(int pipefd[2], int *rows_cols);
static void	animate_shoot(int cols);

int	builtin_shoot(t_sh *sh, char **arg)
{
	int	rows_cols[2];

	if (get_array_length((void **)arg) > 1)
		ft_putstr(2, "Don't shoot anything!\n");
	else
	{
		sh->color_scheme = E_COLOR_PINK;
		ft_putstr(1, "\e[35m  "SHELL"$ \e[0m");
		get_terminal_size(rows_cols);
		animate_shoot(rows_cols[1]);
		ft_putstr(1, "\a");
		ft_putstr(1, "\033[H\033[J");
	}
	return (0);
}

static void	get_terminal_size(int *rows_cols)
{
	int				cpid;
	int				pipefd[2];
	struct termios	oldt;
	struct termios	newt;

	ft_bzero(rows_cols, 2 * sizeof(int));
	tcgetattr(0, &oldt);
	ft_memcpy(&newt, &oldt, sizeof(struct termios));
	newt.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(0, TCSANOW, &newt);
	if (pipe(pipefd) < 0)
		return ;
	cpid = fork();
	if (cpid < 0)
		return ;
	if (!cpid)
		execute_in_child(pipefd);
	else
	{
		execute_in_parent(pipefd, rows_cols);
		waitpid(cpid, 0, 0);
	}
	tcsetattr(0, TCSANOW, &oldt);
	return ;
}

static void	execute_in_child(int pipefd[2])
{
	char	buffer[124];
	int		n_bytes;

	close(pipefd[0]);
	ft_putstr(1, "\e[18t");
	n_bytes = read(0, buffer, sizeof(buffer) - 1);
	if (n_bytes > 0)
	{
		buffer[n_bytes] = '\0';
		ft_putstr(pipefd[1], buffer);
	}
	close(pipefd[1]);
	exit(0);
	return ;
}

static void	execute_in_parent(int pipefd[2], int *rows_cols)
{
	char	**split;
	char	buffer[124];
	int		n_bytes;

	close(pipefd[1]);
	n_bytes = read(pipefd[0], buffer, sizeof(buffer) - 1);
	buffer[n_bytes] = '\0';
	split = ft_split(buffer + 4, ';');
	if (split && split[0] && split[1])
	{
		rows_cols[0] = atoi(split[0]);
		rows_cols[1] = atoi(split[1]);
	}
	free_entire_array((void **)split, free);
	close(pipefd[0]);
	return ;
}

static void	animate_shoot(int cols)
{
	int		pixel_pos;
	int		i;
	float	v;

	pixel_pos = -1;
	v = 0.1;
	while (++pixel_pos < cols && !g_signum)
	{
		ft_putstr(1, "\r");
		i = -1;
		while (++i < pixel_pos)
			ft_putstr(1, " ");
		ft_putstr(1, "\e[35m•\e[0m");
		i = 0;
		while (i < 80000000 / v)
			++i;
		v = ft_clamp(v + 0.2, 0.1, 10.0);
	}
	ft_putstr(1, "\r");
	i = -1;
	while (++i < cols)
		ft_putstr(1, " ");
	ft_putstr(1, "\r");
	return ;
}
