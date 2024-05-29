# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/28 22:03:14 by bfleitas          #+#    #+#              #
#    Updated: 2024/05/29 17:14:40 by bfleitas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC	= cc

CFLAGS	= -Wall -Werror -Wextra

RM	= rm -rf

LIBC	= ar rcs

# Archivos de origen para 'client'
CLIENT_SRCS	= client.c srcs/ft_atoi.c srcs/ft_itoa.c srcs/ft_printf.c \
				srcs/output_char_string.c srcs/output_hex.c srcs/output_nbr.c

# Archivos de origen para 'server'
SERVER_SRCS	= server.c srcs/ft_atoi.c srcs/ft_itoa.c srcs/ft_printf.c \
				srcs/output_char_string.c srcs/output_hex.c srcs/output_nbr.c

# Archivos de origen para versiones de bono ('bonus')
BONUS_CLIENT_SRCS	= client_bonus.c srcs/ft_atoi.c srcs/ft_itoa.c srcs/ft_printf.c \
					srcs/output_char_string.c srcs/output_hex.c srcs/output_nbr.c

BONUS_SERVER_SRCS	= server_bonus.c srcs/ft_atoi.c srcs/ft_itoa.c srcs/ft_printf.c \
					srcs/output_char_string.c srcs/output_hex.c srcs/output_nbr.c

CLIENT_OBJS	= $(CLIENT_SRCS:.c=.o)
SERVER_OBJS	= $(SERVER_SRCS:.c=.o)
BONUS_CLIENT_OBJS	= $(BONUS_CLIENT_SRCS:.c=.o)
BONUS_SERVER_OBJS	= $(BONUS_SERVER_SRCS:.c=.o)

NAME_CLIENT	= client
NAME_SERV	= server	
BONUS_NAME_CLIENT = client_bonus
BONUS_NAME_SERV = server_bonus

all: $(NAME_CLIENT) $(NAME_SERV)

$(NAME_CLIENT): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME_CLIENT)

$(NAME_SERV): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME_SERV)

bonus: $(BONUS_NAME_CLIENT) $(BONUS_NAME_SERV)

$(BONUS_NAME_CLIENT): $(OBJSB)
	$(CC) $(CFLAGS) $(OBJSB) -o $(BONUS_NAME_CLIENT)

$(BONUS_NAME_SERV): $(OBJSB)
	$(CC) $(CFLAGS) $(OBJSB) -o $(BONUS_NAME_SERV)

clean:
	$(RM) $(CLIENT_OBJS) $(SERVER_OBJS) $(BONUS_CLIENT_OBJS) $(BONUS_SERVER_OBJS)

fclean: clean
	$(RM) $(NAME_CLIENT) $(NAME_SERV) $(BONUS_NAME_CLIENT) $(BONUS_NAME_SERV)

re: fclean all

.PHONY: all bonus clean fclean re