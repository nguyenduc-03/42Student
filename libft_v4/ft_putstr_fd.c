/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_putstr_fd.c									 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: ducnguye <ducnguye@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/11/18 12:26:42 by ducnguye		  #+#	#+#			 */
/*   Updated: 2024/11/18 12:26:57 by ducnguye		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
}