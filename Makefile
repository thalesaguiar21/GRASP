all:
	g++ ReaderWriter.cpp gap.cpp Main.cpp -o gap
run:
	./gap
clean:
	rm gap