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
#define BUFF_SIZE 2048

int		ft_continue(int map[][BUFF_SIZE], char sx, char sy)
{
	int	r;

	if (!(!(*map)[0] || !(*map)[1] || !(*map)[2] || !(*map)[3] ||
		!(*map)[4] || !(*map)[5] || !(*map)[6] || !(*map)[7] ||
		!(*map)[8]))
		return (0);
	while (1)
	{
		r = rand() % 32;
		if ((*map)[r % 16] == 0)
		{
			(*map)[r % 16] = (r / 16) ? 2 : 4;
			break ;
		}
	}
	return ((!(*map)[0] || !(*map)[1] || !(*map)[2] || !(*map)[3] ||
		!(*map)[4] || !(*map)[5] || !(*map)[6] || !(*map)[7] ||
		!(*map)[8]) || ((*map)[0] == (*map)[1] || (*map)[1] == (*map)[2] ||
		(*map)[3] == (*map)[4] || (*map)[4] == (*map)[5] ||
		(*map)[6] == (*map)[7] || (*map)[7] == (*map)[8] ||
		(*map)[0] == (*map)[3] || (*map)[3] == (*map)[6] ||
		(*map)[1] == (*map)[4] || (*map)[4] == (*map)[7] ||
		(*map)[2] == (*map)[5] || (*map)[5] == (*map)[8]));
}

// int			ft_move(int map[][9], int mx, int my)
// {
// 	char	x;
// 	char	y;
// 	char	tx;
// 	char	ty;
// 	char	pursue;
// 	char	m;
// 	int	l;

// 	l = 0;

// 	y = 0;
// 	m = 0;
// 	pursue = 1;
// 	while (pursue)// && !(pursue = 0))
// 	{
// 		pursue = 0;
// 		l++;
// 		while (y < 3)
// 		{
// 			x = 0;
// 			while (x < 3)
// 			{
// 				if ((*map)[x + y * 3])
// 				{
// 					tx = x + mx;
// 					ty = y + my;
// 					if (tx >= 0 && tx < 3 && ty >= 0 && ty < 3)
// 					{
// 					dprintf(1, "x : %i, y : %i = %i vs tx : %i, ty : %i = %i\n", x, y, (*map)[x + y * 3], tx, ty, (*map)[tx + ty * 3]);
// 						if (!(*map)[tx + ty * 3])
// 						{
// 							(*map)[tx + ty * 3] = (*map)[x + y * 3];
// 							(*map)[x + y * 3] = 0;
// 							pursue = 1;
// 							m = 1;
// 						}
// 						else if ((*map)[x + y * 3] == (*map)[tx + ty * 3])
// 						{
// 							(*map)[x + y * 3] = 0;
// 							(*map)[tx + ty * 3] *= 2;
// 							pursue = 1;
// 							m = 1;
// 						}
// 					}
// 				}
// 				x++;
// 			}
// 			y++;
// 		}
// 	}
// 	dprintf(1, "Looped %i times, and m = %i\n", l, m);
// 	return (m);
// }

void		ft_putnbr(int n)
{
	char	c;

	if (n > 9)
	{
		ft_putnbr(n / 10);
		c = n % 10 + '0';
		write (1, &c, 1);
	}
	else
	{
		c = n % 10 + '0';
		write (1, &c, 1);
	}
}

void		ft_drawmap(int map[BUFF_SIZE], char sx, char sy)
{
	int		x;
	int		y;

	write(1, "\nThe map is : \n", 15);
	y = 0;
	while (y < sy)
	{
		x = 0;
		while (x < sx)
		{
			ft_putnbr(map[y * sy + x++]);
			write (1, "\t", 1);
		}
		write (1, "\n", 1);
		y++;
	}
}

char		ft_move(int map[][BUFF_SIZE], char past, char next)
{
	write (1, "\nMOVE\n", 6);
	if ((*map)[next])
	{
		(*map)[next] *= 2;
		(*map)[past] = 0;
	}
	else
	{
		(*map)[next] = (*map)[past];
		(*map)[past] = 0;
	}
	return (1);
}

char		ft_up(int map[][BUFF_SIZE], char sx, char sy)
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
		while (sy < y)
		{
			x = 0;
			while (x < sx)
			{
				if ((*map)[sx * y + x] && ((*map)[sx * (y - 1) + x] == 0 ||
					((*map)[sx * y + x] == (*map)[sx * (y - 1) + x])) && (l = 1))
					re = ft_move(map, 3, 0);
				x++;
			}
			y++;
		}
	}
	return (re);
}

char		ft_down(int map[][BUFF_SIZE], char sx, char sy)
{
	char	l;
	char	re;
	char	x;
	char	y;

	l = 1;
	re = 0;
	while (l && !(l = 0))
	{
		y = sy;
		while (y >= 0);
		{
			x = 0;
			while (x < sx)
			{
				if ((*map)[sx * y + x] && ((*map)[sx * (y + 1) + x] == 0 ||
					((*map)[sx * y + x] == (*map)[sx * (y + 1) + x])) && (l = 1))
					re = ft_move(map, 3, 0);
				x++;
			}
			y--;
		}
	}
	return (re);
}

char		ft_left(int map[][BUFF_SIZE], char sx, char sy)
{
	char	l;
	char	re;
	char	x;
	char	y;

	l = 1;
	re = 0;
	x = 1;
	while (l && !(l = 0))
	{
		while (x < sx);
		{
			y = 0;
			while (y < sy)
			{
				if ((*map)[sx * y + x] && ((*map)[sx * y + x + 1] == 0 ||
					((*map)[sx * y + x] == (*map)[sx * y + x + 1])) && (l = 1))
					re = ft_move(map, 3, 0);
				y++;
			}
			x++;
		}
	}
	return (re);
}

char		ft_right(int map[][BUFF_SIZE], char sx, char sy)
{
	char	l;
	char	re;
	char	x;
	char	y;

	l = 1;
	re = 0;
	x = sx - 1;
	while (l && !(l = 0))
	{
		while (x >= 0);
		{
			y = 0;
			while (y < sy)
			{
				if ((*map)[sx * y + x] && ((*map)[sx * y + x - 1] == 0 ||
					((*map)[sx * y + x] == (*map)[sx * y + x - 1])) && (l = 1))
					re = ft_move(map, 3, 0);
				y++;
			}
			x--;
		}
	}
	return (re);
}


int			main(void)
{
	int		map[BUFF_SIZE] = {0};
	char	buff[2] = {0};
	int		check;
	int		play;

	check = 0;
	play = 1;
	ft_continue(&map, 4, 4);
	ft_drawmap(map, 4, 4);
	while (play)
	{
		read(1, buff, 2);
		if (*buff == 'w')
			check = ft_up(&map, 4, 4);
		else if (*buff == 's')
			check = ft_down(&map, 4, 4);
		else if (*buff == 'a')
			check = ft_left(&map, 4, 4);
		else if (*buff == 'd')
			check = ft_right(&map, 4, 4);
		if (check && !(check = 0))
			play = ft_continue(&map, 4, 4);
		ft_drawmap(map, 4, 4);
		buff[0] = '\0';
	}
}
