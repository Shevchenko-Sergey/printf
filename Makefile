NAME	=	libftprintf.a
LIBFT	=	libft.a

SRC		=	ft_printf.c ft_print_args.c ft_func.c ft_convert.c

OBJ		=	$(SRC:c=o)

CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra
RM		=	rm -f
AR		=	ar rcs

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	cp $(LIBFT) ./$(NAME)
	$(AR) $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
