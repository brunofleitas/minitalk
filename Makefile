# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/28 22:03:14 by bfleitas          #+#    #+#              #
#    Updated: 2024/05/30 00:59:17 by bfleitas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC	= cc

CFLAGS	= -Wall -Werror -Wextra

RM	= rm -rf

SRCSC = client.c ft_atoi.c ft_itoa.c
SRCSS = server.c ft_printf.c output_char_string.c output_nbr.c
SRCSBC = client_bonus.c ft_atoi.c ft_itoa.c
SRCSBS = server_bonus.c ft_printf.c output_char_string.c output_nbr.c

CLIENT_OBJS	= $(SRCSC:.c=.o)
SERVER_OBJS	= $(SRCSS:.c=.o)
BONUS_CLIENT_OBJS	= $(SRCSBC:.c=.o)
BONUS_SERVER_OBJS	= $(SRCSBS:.c=.o)

NAME_CLIENT	= client
NAME_SERV	= server	
BONUS_NAME_CLIENT = client_bonus
BONUS_NAME_SERV = server_bonus

all: $(NAME_CLIENT) $(NAME_SERV)

$(NAME_CLIENT): $(CLIENT_OBJS) 
	$(CC) $(CFLAGS) $(CLIENT_OBJS) -o $(NAME_CLIENT)

$(NAME_SERV): $(SERVER_OBJS) 
	$(CC) $(CFLAGS) $(SERVER_OBJS) -o $(NAME_SERV)

bonus: $(BONUS_NAME_CLIENT) $(BONUS_NAME_SERV)

$(BONUS_NAME_CLIENT): $(BONUS_CLIENT_OBJS) 
	$(CC) $(CFLAGS) $(BONUS_CLIENT_OBJS) -o $(BONUS_NAME_CLIENT)

$(BONUS_NAME_SERV): $(BONUS_SERVER_OBJS) 
	$(CC) $(CFLAGS) $(BONUS_SERVER_OBJS) -o $(BONUS_NAME_SERV)

clean:
		$(RM) $(CLIENT_OBJS) $(SERVER_OBJS) \
		$(BONUS_CLIENT_OBJS) $(BONUS_SERVER_OBJS) 

fclean: clean
	@if [ -f $(NAME_CLIENT) ]; then \
	echo "Removing $(NAME_CLIENT)"; \
	$(RM) $(NAME_CLIENT); fi
	@if [ -f $(NAME_SERV) ]; then \
	echo "Removing $(NAME_SERV)"; \
	$(RM) $(NAME_SERV); fi
	@if [ -f $(BONUS_NAME_CLIENT) ]; then \
	echo "Removing $(BONUS_NAME_CLIENT)"; \
	$(RM) $(BONUS_NAME_CLIENT); fi
	@if [ -f $(BONUS_NAME_SERV) ]; then \
	echo "Removing $(BONUS_NAME_SERV)"; \
	$(RM) $(BONUS_NAME_SERV); fi

re: fclean all

.PHONY: all bonus clean fclean re
