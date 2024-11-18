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

t_list	ft_lstlast(t_list *lst)
{
	if (!lst)
	{
		lst = NULL;
		return (*lst);
	}
	while (lst)
		lst = lst->next;
	return (*lst);
}
