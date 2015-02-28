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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../includes/game_2048.h"
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

	mvprintw(0, 0, "x1 = %i, x2 = %i, y1 = %i, y2 = %i\n", x1, x2, y1, y2);
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

	y = 0;
	while (y < e->y)
	{
		x = 0;
		while (x < e->x)
		{
			ft_drawborder(e->box + e->sbx * x, e->box + e->sbx * (x + 1),
				e->boy + e->sby * y, e->boy + e->sby * (y + 1));
			len = ft_intlen(e->map[y * e->y + x]);
			if (e->sbx - 2 >= len)
				mvprintw((int)(e->boy + e->sby * (y + .5)),
					e->box + e->sbx * x + 1 + (e->sbx - len - 1) / 2, "%i", e->map[y * e->y + x]);
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
	if (!(e->map = (unsigned int *)ft_memalloc(sizeof(unsigned int) *
		(e->x * e->y))))
		return (NULL);
	// e->map[0] = 2048;
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
	while (len)
	{
		tmp = ft_intlen(e->map[len--]);
		if (tmp > max)
			max = tmp;
	}
	return (max);
}

void			ft_loop(t_env *e)
{
	while (e->play)
	{
		getmaxyx(stdscr, e->sy, e->sx);
		if (e->sy < 4 * e->y || e->sx < 4 * e->x || ft_biggestword(e) > e->x - 2)
			mvprintw(0, 0, "Screen too little");
		else
		{
			e->sbx = e->sx / e->x - 1;
			e->sby = e->sy / e->y - 1;
			e->box = (e->sx - e->sbx * e->x) / 2;
			e->boy = (e->sy - e->sby * e->y) / 2;
			ft_drawblocks(e);
		}
		refresh();
		clear();
		usleep(100000);
	}
}

int				main(int ac, char **av)
{
	char		buff[2] = {0};
	t_env		*e;

	if (!(e = ft_init_env(ac, av)))
		return (-1);
	ft_loop(e);
	ft_continue(e);
	ft_drawmap(e);
	while (e->play)
	{
		read(1, buff, 2);
		if (*buff == 'w')
			e->check = ft_up(e);
		else if (*buff == 's')
			e->check = ft_down(e);
		else if (*buff == 'a')
			e->check = ft_left(e);
		else if (*buff == 'd')
			e->check = ft_right(e);
		if (e->check && !(e->check = 0))
			e->play = ft_continue(e);
		ft_drawmap(e);
		buff[0] = '\0';
	}
}
