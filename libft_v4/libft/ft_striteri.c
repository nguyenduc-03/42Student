/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_striteri.c									  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: ducnguye <ducnguye@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/11/18 12:24:41 by ducnguye		  #+#	#+#			 */
/*   Updated: 2024/11/18 12:24:41 by ducnguye		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	if (!s || !f)
		return ;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
