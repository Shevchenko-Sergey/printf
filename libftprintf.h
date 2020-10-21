#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include "libft.h"
# include <stdarg.h>

typedef struct		s_flag
{
	char		minus;
	char		zero;
	char		neg_star;
	char		type;
	long long	prec;
	long long	width;
}					t_flag;

int					ft_printf(const char *format, ...);
int					ft_parse_flags(va_list factor, const char **format);
void				ft_prec(const char **str, va_list factor, t_flag *flag);
int					ft_spec(t_flag *flag, const char *str, \
									va_list factor, const char **format);
int					ft_putzero_space(char c, int nbr, char *str, char pdn);
int					ft_print_char(char c, t_flag *flag);
int					ft_print_str(char *str, t_flag *flag);
int					ft_print_p(unsigned long num, t_flag *flag);
int					ft_print_nbr(long adr, t_flag *flag, char spec);
void				ft_flag_init(t_flag *flag);
long long			ft_star_width(long long star, t_flag *flag);
char				*ft_nbr(char *num, int len, int prec);
char				*ft_zero(char *num, int len, int width, t_flag *flag);
char				*ft_convert_hex(unsigned int num);
char				*ft_convert_uphex(unsigned int num);
char				*ft_convert_u(unsigned int num);
char				*ft_convert_di(long int num);
char				*ft_convert(long val, char spec);

#endif
