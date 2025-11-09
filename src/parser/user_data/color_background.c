#include "bigerrno.h"

#define BACKGROUND_COLOR_GNOME  "\033]11;rgb:3030/0a0a/2424\007"
#define BACKGROUND_COLOR_PEACH  "\033]11;rgb:aaaa/5555/5050\007"
#define BACKGROUND_COLOR_POWDER "\033]11;rgb:afaf/d0d0/e1e1\007"
#define BACKGROUND_COLOR_AZUR   "\033]11;rgb:1010/5050/aaaa\007"
#define BACKGROUND_COLOR_PURPLE "\033]11;rgb:3030/0a0a/5050\007"
#define BACKGROUND_COLOR_PINK   "\033]11;rgb:aaaa/5555/9999\007"

void	handle_default_background_color(int set)
{
	static char		color[42];
	struct termios	oldt;
	struct termios	newt;
	size_t			i;

	if (!color[0])
	{
		tcgetattr(0, &oldt);
		newt = oldt;
		newt.c_lflag &= ~(ECHO | ICANON);
		tcsetattr(0, TCSANOW, &newt);
		ft_putstr(1, "\033]11;?\007");
		i = 0;
		while (i < sizeof(color) - 1)
		{
			if (read(0, &color[i], 1) != 1 || color[i++] == '\007')
				break ;
		}
		color[i] = 0;
		tcsetattr(0, TCSANOW, &oldt);
	}
	if (color[0] && set)
		ft_putstr(1, color);
	return ;
}

void	set_background_color(t_color color)
{
	if (color == E_COLOR_GNOME)
		ft_putstr(1, BACKGROUND_COLOR_GNOME);
	else if (color == E_COLOR_PEACH)
		ft_putstr(1, BACKGROUND_COLOR_PEACH);
	else if (color == E_COLOR_POWDER)
		ft_putstr(1, BACKGROUND_COLOR_POWDER);
	else if (color == E_COLOR_AZUR)
		ft_putstr(1, BACKGROUND_COLOR_AZUR);
	else if (color == E_COLOR_PURPLE)
		ft_putstr(1, BACKGROUND_COLOR_PURPLE);
	else if (color == E_COLOR_PINK)
		ft_putstr(1, BACKGROUND_COLOR_PINK);
	return ;
}
