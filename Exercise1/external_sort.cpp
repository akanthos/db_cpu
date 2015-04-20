#include "external_sort.hpp"
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
using namespace std;

struct stat fileStat;
uint64_t *buffer;
uint64_t chunkSize;

// int write_to_file(int fd, char *buffer)
// {
// 	size_t len, idx;
// 	ssize_t wcnt;
// 	idx = 0;
// 	len = strlen(buffer);
// 	do {
		
// 		wcnt = write(fd,buffer + idx, len - idx);
// 		if (wcnt == -1)
// 		{ /* error */
// 			perror("write");
// 			return 1;
// 		}
// 		idx += wcnt;
// 	} while (idx < len);
// 	return 0;
// }
uint64_t getNextChunk(int fdInput) {
	cout << "Reading chunk..." << endl;
	//off_t position = lseek(fdInput, 0, SEEK_CUR);
	cout << "Reading from " << fdInput << " at the buffer " << buffer << " a chunk " << chunkSize << endl;
	uint64_t offset = read(fdInput, buffer, chunkSize);
	cout << "Read " << offset << " bytes" << endl;
	while (offset != chunkSize && offset != 0) {
		offset += read(fdInput, buffer+offset, chunkSize);
	}
	if (offset==0) {
		// Reached end of file, return empty buffer
		free(buffer);
		buffer=NULL;
		return 0;
	}
	//lseek(fdInput, position, SEEK_SET);
	return offset;
}
void write_to_file(int fdOutput) {
	cout << "Writing chunk..." << endl;
	uint64_t data_written = write(fdOutput, buffer, chunkSize);
	if (data_written == 0) {
		perror("Error while writing the file");
		exit(1);
	}
	while (data_written != chunkSize) {
		data_written += write(fdOutput, buffer, chunkSize);
	}
	
}

void external_sort(int fdInput, uint64_t size, int fdOutput, uint64_t memSize) {


	FILE *inFile = fdopen(fdInput, "r");
	FILE *outFile = fdopen(fdOutput, "w");

	cout << "Size of buffer: " << memSize << endl;
	// Begin sorting
	chunkSize = (memSize / sizeof(uint64_t));
	cout << "Size of actual buffer: " << chunkSize << " elements" << endl;
    unsigned chunk_number;
    if (size < chunkSize)
    	chunk_number = 1;
    else {
    	chunk_number = (size / chunkSize);
    	if (size % chunkSize != 0) chunk_number++;
    }
    cout << "Filesize in elements: " << size << endl;
	cout << "Numbers of chunks: " << chunk_number << endl;

	// Allocate memory buffer

	uint64_t* buffer = (uint64_t *) malloc(chunkSize * sizeof(uint64_t));
	uint64_t elements_read;
	while ( elements_read = fread(buffer, sizeof(uint64_t), chunkSize, inFile)) {
		cout << "Read " << elements_read << " elements" << endl;
		fwrite(buffer, sizeof(uint64_t), elements_read, outFile);
	}

	free(buffer);
	fclose(inFile);
	fclose(outFile);
}