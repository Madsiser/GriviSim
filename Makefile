# Program name
TARGET = GraviSim.exe  # Add .exe extension for Windows

# Compiler
CXX = g++

# Check if SFML path is set, if not prompt the user
ifndef SFML_PATH
    $(info SFML library path not set. Please enter the path to your SFML installation.)
    $(info Example: C:\path\to\SFML-2.6.2)
    $(info You can set it by running: export SFML_PATH=/path/to/SFML)
    $(error Please set the SFML_PATH variable)
endif

# Compilation flags
CXXFLAGS = -std=c++11 -I$(SFML_PATH)/include

# Linker flags
LDFLAGS = -L$(SFML_PATH)/lib -lsfml-graphics -lsfml-window -lsfml-system

# Source files
SRCS = main.cpp Obj.cpp

# Object files
OBJS = $(patsubst %.cpp, build/%.o, $(SRCS))

# Default rule
all: createbuild $(TARGET)

# Rule to link object files into the final executable
$(TARGET): $(OBJS) | createbuild
	$(CXX) -o build/$(TARGET) $^ $(LDFLAGS)

# Rule to compile .cpp files into .o object files
build/%.o: %.cpp | createbuild
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to clean up build artifacts
clean:
	rm -f build/*.o build/$(TARGET)

# Rule to create the build directory
createbuild:
	mkdir -p build

# Rule to build the target
build: $(TARGET)

# Rule to run the program with the appropriate library path
run:
	LD_LIBRARY_PATH=$(SFML_PATH)/lib ./build/$(TARGET)
