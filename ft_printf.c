#include "libftprintf.h"

int				ft_printf(const char *format, ...)
{
	va_list		ap;
	int			ret;
	int			tmp;

	ret = 0;
	va_start(ap, format);
	while (*format != '\0')
		if (*format != '%')
			ret += ft_putchar(*format++);
		else
		{
			if ((tmp = ft_parse_flags(ap, &format)) == -1)
				return (-1);
			ret += tmp;
		}
	va_end(ap);
	return (ret);
}

int				ft_parse_flags(va_list ap, const char **format)
{
	const char	*str = *format;
	t_flag		flag;

	ft_flag_init(&flag);
	++str;
	while (*str && !(ft_strchr("cspdiuxX%", *str)))
	{
		if (*str == '-')
			flag.minus = 1;
		else if (*str == '0')
			flag.zero = 1;
		else if (*str == '.')
			ft_prec(&str, ap, &flag);
		else if (*str == '*')
			flag.width = ft_star_width((long long)va_arg(ap, int), &flag);
		else if (ft_isdigit(*str))
		{
			flag.width = ft_atoi(str);
			while (ft_isdigit(*(str + 1)))
				++str;
		}
		++str;
	}
	return (*str ? ft_spec(&flag, str, ap, format) : -1);
}

int				ft_spec(t_flag *flag, const char *str, \
						va_list ap, const char **format)
{
	int			res;

	res = 0;
	flag->type = *str;
	if (flag->type == '%')
		res = ft_print_char('%', flag);
	else if (flag->type == 'c')
		res = ft_print_char(va_arg(ap, int), flag);
	else if (flag->type == 's')
		res = ft_print_str(va_arg(ap, char *), flag);
	else if (flag->type == 'p')
		res = ft_print_p((long long)va_arg(ap, void *), flag);
	else if (flag->type == 'd' || flag->type == 'i')
		res = ft_print_nbr(va_arg(ap, int), flag, 'd');
	else if (flag->type == 'u')
		res = ft_print_nbr(va_arg(ap, unsigned int), flag, 'u');
	else if (flag->type == 'x')
		res = ft_print_nbr(va_arg(ap, long), flag, 'x');
	else if (flag->type == 'X')
		res = ft_print_nbr(va_arg(ap, long), flag, 'X');
	*format = ++str;
	return (res);
}
