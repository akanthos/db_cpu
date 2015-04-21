#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <algorithm>
#include "external_sort.hpp"

#define G4 (4294967296) // 4GB in bytes
#define G25 (41943040) // 2,5 GB in 64-bit numbers
#define G5 (167772160) // 5 GB in 64-bit numbers
using namespace std;


bool check_results(char *filename, uint64_t memSize) {
	FILE *resultsFile = fopen(filename, "r");
	uint64_t chunkSize = (memSize / sizeof(uint64_t));
	uint64_t *buff = (uint64_t *) malloc( chunkSize * sizeof(uint64_t));
	uint64_t elem;
	bool sorted = true;
	while ( sorted && ( elem = fread(buff, sizeof(uint64_t), chunkSize, resultsFile) ) ) {
		sorted = ( std::is_sorted(buff, buff+elem) ) ;
	}
	
	return sorted;
}


int main(int argc, char* argv[]) {
	if (argc < 4) {
		std::cerr << "usage: " << argv[0] << " <inputFile> <outputFile> <memoryBufferInMB>" << std::endl;
		return -1;
	}
	uint64_t bytes = strtol(argv[3], NULL, 10);
	// cout << "user gave " << bytes << " bytes" << endl;
	
	int inFile = open(argv[1], O_RDONLY);
	int outFile = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
	if (inFile < 0 || outFile < 0) {
        perror("File does not exist");
		exit (1);
	}

	uint64_t inFileSize;
	inFileSize = lseek(inFile, 0, SEEK_END) / sizeof(uint64_t);
	lseek(inFile, 0, 0);

	
	external_sort(inFile, inFileSize, outFile, bytes);

	if (check_results(argv[2], bytes)) 
		cout << "Results are sorted!" << endl;
	else 
		cout << "Results are NOT sorted ! ! !" << endl;
}