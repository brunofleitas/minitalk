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

SRCSC = client.c 
SRCSS = server.c
SRCSBC = client_bonus.c 
SRCSBS = server_bonus.c

NAME_CLIENT	= client
NAME_SERV	= server	
BONUS_NAME_CLIENT = client_bonus
BONUS_NAME_SERV = server_bonus

all: $(NAME_CLIENT) $(NAME_SERV)

$(NAME_CLIENT): $(SRCSC)
	$(CC) $(CFLAGS) $(SRCSC) -o $(NAME_CLIENT)

$(NAME_SERV): $(SRCSS)
	$(CC) $(CFLAGS) $(SRCSS) -o $(NAME_SERV)

bonus: $(BONUS_NAME_CLIENT) $(BONUS_NAME_SERV)

$(BONUS_NAME_CLIENT): $(SRCSBC)
	$(CC) $(CFLAGS) $(SRCSBC) -o $(BONUS_NAME_CLIENT)

$(BONUS_NAME_SERV): $(SRCSBS)
	$(CC) $(CFLAGS) $(SRCSBS) -o $(BONUS_NAME_SERV)

clean:
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

fclean: clean

re: fclean all

.PHONY: all bonus clean fclean re
