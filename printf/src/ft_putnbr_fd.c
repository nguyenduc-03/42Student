#include "ft_printf.h"

int	ft_putnbr_fd(int n, int fd)
{
	int	count;

	count = 0;
	if (n == -2147483648)
	{
		count += ft_putstr_fd("-2147483648", fd);
		return (count);
	}
	if (n < 0)
	{
		count += ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n > 9)
		count += ft_putnbr_fd(n / 10, fd);
	return (count + ft_putchar_fd((n % 10) + '0', fd));
}