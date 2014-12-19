GPP=-O2
all: parser
	@echo "Compile Done."

parser: valuedfa.o number_dfa.o stringdfa.o arraydfa.o dfa.o value.o main.o objectdfa.o nildfa.o booldfa.o
	g++ $(GPP) -std=c++11 -pg -g -o labeler.exe number_dfa.o stringdfa.o arraydfa.o dfa.o value.o main.o valuedfa.o objectdfa.o booldfa.o nildfa.o

objectdfa.o: objectdfa.hpp objectdfa.cpp
	g++ $(GPP) -c -std=c++11 objectdfa.cpp

number_dfa.o: number_dfa.hpp number_dfa.cpp
	g++ $(GPP) -c -std=c++11 number_dfa.cpp

stringdfa.o: stringdfa.hpp stringdfa.cpp
	g++ $(GPP) -c  -std=c++11 stringdfa.cpp

value.o: value.hpp value.cpp
	g++ $(GPP) -c  -std=c++11 value.cpp

valuedfa.o: valuedfa.hpp valuedfa.cpp
	g++ $(GPP) -c  -std=c++11 valuedfa.cpp
	
arraydfa.o: arraydfa.hpp arraydfa.cpp
	g++ $(GPP) -c  -std=c++11 arraydfa.cpp

dfa.o: dfa.hpp dfa.cpp
	g++ $(GPP) -c  -std=c++11 dfa.cpp

booldfa.o: booldfa.hpp booldfa.cpp
	g++ $(GPP) -c -std=c++11 booldfa.cpp
nildfa.o: nildfa.hpp nildfa.cpp
	g++ $(GPP) -c -std=c++11 nildfa.cpp
main.o: config_parser.cpp
	g++ $(GPP) -c  -std=c++11 config_parser.cpp -o main.o
clean:
	rm *.o
