/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:36:50 by orezek            #+#    #+#             */
/*   Updated: 2023/11/21 17:58:12 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*ft_search_for_sub(const char *str, const char *to_find, size_t len)
{
	size_t	step;
	size_t	inner_step;
	size_t	success_flag;
	char	*sstr;

	sstr = (char *) str;
	step = 0;
	while (step < len && *sstr++)
	{
		inner_step = step;
		success_flag = 0;
		while (inner_step < (ft_strlen(to_find) + step))
		{
			if (*(str + inner_step) == *(to_find + inner_step - step))
				success_flag += 1;
			inner_step++;
		}
		if (success_flag == ft_strlen(to_find) && inner_step <= len)
			return ((char *) str + step);
		step++;
	}
	return (NULL);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	if (*little == '\0')
		return ((char *) big);
	if (ft_strlen(big) < ft_strlen(little))
		return (NULL);
	if (ft_strlen(little) > len)
		return (NULL);
	if (ft_strlen(big) == ft_strlen(little))
	{
		if (ft_strncmp(big, little, ft_strlen(big)) == 0)
			return ((char *) big);
		else
			return (NULL);
	}
	return (ft_search_for_sub(big, little, len));
}
