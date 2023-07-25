CXX = g++
CXXFLAGS = -Wall -std=c++11
SRCS = main.cpp searchfile.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = app

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) -pthread

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)