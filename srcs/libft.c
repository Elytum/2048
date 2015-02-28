/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/28 00:23:09 by achazal           #+#    #+#             */
/*   Updated: 2015/02/28 00:23:11 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game_2048.h"
#include <stdlib.h>
#include <unistd.h>

char		*ft_strnew(size_t n)
{
	char	*str;
	char	*ptr;

	if (!(str = (char *)malloc(sizeof(char) * (n++ + 1))))
		return (NULL);
	ptr = str;
	while (n--)
		*ptr++ = '\0';
	return (str);
}

void		ft_putnbr(unsigned int n)
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

void		*ft_memalloc(size_t size)
{
	void	*memory;
	char	*explorer;

	if (!size || !(memory = (void *)malloc(size)))
		return (NULL);
	explorer = (char *)memory;
	while (size--)
		*explorer++ = 0;
	return (memory);
}