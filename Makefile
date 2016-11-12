all:
	g++ ReaderWriter.cpp gap.cpp Main.cpp -o grasp
run:
	./grasp
clean:
	rm grasp
