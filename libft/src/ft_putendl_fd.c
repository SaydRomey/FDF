/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:01:06 by cdumais           #+#    #+#             */
/*   Updated: 2023/08/30 12:14:28 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
writes the string 'str' to the file descriptor fd, followed by a newline.
returns the number of characters written.
*/
size_t	ft_putendl_fd(char *str, int fd)
{
	size_t	out;

	out = 0;
	out += ft_putstr_fd(str, fd);
	out += ft_putchar_fd('\n', fd);
	return (out);
}
