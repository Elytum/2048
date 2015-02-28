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
#include <unistd.h>

static char	ft_move(t_env *e, unsigned int x1, unsigned int y1, unsigned int moves[2])
{
	unsigned int	x2;
	unsigned int	y2;

	x2 = x1 + moves[0];
	y2 = y1 + moves[1];
//truc moche
	// if (e->map[y2 * e->x + x2] == 0)
	// {
	// 	x2 += moves[0];
	// }
	//c est la "possibilite " qui crashait le moins ...
	if (e->map[y2 * e->x + x2])
	{
		e->map[y2 * e->x + x2] <<= 1;
		e->player_score += e->map[y2 * e->x + x2];
		e->map[y1 * e->x + x1] = 0;
		return (1);
	}
	while (y2 > 0 && x2 > 0 && y2 < e->y - 1 && x2 < e->x - 1 &&
		!e->map[y2 * e->x + x2] &&
		!e->map[(y2 + moves[1]) * e->x + x2 + moves[0]])
	{
		x2 += moves[0];
		y2 += moves[1];
	}
	e->map[y2 * e->x + x2] = e->map[y1 * e->x + x1];
	e->map[y1 * e->x + x1] = 0;
	return (1);
}

char		ft_up(t_env *e)
{
	char			re;
	unsigned int	moves[2];
	unsigned int	x;
	unsigned int	y;

	re = 0;
	y = 1;
	moves[0] = 0;
	moves[1] = -1;
	while (y < e->y)
	{
		x = 0;
		while (x < e->x)
		{
			if (e->map[e->x * y + x] && (e->map[e->x * (y - 1) + x] == 0 ||
				(e->map[e->x * y + x] == e->map[e->x * (y - 1) + x])))
				re = ft_move(e, x, y, moves);
			x++;
		}
		y++;
	}
	return (re);
}

char		ft_down(t_env *e)
{
	char			re;
	unsigned int	moves[2];
	unsigned int	x;
	unsigned int	y;

	re = 0;
	moves[0] = 0;
	moves[1] = 1;
	y = e->y - 2;
	while (42)
	{
		x = 0;
		while (x < e->x)
		{
			if (e->map[e->x * y + x] && (e->map[e->x * (y + 1) + x] == 0 ||
				(e->map[e->x * y + x] == e->map[e->x * (y + 1) + x])))
				re = ft_move(e, x, y, moves);
			x++;
		}
		if (!y)
			return (re);
		y--;
	}
	return (re);
}

char		ft_left(t_env *e)
{
	char			re;
	unsigned int	moves[2];
	unsigned int	x;
	unsigned int	y;

	re = 0;
	moves[0] = -1;
	moves[1] = 0;
	x = 1;
	while (x < e->x)
	{
		y = 0;
		while (y < e->y)
		{
			if (e->map[e->x * y + x] && (e->map[e->x * y + x - 1] == 0 ||
				(e->map[e->x * y + x] == e->map[e->x * y + x - 1])))
				re = ft_move(e, x, y, moves);
			y++;
		}
		x++;
	}
	return (re);
}

char		ft_right(t_env *e)
{
	char	re;
	unsigned int	moves[2];
	unsigned int	x;
	unsigned int	y;

	re = 0;
	moves[0] = 1;
	moves[1] = 0;
	x = e->x - 2;
	while (42)
	{
		y = 0;
		while (y < e->y)
		{
			if (e->map[e->x * y + x] && (e->map[e->x * y + x + 1] == 0 ||
				(e->map[e->x * y + x] == e->map[e->x * y + x + 1])))
				re = ft_move(e, x, y, moves);
			y++;
		}
		if (!x)
			return (re);
		x--;
	}
	return (re);
}
