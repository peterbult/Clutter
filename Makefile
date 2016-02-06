EXEC = libclutter

CXX = clang++ -std=c++11 -stdlib=libc++

SRC_DIR     = src
HEADER_DIR  = src
BUILD_DIR 	= build
INSTALL     = /usr/local

# Collect all file names
HEADER		:= $(wildcard $(HEADER_DIR)/*.h)
CPPBASE_SRC := $(wildcard $(SRC_DIR)/*.cpp)
CPPBASE_OBJ := $(patsubst $(SRC_DIR)/%.cpp,build/%.o,$(CPPBASE_SRC))
vpath %.cpp $(SRC_DIR)

#
# |-------------------------------------------------------------------
#

all: checkdirs $(BUILD_DIR)/$(EXEC).dylib $(BUILD_DIR)/$(EXEC).a

# -> This ensures that the local building directory exist
checkdirs: $(BUILD_DIR)

$(BUILD_DIR):
	@mkdir -p $@

# -> This build the C++ object files
$(BUILD_DIR)/%.o: %.cpp
	$(CXX) -c $(addprefix -I ,$(HEADER_DIR)) $< -o $@

# -> This compiles the object files into a dylib
$(BUILD_DIR)/$(EXEC).dylib: $(CPPBASE_OBJ) 
	$(CXX) -dynamiclib $^ -o $(BUILD_DIR)/$(EXEC).dylib

# -> This compiles the object files into a static lib
$(BUILD_DIR)/$(EXEC).a: $(CPPBASE_OBJ) 
	ar rs $(BUILD_DIR)/$(EXEC).a $^

# Install rules |-----------------------------------------

install: makedir all
	@echo "--> installing in" $(INSTALL)
	@cp $(BUILD_DIR)/$(EXEC).dylib $(INSTALL)/lib
	@cp $(BUILD_DIR)/$(EXEC).a $(INSTALL)/lib
	@cp $(HEADER) $(INSTALL)/include/Clutter

# -> This ensures the install directories exists
makedir: $(INSTALL)/include/Clutter

$(INSTALL)/include/Clutter:
	@mkdir $(INSTALL)/include/Clutter

# Some bookkeeping |----------------------------------------

remake: clean all

clean:
	@rm -rf $(BUILD_DIR)/*
	
uninstall:
	@rm -rf $(INSTALL)/lib/$(EXEC).dylib
	@rm -rf $(INSTALL)/lib/$(EXEC).a
	@rm -rf $(INSTALL)/include/Clutter
