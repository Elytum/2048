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
# include <signal.h>
# include <termios.h>
# include <termcap.h>
# include <curses.h>

typedef struct		s_params
{
	char			**av;
	int				ac;
	char			*v_term;
	char			buf[2048];
	struct termios	term;
	struct termios	*oldterm;
	char			r_char[4];
	int				print;
	tcflag_t		old_term;
	int				c_pos_x;
	int				c_pos_y;
	int				l_count;
	int				col_count;
	int				max_size;
}					t_params;

typedef struct		s_env
{
	unsigned int	*map;
	unsigned int	x;
	unsigned int	y;
	unsigned int	sbx;
	unsigned int	sby;
	unsigned int	box;
	unsigned int	boy;
	unsigned int	sx;
	unsigned int	sy;
	char			play;
	char			check;
	char			*player_name;
	unsigned int	player_name_len;
	size_t			player_score;
	t_params		*p;
}					t_env;

char				*ft_strnew(size_t n);
void				*ft_memalloc(size_t size);
void				ft_putnbr(unsigned int n);
char				ft_up(t_env *e);
char				ft_down(t_env *e);
char				ft_left(t_env *e);
char				ft_right(t_env *e);
int					ft_power2(char power);
void				ft_drawmap(t_env *e);
void				ft_generaterandom(t_env *e);
int					ft_neighboor(t_env *e);
int					ft_anyat(t_env *e, unsigned int value);
unsigned int		ft_intlen(unsigned int n);

size_t				ft_strlen(const char *str);
char				*ft_strrev(char *str);
char				*ft_strdup(const char *str);
char				*ft_itoa(int n);
#endif