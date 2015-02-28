/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_2048.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/28 00:25:10 by achazal           #+#    #+#             */
/*   Updated: 2015/02/28 00:25:11 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SH1_H
# define FT_SH1_H
# include <stdlib.h>

typedef struct	s_env
{
	int			*map;
	char		x;
	char		y;
	char		play;
	char		check;
}				t_env;

char			*ft_strnew(size_t n);
void			*ft_memalloc(size_t size);
void			ft_putnbr(int n);
char			ft_up(t_env *e);//char **map, char sx, char sy);
char			ft_down(t_env *e);//char **map, char sx, char sy);
char			ft_left(t_env *e);//char **map, char sx, char sy);
char			ft_right(t_env *e);//char **map, char sx, char sy);
int				ft_power2(char power);
void			ft_drawmap(t_env *e);//char *map, char sx, char sy);
void			ft_generaterandom(t_env *e);//char **map, char sx, char sy);
int				ft_neighboor(t_env *e);//char **map, char sx, char sy);
int				ft_anyat(t_env *e, int value);//char **map, char sx, char sy, int value);


#endif