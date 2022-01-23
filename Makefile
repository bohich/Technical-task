test : main.cpp
	g++ main.cpp library/searchfile.a -std=c++2a -o test -lpthread