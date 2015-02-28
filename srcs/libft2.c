/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/28 00:23:09 by achazal           #+#    #+#             */
/*   Updated: 2015/02/28 00:23:11 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game_2048.h"

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
