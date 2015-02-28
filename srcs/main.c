/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/27 18:42:42 by achazal           #+#    #+#             */
/*   Updated: 2015/02/27 18:42:45 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game_2048.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define WIDTH 4
#define HEIGHT 4

int				ft_continue(t_env *e)
{

	if (!(ft_anyat(e, 0)))
		return (0);
	ft_generaterandom(e);
	return (ft_anyat(e, 0) || ft_neighboor(e));
}

void			ft_drawborder(unsigned int x1, unsigned int x2, unsigned int y1, unsigned int y2)
{
	unsigned	i;

	i = x1;
	while (i <= x2)
	{
		mvprintw(y1, i, "_");
		mvprintw(y2, i, "_");
		i++;
	}
	i = y1 + 1;
	while (i <= y2)
	{
		mvprintw(i, x1, "|");
		mvprintw(i, x2, "|");
		i++;
	}
}

void				ft_drawblocks(t_env *e)
{
	unsigned int	x;
	unsigned int	y;
	unsigned int	len;
	unsigned int	v;

	y = 0;
	while (y < e->y)
	{
		x = 0;
		while (x < e->x)
		{
			ft_drawborder(e->box + e->sbx * x, e->box + e->sbx * (x + 1),
				e->boy + e->sby * y + 1, e->boy + e->sby * (y + 1) + 1);
			v = e->map[y * e->x + x];
			len = ft_intlen(v);
			if (e->sbx - 2 >= len)
				mvprintw((int)(e->boy + e->sby * (y + .5) + 1),
					e->box + e->sbx * x + 1 + (e->sbx - len) / 2, "%i", v);
			x++;
		}
		y++;
	}
}

t_env			*ft_init_env(int ac, char **av)
{
	t_env		*e;

	if (!(e = (t_env *)ft_memalloc(sizeof(t_env))))
		return (NULL);
	e->x = WIDTH;
	e->y = HEIGHT;
	initscr();
	noecho();
	curs_set(FALSE);
	keypad(stdscr, TRUE);
	e->player_name = ft_strdup("Elytum");
	e->player_name_len = ft_strlen(e->player_name);
	e->player_score = 0;
	if (!(e->map = (unsigned int *)ft_memalloc(sizeof(unsigned int) *
		(e->x * e->y))))
		return (NULL);
	e->pastkey = '\0';
	ft_generaterandom(e);
	e->play = 1;
	e->check = 0;
	return (e);
	ac++;
	av++;
}

unsigned int	ft_biggestword(t_env *e)
{
	unsigned int max;
	unsigned int len;
	unsigned int tmp;

	len = e->x * e->y - 1;
	max = 0;
	while (42)
	{
		tmp = ft_intlen(e->map[len]);
		if (tmp > max)
			max = tmp;
		if (!len)
			break ;
		len--;
	}
	return (max);
}

void			ft_actualize(t_env *e)
{
	e->sbx = e->sx / e->x - 2;
	e->sby = e->sy / e->y - 2;
	e->box = (e->sx - e->sbx * e->x) / 2;
	e->boy = (e->sy - e->sby * e->y) / 2;
}

void			ft_refresh(t_env *e)
{
	mvprintw(0, (e->sx - e->player_name_len) / 2, e->player_name);
	mvprintw(1, (e->sx - ft_intlen(e->player_score) - 8) / 2,
		"Score : %i", e->player_score);
	if (e->pastkey == '\n')
	{
		mvprintw(2, (e->sx - ft_strlen(QUIT1)) / 2, QUIT1);
		mvprintw(3, (e->sx - ft_strlen(QUIT2)) / 2, QUIT2);
	}
	ft_drawblocks(e);
}

void			ft_event(t_env *e, int key)
{
	if (key == KEY_UP || key == 'w')
		ft_up(e);
	if (key == KEY_DOWN || key == 's')
		ft_down(e);
	if (key == KEY_LEFT || key == 'a')
		ft_left(e);
	if (key == KEY_RIGHT || key == 'd')
		ft_right(e);
	e->play = ft_continue(e);
}

// void			ft_save(t_env *e)
// {
// 	int fd = open ("/tmp/test.svg", O_RDWR|O_CREAT,777);
// }

void			ft_event_special(t_env *e, int key)
{
	if (key == '\n')
	{
		if (e->pastkey == '\n')
			e->play = 0;
	}
}

void			ft_loop(t_env *e)
{
	int c;

	while (e->play)
	{
		getmaxyx(stdscr, e->sy, e->sx);
		ft_actualize(e);
		if (e->sy < 3 * e->y || e->sx < 3 * e->x ||
			ft_biggestword(e) > e->sbx - 2 || e->player_name_len > e->sx ||
			e->sx < ft_intlen(e->player_score) + 8 ||
			e->sx < ft_strlen(QUIT1) || e->sx < ft_strlen(QUIT2))
			mvprintw(0, 0, "Screen too little");
		else
		{
			ft_refresh(e);
			c = wgetch(stdscr);
			if (c == KEY_UP || c == KEY_DOWN || c == KEY_LEFT || c == KEY_RIGHT ||
				c == 'w' || c == 's' || c == 'a' || c == 'd' || c == 27)
				ft_event(e, c);
			else if (c == 27 || c == '\n')
				ft_event_special(e, c);
			e->pastkey = c;
		}
		refresh();
		clear();
		usleep(100000);
	}
}

int				main(int ac, char **av)
{
	t_env		*e;

	if (!(e = ft_init_env(ac, av)))
		return (-1);
	ft_loop(e);
	// ft_save(e);
}
