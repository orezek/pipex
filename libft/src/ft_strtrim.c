/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:38:11 by orezek            #+#    #+#             */
/*   Updated: 2023/11/21 17:58:03 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// "abrakadabra" "abra" -> "kad"
// "abrakadabra" "a" -> "brakadabr"
// cc -fsanitize=address -Wall -Werror -Wextra ./.tests/tst_ft_strtrim.c
//ft_strtrim.c ft_strlen.c ft_strlcpy.c ft_strncmp.c && ./a.out | cat -e
int	is_inside(char const c, char const *set)
{
	while (*set)
	{
		if (c == *set++)
			return (1);
	}
	return (0);
}

int	is_same(char const *s1, char const *set, int s_length)
{
	while (is_inside(*s1++, set))
		s_length--;
	if (s_length == 0)
		return (1);
	return (0);
}

char	*ft_empty_or_null(char *substr)
{
	substr = (char *) malloc(sizeof(char) * (1));
	if (substr == NULL)
		return (NULL);
	*substr = '\0';
	return (substr);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*substr;
	int		s_length;
	int		i;
	int		start;

	substr = NULL;
	s_length = ft_strlen(s1);
	if (*s1 == '\0' || is_same(s1, set, s_length))
		return (ft_empty_or_null(substr));
	while (is_inside(*(s1 + s_length - 1), set))
		s_length--;
	start = 0;
	while (is_inside(*(s1 + start++), set))
		s_length--;
	substr = (char *) malloc(sizeof(char) * (s_length + 1));
	if (substr == NULL)
		return (NULL);
	i = 0;
	start -= 1;
	while (i++ < s_length)
		*(substr++) = *(s1 + start++);
	*substr = '\0';
	return (substr - s_length);
}
