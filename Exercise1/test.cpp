#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include "external_sort.hpp"

using namespace std;

uint64_t determine_system_memory() {
	return 4*1024*1024;
}

int main() {
	cout << "Test program!" << endl;
	int inFile = open("in.txt", O_RDONLY);
	int outFile = open("out.txt", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	if (inFile < 0 || outFile < 0) {
        perror("File does not exist");
		exit (1);
	}

	// fseek(in, 0, SEEK_END);
	// uint64_t inFileSize = ftell(in) / sizeof(uint64_t);
	// fseek(in, 0, SEEK_SET);
	uint64_t inFileSize = 10;
	external_sort(inFile, inFileSize, outFile, determine_system_memory());
}