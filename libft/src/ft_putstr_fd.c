/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:46:10 by cdumais           #+#    #+#             */
/*   Updated: 2023/08/30 12:15:51 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
writes the string 'str' to the file descriptor 'fd'
if 'str' is NULL, writes "(null)" to 'fd' (like printf)
returns the number of bytes written (excluding the terminating null byte)
*/
size_t	ft_putstr_fd(char *str, int fd)
{
	size_t	length;

	length = 0;
	if (!str)
	{
		length = write (fd, "(null)", 6);
		return (length);
	}
	length = write(fd, str, ft_strlen(str));
	return (length);
}
