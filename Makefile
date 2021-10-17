TARGET := tradebot
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
SRC_FILES := $(SRC_FILES) $(wildcard $(SRC_DIR)/data/*.cpp)
SRC_FILES := $(SRC_FILES) $(wildcard $(SRC_DIR)/data/types/*.cpp)
SRC_FILES := $(SRC_FILES) $(wildcard $(SRC_DIR)/helpers/*.cpp)
SRC_FILES := $(SRC_FILES) $(wildcard $(SRC_DIR)/functions/*.cpp)
SRC_FILES := $(SRC_FILES) $(wildcard $(SRC_DIR)/threads/*.cpp)

OBJ_FILES := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Need added include path openssl boost cpprest
INCL_PATH := $(SRC_DIR) ../rapidjson/include ../websocketpp
INCL_FLAGS := $(patsubst %,-I%,$(INCL_PATH))

# Need added lib path openssl boost cpprest
#LD_PATH := 
LD_PATH_FLAGS := #$(patsubst %,-L%,$(LD_PATH))
LD_NAME := cpprest boost_system pthread crypto ssl boost_date_time boost_filesystem
LD_NAME_FLAGS := $(patsubst %,-l%,$(LD_NAME))

# -static not working from cpprest
LD_FLAGS := 
CXXFLAGS := -std=c++17 -O2 -Wall -c -fmessage-length=0 -DSSL_R_SHORT_READ=219
CXX := g++

all: dirs $(BIN_DIR)/$(TARGET) move_bin

dirs:
	mkdir -p $(OBJ_DIR)/$(SRC_DIR) \
	$(OBJ_DIR)/$(SRC_DIR)/data \
	$(OBJ_DIR)/$(SRC_DIR)/data/types \
	$(OBJ_DIR)/$(SRC_DIR)/helpers \
	$(OBJ_DIR)/$(SRC_DIR)/functions \
	$(OBJ_DIR)/$(SRC_DIR)/threads \
	$(BIN_DIR)/etc/rsyslog.d \
	$(BIN_DIR)/etc/systemd/system \
	$(BIN_DIR)/usr/local/bin \


move_bin:
	mv $(BIN_DIR)/$(TARGET) $(BIN_DIR)/usr/local/bin/$(TARGET)
	cp -f local_settings/config.json $(BIN_DIR)/usr/local/bin/config.json

$(BIN_DIR)/$(TARGET): $(OBJ_FILES)
	$(CXX) $(LD_FLAGS) $^ -o $@ $(LD_PATH_FLAGS) $(LD_NAME_FLAGS)
 
$(OBJ_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCL_FLAGS) -c -o $@ $<
	
clean:
	rm -Rf $(OBJ_DIR)
	rm -Rf $(BIN_DIR)

run:
	$(BIN_DIR)/usr/local/bin/./$(TARGET)
