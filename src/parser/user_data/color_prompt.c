#include "bigerrno.h"

#define PROMPT_COLOR_GREEN  "\001\e[1;32m\002"
#define PROMPT_COLOR_PEACH  "\001\e[1;38;5;208m\002"
#define PROMPT_COLOR_POWDER "\001\e[1;34m\002"
#define PROMPT_COLOR_AZUR   "\001\e[1;38;5;18m\002"
#define PROMPT_COLOR_PURPLE "\001\e[1;38;5;183m\002"
#define PROMPT_COLOR_PINK   "\001\e[1;35m\002"

void	set_prompt_color(t_sh *sh, t_color color)
{
	const char	*str_color;

	str_color = 0;
	if (color == E_COLOR_GNOME)
	{
		sh->prompt_color1 = PROMPT_COLOR_GREEN;
		sh->prompt_color2 = PROMPT_COLOR_POWDER;
		return ;
	}
	else if (color == E_COLOR_PEACH)
		str_color = PROMPT_COLOR_PEACH;
	else if (color == E_COLOR_POWDER)
		str_color = PROMPT_COLOR_POWDER;
	else if (color == E_COLOR_AZUR)
		str_color = PROMPT_COLOR_AZUR;
	else if (color == E_COLOR_PURPLE)
		str_color = PROMPT_COLOR_PURPLE;
	else if (color == E_COLOR_PINK)
		str_color = PROMPT_COLOR_PINK;
	sh->prompt_color1 = str_color;
	sh->prompt_color2 = str_color;
	return ;
}
