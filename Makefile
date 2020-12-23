all:
	g++ -c entities.cpp && g++ -c util.cpp && g++ entities.o util.o versao1.cpp -lglut -lGLU -lGL
run:
	./a.out
runA:
	g++ -c entities.cpp && g++ -c util.cpp && g++ entities.o util.o versao1.cpp -lglut -lGLU -lGL && ./a.out