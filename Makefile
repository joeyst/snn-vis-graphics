sample:		sample.cpp
		g++   -o sample   sample.cpp  -I. -lGL -lGLU -lglut  -lm


save:
		cp sample.cpp sample.save.cpp

run:
	make 
	./sample