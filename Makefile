# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/08 12:51:48 by marcsilv          #+#    #+#              #
#    Updated: 2025/11/17 19:59:34 by dvemba           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ircserv

CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98

SRC_DIR		= src/
OBJ_DIR		= obj/
INC_DIR		= inc/

SRC_FILES	= main.cpp IRC.cpp Validate.cpp Server.cpp Client.cpp Parser.cpp commands/Command.cpp commands/PASS.cpp utils.cpp commands/CAP.cpp commands/NICK.cpp commands/USER.cpp commands/MODE.cpp commands/PING.cpp
HEADERS		= IRC.hpp Validate.hpp Server.hpp Client.hpp Parser.hpp commands/Command.hpp commands/PASS.hpp utils.hpp commands/CAP.hpp commands/NICK.hpp commands/USER.hpp commands/MODE.hpp commands/PING.hpp

SRC			= $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ			= $(addprefix $(OBJ_DIR), $(SRC_FILES:.cpp=.o))
INC			= $(addprefix $(INC_DIR), $(HEADERS))

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
$(OBJ_DIR)commands/%.o: $(SRC_DIR)commands/%.cpp
	@mkdir -p $(OBJ_DIR)commands
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@
	
clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
