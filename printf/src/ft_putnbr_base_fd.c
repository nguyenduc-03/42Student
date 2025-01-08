#include "ft_printf.h"

int	ft_putnbr_base_fd(unsigned int n, const char *base, int fd)
{
	unsigned int	base_len;
	int				count;

	base_len = 0;
	count = 0;
	while (base[base_len])
		base_len++;
	if (n >= base_len)
		count += ft_putnbr_base_fd(n / base_len, base, fd);
	count += ft_putchar_fd(base[n % base_len], fd);
	return (count);
}