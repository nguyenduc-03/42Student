#include "ft_printf.h"

int	ft_putstr_fd(const char *s, int fd)
{
	int	count;

	if (!s)
		return (ft_putstr_fd("(null)", fd));
	count = 0;
	while (*s)
	{
		count += ft_putchar_fd(*s, fd);
		s++;
	}
	return (count);
}