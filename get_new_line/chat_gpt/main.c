/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   main.c											 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: codespace <codespace@student.42.fr>		+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/12/09 11:16:11 by codespace		 #+#	#+#			 */
/*   Updated: 2024/12/09 11:16:12 by codespace		###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main()
{
	int fd = open("example.txt", O_RDONLY);
	char *line;

	while ((line = get_next_line(fd))) {
		printf("%s", line);
		free(line);
	}
	close(fd);

	return 0;
}
