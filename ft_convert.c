#include "libftprintf.h"

char			*ft_convert_hex(unsigned int num)
{
	static char representation[] = "0123456789abcdef";
	static char buffer[30];
	char		*ptr;

	ptr = &buffer[29];
	*ptr = '\0';
	if (num == 0)
		*--ptr = '0';
	while (num != 0)
	{
		*--ptr = representation[num % 16];
		num /= 16;
	}
	return (ptr);
}

char			*ft_convert_uphex(unsigned int num)
{
	static char representation[] = "0123456789ABCDEF";
	static char buffer[30];
	char		*ptr;

	ptr = &buffer[29];
	*ptr = '\0';
	if (num == 0)
		*--ptr = '0';
	while (num != 0)
	{
		*--ptr = representation[num % 16];
		num /= 16;
	}
	return (ptr);
}

char			*ft_convert_u(unsigned int num)
{
	static char	representation[] = "0123456789";
	static char	buffer[30];
	char		*ptr;

	ptr = &buffer[29];
	*ptr = '\0';
	if (num == 0)
		*--ptr = '0';
	while (num != 0)
	{
		*--ptr = representation[num % 10];
		num /= 10;
	}
	return (ptr);
}

char			*ft_convert_di(long int num)
{
	static char	representation[] = "0123456789";
	static char	buffer[30];
	char		*ptr;
	int			i;

	i = 0;
	if (num < 0)
	{
		i = 1;
		num = -1 * num;
	}
	ptr = &buffer[29];
	*ptr = '\0';
	if (num == 0)
		*--ptr = '0';
	while (num != 0)
	{
		*--ptr = representation[num % 10];
		num /= 10;
	}
	if (i > 0)
		*--ptr = '-';
	return (ptr);
}

char			*ft_convert(long val, char spec)
{
	if (spec == 'u')
		return (ft_convert_u(val));
	else if (spec == 'd')
		return (ft_convert_di(val));
	else if (spec == 'x')
		return (ft_convert_hex(val));
	else if (spec == 'X')
		return (ft_convert_uphex(val));
	else
		return (NULL);
}
