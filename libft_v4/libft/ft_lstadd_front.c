/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   $TM_FILENAME                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ducnguye <ducnguyen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:00:00 by ducnguye          #+#    #+#             */
/*   Updated: 2025/05/17 12:01:32 by ducnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}
