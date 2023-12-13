
CC = g++
CFLAGS = -Wall -g -I. -lGL -lGLU -lglut -lm
SRCS = Net.cpp NetBuilder.cpp Neuron.cpp Synapse.cpp utils.cpp neuron_spacing.cpp sample.cpp NavGraph.cpp NavNode.cpp NetGraphics.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = sample

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -f $(TARGET) $(OBJS)

save:
		cp sample.cpp sample.save.cpp

run:
	make 
	./sample
