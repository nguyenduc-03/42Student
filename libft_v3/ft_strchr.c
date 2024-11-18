/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strchr.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: ducnguye <ducnguye@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/11/13 11:09:43 by ducnguye		  #+#	#+#			 */
/*   Updated: 2024/11/13 15:14:06 by ducnguye		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int search_char)
{
	char	c;

	c = search_char;
	if (search_char == 0)
	{
		str = str + ft_strlen(str);
		return ((char *)str);
	}
	while (*str)
	{
		if (*str == c)
			return ((char *)str);
		str++;
	}
	return (NULL);
}
