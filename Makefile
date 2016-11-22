all:
	g++ ReaderWriter.cpp gap.cpp Main.cpp -std=c++11 -o grasp
run:
	./grasp
clean:
	rm grasp
