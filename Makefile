NAME = webserv

CC = c++
CFLAGS = #-g3 -fsanitize=address


DEBUG =  valgrind --track-origins=yes 
RM = rm
RMFLAGS = -rf

SRCS_SBOOF_DIR = Sources/sboof/
INC_SBOOF_DIR = Includes/sboof/
INC_DIR = Includes/
SRC_DIR = Sources/
OBJ_DIR = obj/

INCS = 	Includes/tt.hpp\
		Includes/server.hpp\
		Includes/location.hpp\
		Includes/request.hpp\
		Includes/Cgi.hpp\
		Includes/parsing.hpp


INCS_SBOOF = Includes/sboof/Firstline.hpp\
			 Includes/sboof/Response.hpp\
			 Includes/sboof/Header.hpp\
			 Includes/sboof/Response_cgi.hpp

SRCS_SBOOF = /sboof/Firstline.cpp\
	/sboof/Response.cpp\
	Sources/sboof/StatusCode.cpp\
	Sources/sboof/Header.cpp\
	Sources/sboof/Response_cgi.cpp\
	
SRCS_CLIENT = Sources/client.cpp

SRCS = \
	Sources/parsing_request.cpp\
	Sources/main.cpp\
	Sources/vector_parsing.cpp\
	Sources/server.cpp\
	Sources/request.cpp\
	Sources/location.cpp\
	Sources/Cgi.cpp\
	Sources/before_parsing.cpp\
	Sources/get_config_infos.cpp


	



vpath %.cpp $(SRC_DIR) %.cpp $(SRCS_SBOOF_DIR)

OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.cpp=.o)))
OBJS_SBOOF = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS_SBOOF:.cpp=.o)))



# ============================================================================ #
#                                   COLOR                                      #
# ============================================================================ #

CL_BOLD	 = \e[1m
CL_DIM	= \e[2m
CL_UDLINE = \e[4m

NO_COLOR = \e[0m

BG_TEXT = \e[48;2;45;55;72m
BG_BLACK = \e[48;2;30;31;33m

FG_WHITE = $(NO_COLOR)\e[0;37m
FG_TEXT = $(NO_COLOR)\e[38;2;189;147;249m
FG_TEXT_PRIMARY = $(NO_COLOR)$(CL_BOLD)\e[38;2;255;121;198m

LF = \e[1K\r$(NO_COLOR)
CRLF= \n$(LF)

all : $(NAME) $(CLIENT)

debug :$(NAME_D)

clean :
	@$(RM) $(RMFLAGS) $(OBJS) $(OBJS_SBOOF)
	@printf "$(LF)🧹 $(FG_TEXT)Cleaning $(FG_TEXT_PRIMARY)$(NAME)'s Object files...\n"

fclean : clean
	@$(RM) $(RMFLAGS) $(NAME)
	@printf "$(LF)🧹 $(FG_TEXT)Cleaning $(FG_TEXT_PRIMARY)$(NAME)\n"

re : fclean all

$(OBJ_DIR) :
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o : %.cpp $(INCS) $(INCS_SBOOF) | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@
	@printf "$(LF)🚧 $(FG_TEXT)Create $(FG_TEXT_PRIMARY)$@ $(FG_TEXT)from $(FG_TEXT_PRIMARY)$<"

$(NAME) : $(OBJS)  $(OBJS_SBOOF) $(INCS) $(INCS_SBOOF)
	@printf "$(LF)🚀 $(FG_TEXT)Successfully Created $(FG_TEXT_PRIMARY)$@'s Object files $(FG_TEXT)!"
	@printf "$(CRLF)📚 $(FG_TEXT)Create $(FG_TEXT_PRIMARY)$@$(FG_TEXT)!\n"
	@$(CC) $(CFLAGS) -I $(INC_DIR) $(OBJS) $(OBJS_SBOOF) -o $@
	@printf "$(LF)🎉 $(FG_TEXT)Successfully Created $(FG_TEXT_PRIMARY)$@ $(FG_TEXT)!\n$(NO_COLOR)"


$(NAME_D) : $(OBJS)  $(OBJS_SBOOF) $(INCS) $(INCS_SBOOF)
	@printf "$(LF)🚀 $(FG_TEXT)Successfully Created $(FG_TEXT_PRIMARY)$@'s Object files $(FG_TEXT)!"
	@printf "$(CRLF)📚 $(FG_TEXT)Create $(FG_TEXT_PRIMARY)$@$(FG_TEXT)!\n"
	@$(CC) $(CFLAGS) -g -I $(INC_DIR) $(OBJS) $(OBJS_SBOOF) -o $@
	@printf "$(LF)🎉 $(FG_TEXT)Successfully Created $(FG_TEXT_PRIMARY)$@ $(FG_TEXT)!\n$(NO_COLOR)"

$(CLIENT) :  $(INCS)
	@printf "$(LF)🚀 $(FG_TEXT)Successfully Created $(FG_TEXT_PRIMARY)$@'s Object files $(FG_TEXT)!"
	@printf "$(CRLF)📚 $(FG_TEXT)Create $(FG_TEXT_PRIMARY)$@$(FG_TEXT)!\n"
	@$(CC) $(CFLAGS) -I $(INC_DIR) $(SRCS_CLIENT) -o $@
	@printf "$(LF)🎉 $(FG_TEXT)Successfully Created $(FG_TEXT_PRIMARY)$@ $(FG_TEXT)!\n$(NO_COLOR)"

.PHONY: all clean fclean re