/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/28 00:21:47 by achazal           #+#    #+#             */
/*   Updated: 2015/02/28 00:21:50 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game_2048.h"

static char	ft_move(int **map, int past, int next)
{
	if ((*map)[next])
	{
		(*map)[next] <<= 1;
		(*map)[past] = 0;
	}
	else
	{
		(*map)[next] = (*map)[past];
		(*map)[past] = 0;
	}
	return (1);
}

char		ft_up(t_env *e)
{
	char	l;
	char	re;
	char	x;
	char	y;

	l = 1;
	re = 0;
	while (l && !(l = 0))
	{
		y = 1;
		while (y < e->y)
		{
			x = 0;
			while (x < e->x)
			{
				if (e->map[e->x * y + x] && (e->map[e->x * (y - 1) + x] == 0 ||
					(e->map[e->x * y + x] == e->map[e->x * (y - 1) + x])) &&
					(l = 1))
					re = ft_move(&(e->map), e->x * y + x, e->x * (y - 1) + x);
				x++;
			}
			y++;
		}
	}
	return (re);
}

char		ft_down(t_env *e)
{
	char	l;
	char	re;
	char	x;
	char	y;

	l = 1;
	re = 0;
	while (l && !(l = 0))
	{
		y = e->y - 2;
		while (y >= 0)
		{
			x = 0;
			while (x < e->x)
			{
				if (e->map[e->x * y + x] && (e->map[e->x * (y + 1) + x] == 0 ||
					(e->map[e->x * y + x] == e->map[e->x * (y + 1) + x])) &&
					(l = 1))
					re = ft_move(&(e->map), e->x * y + x, e->x * (y + 1) + x);
				x++;
			}
			y--;
		}
	}
	return (re);
}

char		ft_left(t_env *e)
{
	char	l;
	char	re;
	char	x;
	char	y;

	l = 1;
	re = 0;
	while (l && !(l = 0))
	{
		x = 1;
		while (x < e->x)
		{
			y = 0;
			while (y < e->y)
			{
				if (e->map[e->x * y + x] && (e->map[e->x * y + x - 1] == 0 ||
					(e->map[e->x * y + x] == e->map[e->x * y + x - 1])) && (l = 1))
					re = ft_move(&(e->map), e->x * y + x, e->x * y + x - 1);
				y++;
			}
			x++;
		}
	}
	return (re);
}

char		ft_right(t_env *e)
{
	char	l;
	char	re;
	char	x;
	char	y;

	l = 1;
	re = 0;
	while (l && !(l = 0))
	{
		x = e->x - 2;
		while (x >= 0)
		{
			y = 0;
			while (y < e->y)
			{
				if (e->map[e->x * y + x] && (e->map[e->x * y + x + 1] == 0 ||
					(e->map[e->x * y + x] == e->map[e->x * y + x + 1])) && (l = 1))
					re = ft_move(&(e->map), e->x * y + x, e->x * y + x + 1);
				y++;
			}
			x--;
		}
	}
	return (re);
}
