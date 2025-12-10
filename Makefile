srcs = ft_putchar.c ft_puthex.c ft_putnbr.c  ft_putstr.c ft_strlen.c ft_printf.c


OBJ = ${srcs:.c=.o}
NAME = libftprintf.a
LIB = ar rc
CC = cc
RM = rm -f
FLAG = -Wall -Wextra -Werror

all: ${NAME}

${NAME}: ${OBJ}
	echo "les fichiers de compilation"
	${LIB} ${NAME} ${OBJ}

%.o:%.c ft_printf.h
	${CC} ${FLAG} -c $<

clean:
	echo "supression des fichiers objet"
	${RM} ${OBJ}

fclean: clean
	echo "suppression de la bibliotheque"
	${RM} ${NAME}

re: fclean all

.PHONY : clean