#include "libftprintf.h"

void			ft_prec(const char **str, va_list ap, t_flag *flag)
{
	long long star;

	(*str)++;
	if (**str == '*')
	{
		star = va_arg(ap, int);
		if (star < 0)
			flag->neg_star = 1;
		flag->prec = star < 0 ? star * -1 : star;
	}
	else if (ft_isdigit(**str))
	{
		flag->prec = (size_t)ft_atoi(*str);
		while (ft_isdigit(*(*str + 1)))
			(*str)++;
	}
	else
	{
		flag->prec = 0;
		--(*str);
	}
}

void			ft_flag_init(t_flag *flag)
{
	flag->width = -1;
	flag->prec = -1;
	flag->minus = 0;
	flag->neg_star = 0;
	flag->zero = 0;
}

long long		ft_star_width(long long star, t_flag *flag)
{
	if (star < 0)
	{
		flag->minus = 1;
		flag->neg_star *= -1;
	}
	return (star < 0 ? star * -1 : star);
}

char			*ft_nbr(char *num, int len, int prec)
{
	long long	size;
	char		*new;
	int			i;
	int			j;

	size = *num == '-' ? prec + 2 : prec + 1;
	if (!(new = malloc(size)))
	{
		free(num);
		num = NULL;
		return (NULL);
	}
	i = 0;
	j = 0;
	new[size - 1] = '\0';
	if (num[i] == '-' && len--)
		new[i++] = num[j++];
	while (prec-- > len)
		new[i++] = '0';
	while (len--)
		new[i++] = num[j++];
	return (new);
}

char			*ft_zero(char *num, int len, int width, t_flag *flag)
{
	char	*new;
	int		i;
	int		j;

	if (flag->prec < len && flag->prec != -1)
		return (num);
	if (!(new = malloc(width + 1)))
	{
		free(num);
		num = NULL;
		return (NULL);
	}
	new[width] = '\0';
	i = 0;
	j = 0;
	if (num[i] == '-')
		new[i++] = num[j++];
	while (width-- > len)
		new[i++] = '0';
	while (len--)
		new[i++] = num[j++];
	return (new);
}
