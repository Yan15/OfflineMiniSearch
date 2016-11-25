INC_DIR:= ./inc ./include/cppjieba
SRC_DIR:= ./src
CC:= g++
INC_FILE:= $(addprefix -I, $(INC_DIR))
SRC_FILE:= $(wildcard $(SRC_DIR)/*.cpp)
LIBS:= -lpthread
CPPFLAGS:= -std=c++11 -g
TERGET:= demo_minSearch.exe
$(TARGET):$(SRCS)
	 $(CC) $(CPPFLAGS) -o $@ $(INC_FILE) $(SRC_FILE) $(LIBS)
clean:
	rm -rf $(TRAGET)
