# Directory for the resulting library files
LIB_DIR=lib

# Directory to install the header files in
INST_DIR=inc/2mat

# Directory for the built object files
BUILD_DIR=build

# Directory containing all of the source files
SRC_DIR=src
SRC_SUBDIR= v4 v6 v7 v7_3 io

# Source files from the source directory
LIB_CPP_FILE = container.cpp element.cpp matrix.cpp mstruct.cpp util.cpp \
	v6/write.cpp v7/write.cpp v7/zstream.cpp v7_3/write.cpp io/fwriter.cpp
LIB_SRCS = $(addprefix $(SRC_DIR)/,$(LIB_CPP_FILE))

# The resulting lib file
LIB_FILE = $(LIB_DIR)/lib2mat.a

# The files to install in the include directory
HEAD_FILES = util.hpp types.hpp mstruct.hpp matrix.hpp element.hpp datenum.hpp container.hpp \
	2mat.hpp io/fwriter.hpp
INST_SRC = $(addprefix $(SRC_DIR)/,$(HEAD_FILES))
INST_FILES = $(addprefix $(INST_DIR)/,$(HEAD_FILES))

# Object files for each of the source files
LIB_OBJS=$(addprefix $(BUILD_DIR)/,$(LIB_CPP_FILE:.cpp=.o))

# Include directories, and the libraries to link
LIBS = -lz

# FLAGS
CXXFLAGS := $(CXXFLAGS) -g -std=c++11 -pedantic -Wall -Wextra

.DEFAULT_GOAL := compile
all: compile $(LIB_FILE) $(INST_FILES) # testcompile $(TEST_BIN)

ifdef INSTALL_DIR
install: compile $(LIB_FILE) $(INST_FILES)
	mkdir -p $(INSTALL_DIR)/$(INST_DIR)
	mkdir -p $(INSTALL_DIR)/$(LIB_DIR)
	rm -f $(INSTALL_DIR)/$(INST_DIR)/*
	rm -f $(INSTALL_DIR)/$(LIB_DIR)/$(notdir $(LIB_FILE))
	cp $(INST_FILES) $(INSTALL_DIR)/$(INST_DIR)/
	cp $(LIB_FILE) $(INSTALL_DIR)/$(LIB_DIR)/
else
install:
	$(error INSTALL_DIR must be specified to use `make install`)
endif

compile: $(LIB_OBJS)

$(INST_FILES): $(INST_DIR)
	cp $(patsubst $(INST_DIR)/%,$(SRC_DIR)/%, $@) $(INST_DIR)/$(dir $(patsubst $(INST_DIR)/%,%, $@))

$(LIB_DIR)/%.a: $(LIB_OBJS) $(LIB_DIR)
	ar rc $@ $(LIB_OBJS)
	ranlib $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<
	
$(LIB_DIR):
	mkdir -p $(LIB_DIR)

$(INST_DIR):
	mkdir -p $(INST_DIR) $(INST_DIR)/io

$(BUILD_DIR): $(addprefix $(BUILD_DIR)/,$(SRC_SUBDIR))
	mkdir -p $(BUILD_DIR) $(addprefix $(BUILD_DIR)/,$(SRC_SUBDIR))

$(addprefix $(BUILD_DIR)/,$(SRC_SUBDIR)):
	mkdir -p $@

.PHONY: clean
clean:
	rm -f $(addsuffix /*,$(addprefix ./$(BUILD_DIR)/,$(SRC_SUBDIR)))
	rm -fd $(addprefix ./$(BUILD_DIR)/,$(SRC_SUBDIR))
	rm -f ./$(BUILD_DIR)/* ./$(LIB_FILE)
	rm -rf ./$(INST_DIR)