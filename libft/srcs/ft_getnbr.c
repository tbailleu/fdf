/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbailleu <tbailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 09:27:24 by tbailleu          #+#    #+#             */
/*   Updated: 2017/12/18 12:50:33 by tbailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_getnbr(char *str)
{
	int nbr;
	int neg;

	neg = 0;
	if (*str == '-')
	{
		neg = 1;
		str++;
	}
	nbr = 0;
	while (ft_isdigit(*str))
		nbr = (nbr * 10) + *str++ - '0';
	return ((neg) ? -nbr : nbr);
}
