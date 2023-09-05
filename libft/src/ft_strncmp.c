/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:55:29 by cdumais           #+#    #+#             */
/*   Updated: 2023/08/29 18:13:13 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
compare 'n' bytes of 's1' and 's2'
return SAME(0) if s1 and s2 are identical,
or the difference between the first two different bytes (s1 - s2)
*/
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		diff;
	char	c1;
	char	c2;

	i = 0;
	while (i < n)
	{
		c1 = (unsigned char)s1[i];
		c2 = (unsigned char)s2[i];
		if (c1 != c2)
		{
			diff = (int)c1 - (int)c2;
			return (diff);
		}
		if (c1 == '\0')
			return (0);
		i++;
	}
	return (SAME);
}

/*
gets the starting pointer of the last 'n' characters of a string,
or the beginning of the string if it is shorter than 'n'
*/
static const char	*last_n_chars(const char *s, size_t n)
{
	size_t	len;

	len = ft_strlen(s);
	if (len < n)
		return (s);
	return (s + len - n);
}

/*
compare 'n' bytes of 's1' and 's2' starting from the last 'n' characters
return SAME(0) if s1 and s2 are identical,
or the difference between the first two different bytes (s1 - s2)
*/
int	ft_strrncmp(const char *s1, const char *s2, size_t n)
{
	const char	*start1;
	const char	*start2;

	start1 = last_n_chars(s1, n);
	start2 = last_n_chars(s2, n);
	return (ft_strncmp(start1, start2, n));
}
