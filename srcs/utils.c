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

size_t				ft_strlen(const char *str)
{
    register char	*ptr;

    ptr = (char *)str;
    while (*ptr)
        ptr++;
    return (ptr - str);
}

char				*ft_strrev(char *str)
{
	char			*dst;
	int				len;
	int				i;

	len = ft_strlen(str);
	dst = (char *)malloc(sizeof(char) * (len + 1));
	i = 0;
	while (i < len)
	{
		dst[i] = str[len - i - 1];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char				*ft_strdup(const char *str)
{
	register char	*strnew;
	register char	*ptr;

	strnew = (char *)malloc(sizeof(char) * ft_strlen(str) + 1);
	ptr = strnew;
	while (*str)
		*ptr++ = *str++;
	*ptr = '\0';
	return (strnew);
}

char				*ft_itoa(int n)
{
	char			*str;
	int				pos;
	int				tmp;

	pos = 0;
	tmp = n;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	if (!(str = (char *)malloc(sizeof(char) * 12)))
		return (NULL);
	if (n < 0)
		n *= -1;
	while (n > 0)
	{
		str[pos++] = (n % 10) + 48;
		n = n / 10;
	}
	str[pos] = '\0';
	if (tmp < 0)
		str[pos++] = '-';
	str[pos] = '\0';
	return (ft_strrev(str));
}

void				ft_drawmap(t_env *e)
{
	int				x;
	int				y;
	char			*str;

	mvprintw(0, 0, "\nThe map is : \n");
	y = 0;
	while (y < e->y)
	{
		x = 0;
		while (x < e->x)
		{
			str = ft_itoa(e->map[y * e->y + x++]);
			mvprintw(10 * y + 1, 10 * x, str);
			mvprintw(10 * y + 1, 10 * x + ft_strlen(str), "\t");
			free(str);
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
	int				*ptr;
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
	int				x;
	int				y;

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

int					ft_anyat(t_env *e, int value)
{
	int				max;

	max = e->x * e->y - 1;
	while (max >= 0)
	{
		if (e->map[max--] == value)
			return (1);
	}
	return (0);
}
