/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_lstlast.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: ducnguye <ducnguye@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/11/18 13:44:11 by ducnguye		  #+#	#+#			 */
/*   Updated: 2024/11/18 13:44:11 by ducnguye		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

int	ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst)
		lst = lst->next;
	return (lst);
}
