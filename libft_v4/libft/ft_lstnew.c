/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_lstnew.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: ducnguye <ducnguye@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/11/18 13:44:37 by ducnguye		  #+#	#+#			 */
/*   Updated: 2024/11/18 13:44:37 by ducnguye		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(16);
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}
