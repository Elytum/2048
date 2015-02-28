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

// int			ft_power2(char power)
// {
// 	int		n;

// 	n = 1;
// 	while (power--)
// 		n <<= 2;
// 	return (n);
// }

void		ft_drawmap(t_env *e)
{
	int		x;
	int		y;

	write(1, "\nThe map is : \n", 15);
	y = 0;
	while (y < e->y)
	{
		x = 0;
		while (x < e->x)
		{
			ft_putnbr(e->map[y * e->y + x++]);
			write (1, "\t", 1);
		}
		write (1, "\n", 1);
		y++;
	}
}

void		ft_generaterandom(t_env *e)
{
	int		r;
	int		v;
	int		nb;
	int		*ptr;
	int		max;

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

int			ft_neighboor(t_env *e)
{
	int		x;
	int		y;

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

int			ft_anyat(t_env *e, int value)
{
	int		max;

	max = e->x * e->y - 1;
	while (max >= 0)
	{
		if (e->map[max--] == value)
			return (1);
	}
	return (0);
}
