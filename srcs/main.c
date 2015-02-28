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
#define HEIGHT 4
#define WIDTH 4

int				ft_continue(t_env *e)
{

	if (!(ft_anyat(e, 0)))
		return (0);
	ft_generaterandom(e);
	return (ft_anyat(e, 0) || ft_neighboor(e));
}

t_params		*ft_get_params(void)
{
	t_params	*p;

	if (!(p = (t_params *)ft_memalloc(sizeof(t_params))))
		return (NULL);
	p->c_pos_x = 0;
	p->c_pos_y = 0;
	p->print = 0;
	if (tgetent(p->buf, p->v_term) < 1)
		return (NULL);
	tcgetattr(0, &p->term);
	p->term.c_lflag &= ~(ICANON);
	p->term.c_lflag &= ~(ECHO);
	p->term.c_cc[VMIN] = 1;
	p->term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &p->term) == -1)
		return (NULL);
	p->max_size = 1;
	p->col_count = 1;
	return (p);
}

t_env			*ft_init_env(int ac, char **av)
{
	t_env		*e;

	if (!(e = (t_env *)ft_memalloc(sizeof(t_env))))
		return (NULL);
	e->p = ft_get_params();
	e->x = WIDTH;
	e->y = HEIGHT;
	if (!(e->map = ft_memalloc(sizeof(int) * (e->x * e->y))))
		return (NULL);
	e->play = 1;
	e->check = 0;
	return (e);
	ac++;
	av++;
}

int				main(int ac, char **av)
{
	char		buff[2] = {0};
	t_env		*e;

	if (!(e = ft_init_env(ac, av)))
		return (-1);
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
