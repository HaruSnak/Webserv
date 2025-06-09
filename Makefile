NAME = webserv
CXX = c++
RM = rm -f
INCLUDES = -I./includes
CXXFLAGS = -std=c++98 -Wall -Wextra -Werror
OBJ_DIR = obj/

SRC_1 = srcs/main.cpp \
		srcs/errors/parsing/errors.cpp \
		srcs/parsing/ConfigParser.cpp \
		srcs/parsing/LocationConfig.cpp \
		srcs/parsing/LocationConfigParser.cpp \
		srcs/parsing/ServerConfig.cpp \
		srcs/parsing/ServerConfigParser.cpp \

OBJ_1 = $(patsubst %.cpp,$(OBJ_DIR)%.o,$(SRC_1))

$(OBJ_DIR)%.o: %.cpp
	@mkdir -p $(@D)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

.cpp.o:
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

${NAME}: ${OBJ_1}
	@echo "Compiling $(NAME)..."
	@${CXX} ${CXXFLAGS} ${OBJ_1} -o ${NAME}
	@echo "$(NAME) compiled successfully."

all: ${NAME}

clean:
	@echo "Cleaning object files..."
	@${RM} ${OBJ_1}
	@rm -rf ${OBJ_DIR}
	@echo "Object files cleaned."

fclean: clean
	@echo "Cleaning executable..."
	@${RM} ${NAME}
	@rm -rf ${OBJ_DIR}
	@echo "Executable cleaned."

re: clean all

.PHONY: all clean fclean re