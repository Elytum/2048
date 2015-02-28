/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/28 00:23:25 by achazal           #+#    #+#             */
/*   Updated: 2015/02/28 00:23:25 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game_2048.h"
#include <unistd.h>

unsigned int		ft_intlen(unsigned int n)
{
	unsigned int	len;

	len = 1;
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

void				ft_drawmap(t_env *e)
{
	unsigned int	x;
	unsigned int	y;

	mvprintw(0, 0, "The map is : ");
	y = 0;
	while (y < e->y)
	{
		x = 0;
		while (x < e->x)
		{
			mvprintw(10 * y + 1, 10 * x, "%i\n", e->map[y * e->y + x]);
			x++;
		}
		y++;
	}
	refresh();
}

void				ft_generaterandom(t_env *e)
{
	int				r;
	int				v;
	int				nb;
	unsigned int	*ptr;
	int				max;

	max = e->x * e->y;
	ptr = e->map;
	nb = 0;
	while (max--)
		if (*ptr++ == 0)
			nb++;
	r = rand() % (nb * 2);
	v = (r / nb) ? 2 : 4;
	if (r > nb)
		r -= nb;
	ptr = e->map;
	if (r == 0 && (*ptr = v))
		return ;
	while (r)
	{
		(*ptr == 0) ? r-- : r;
		ptr++;
	}
	*ptr = v;
}

int					ft_neighboor(t_env *e)
{
	unsigned		x;
	unsigned		y;

	x = 0;
	y = 0;
	while (y < e->y)
	{
		if (x > 0)
		{
			if (e->map[e->x * y + x] == e->map[e->x * y + x - 1])
				return (1);
		}
		if (y > 0)
		{
			if (e->map[e->x * y + x] == e->map[e->x * (y - 1) + x])
				return (1);
		}
		x++;
		if (x > e->x && ++y)
			x = 0;
	}
	return (0);
}

int					ft_anyat(t_env *e, unsigned int value)
{
	unsigned int	max;

	max = e->x * e->y - 1;
	while (max)
	{
		if (e->map[max--] == value)
			return (1);
	}
	return (0);
}
