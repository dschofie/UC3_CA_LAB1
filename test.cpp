#include <iostream>
#include <fstream>
int main()
{
	std::ofstream outputFile("result1.txt");
	outputFile << "the test worked\n";
	//outputFile.close();
}