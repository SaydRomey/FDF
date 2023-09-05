/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:12:43 by cdumais           #+#    #+#             */
/*   Updated: 2023/08/30 12:12:44 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_min(int this, int that)
{
	if (this < that)
		return (this);
	else
		return (that);
}

// #define MIN(a, b) (a < b ? a : b)