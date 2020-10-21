#include "libftprintf.h"

int				ft_print_p(unsigned long int num, t_flag *flag)
{
	static	char	representation[] = "0123456789abcdef";
	static	char	buffer[30];
	char			*ptr;
	int				len;
	int				ret;

	ret = 0;
	ptr = &buffer[29];
	*ptr = '\0';
	if (!num)
		*--ptr = '0';
	while (num != 0)
	{
		*--ptr = representation[num % 16];
		num /= 16;
	}
	*--ptr = 'x';
	*--ptr = '0';
	len = ft_strlen(ptr);
	ret += ft_putzero_space(' ', flag->width - len, ptr, flag->minus);
	return (ret);
}

int				ft_print_char(char c, t_flag *flag)
{
	int		res;
	char	str[2];

	str[0] = c;
	str[1] = '\0';
	res = 0;
	if (str[0] == '%' && flag->zero && !flag->minus)
		res += ft_putzero_space('0', flag->width - 1, str, flag->minus);
	else if (flag->width > 1)
	{
		if (c == '\0' && flag->minus)
			res += ft_putchar(c);
		res += ft_putzero_space(' ', flag->width - 1, str, flag->minus);
		if (c == '\0' && !flag->minus)
			res += ft_putchar(c);
	}
	else
		res = ft_putchar(c);
	return (res);
}

int				ft_print_nbr(long val, t_flag *flag, char spec)
{
	char	*num;
	int		res;
	int		len;

	if (flag->neg_star)
		flag->prec = -1;
	if (flag->zero && flag->prec != -1)
		flag->zero = 0;
	num = ft_convert(val, spec);
	(num[0] == '0' && flag->prec == 0) ? num = "\0" : 0;
	len = ft_strlen(num);
	if (flag->prec >= len)
	{
		if (!(num = ft_nbr(num, len, flag->prec)))
			return (-1);
	}
	else if (flag->zero && !flag->minus && flag->width > len)
		if (!(num = ft_zero(num, len, flag->width, flag)))
			return (-1);
	res = ft_putzero_space(' ', flag->width - ft_strlen(num), num, flag->minus);
	return (res);
}

int				ft_putzero_space(char c, int nbr, char *str, char minus)
{
	int res;
	int i;

	i = 0;
	res = 0;
	if (minus)
	{
		res = ft_putstr(str);
		while (i++ < nbr)
			res += ft_putchar(c);
	}
	else
	{
		while (i++ < nbr)
			res += ft_putchar(c);
		res += ft_putstr(str);
	}
	return (res);
}

int				ft_print_str(char *str, t_flag *flag)
{
	char	*tmp;
	int		str_len;
	int		res;

	if (!str)
		return (ft_print_str("(null)", flag));
	str_len = ft_strlen(str);
	if (flag->neg_star)
		flag->prec = -1;
	if (!(tmp = malloc(str_len + 1)))
		return (-1);
	ft_strlcpy(tmp, str, str_len + 1);
	if (flag->prec != -1 && flag->prec < str_len)
	{
		tmp[flag->prec] = '\0';
		str_len = flag->prec;
	}
	res = ft_putzero_space(' ', flag->width - str_len, tmp, flag->minus);
	free(tmp);
	tmp = NULL;
	return (res);
}
