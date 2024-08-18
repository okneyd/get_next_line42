/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydemyden <ydemyden@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:49:54 by ydemyden          #+#    #+#             */
/*   Updated: 2024/08/18 17:33:50 by ydemyden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// string scanning operation || locate the FIRST occurrence of c
// (converted to a char) in the string pointed to by s.  The
// terminating NUL character is considered to be part of the string.
char	*ft_strchr(const char *s, int c)
{
	int				z;
	unsigned char	uc;

	uc = (unsigned char)c;
	z = 0;
	while (s[z] != '\0')
	{
		if (s[z] == uc)
			return ((char *)&s[z]);
		z++;
	}
	if (uc == '\0')
		return ((char *)&s[z]);
	return (NULL);
}

// calculates the length of a string, not including '\0'
size_t	ft_strlen(const char *s)
{
	size_t	z;

	z = 0;
	while (s[z] != '\0')
	{
		z++;
	}
	return (z);
}

// copies n bytes from memory area src to memory area dest.
// The memory areas must not overlap (for overlaps is memmove)

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		z;
	char		*pdest;
	const char	*psrc;

	pdest = (char *)dest;
	psrc = (const char *)src;
	if (!dest && !src)
		return (NULL);
	z = 0;
	while (n > z)
	{
		pdest[z] = psrc[z];
		z++;
	}
	return (dest);
}

// returns a pointer to a new string which is
// a duplicate of the string s.
char	*ft_strdup(const char *s)
{
	size_t	l;
	char	*dplct;

	l = ft_strlen(s) + 1;
	dplct = malloc(l);
	if (s == 0)
		return (NULL);
	else if (dplct != NULL)
		ft_memcpy(dplct, s, l);
	return (dplct);
}

// Allocates and returns a new string,
// which is the result of the concatenation of ’s1’ and ’s2’
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*comb;
	size_t	lens1;
	size_t	lens2;
	size_t	summary;

	if (!s1 || !s2)
		return (NULL);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	summary = lens1 + lens2;
	comb = (char *)malloc(summary + 1);
	if (!comb)
		return (NULL);
	ft_memcpy(comb, s1, lens1);
	ft_memcpy(comb + lens1, s2, lens2);
	comb[summary] = '\0';
	return (comb);
}
