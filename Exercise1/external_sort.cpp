#include "external_sort.hpp"
#include <algorithm>
#include <queue> 
#include <tuple> 
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <string>
#include <sstream>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

using namespace std;

struct stat fileStat;
uint64_t buffer_size = 65536; // 4MB in 64-bit numbers
uint64_t *buffer;
uint64_t chunkSize;
uint64_t *inputBuffer;
uint64_t *outputBuffer;
uint64_t readLimit = buffer_size, inputBfIndex = readLimit, outputBfIndex = 0;



struct my_tuple {
    uint64_t num;
    uint64_t i;
    bool operator<(const my_tuple& rhs) const
    {
        return num < rhs.num;
    }
};
priority_queue<my_tuple> my_queue;

// void print_chunk(uint64_t elements) {
// 	uint64_t *temp = buffer;
// 	for (uint64_t i=0; i<elements; i++) {
// 		cout << temp[i] << endl;
// 	}
// }

void flush(FILE *outFile) {
	if (outputBfIndex > 0) {
		fwrite(outputBuffer, sizeof(uint64_t), outputBfIndex, outFile);
	}
}
void write_to_file(FILE * outFile, uint64_t n) {
	if (outputBfIndex < buffer_size) {
		outputBuffer[outputBfIndex++] = n;
	}
	else {
		fwrite(outputBuffer, sizeof(uint64_t), buffer_size, outFile);
		memset(outputBuffer, 0, buffer_size*sizeof(uint64_t));
		outputBfIndex = 1;
		outputBuffer[0] = n;
	}
}

uint64_t* getNextElement(FILE *f) {
	if (inputBfIndex >= readLimit) {
		memset(inputBuffer, 0, buffer_size*sizeof(uint64_t));
		inputBfIndex = 0;
		readLimit = fread(inputBuffer, sizeof(uint64_t), buffer_size, f);
		if (readLimit==0) return NULL;
	}
	return ( inputBuffer + (inputBfIndex++) );
}

void external_sort(int fdInput, uint64_t size, int fdOutput, uint64_t memSize) {

	// cout << "Size of buffer: " << memSize << endl;
	// Begin sorting
	chunkSize = (memSize / sizeof(uint64_t));
	// cout << "Size of actual buffer: " << chunkSize << " elements" << endl;
    uint64_t chunk_number;
    if (size < chunkSize)
    	chunk_number = 1;
    else {
    	chunk_number = (size / chunkSize);
    	if (size % chunkSize != 0) chunk_number++;
    }
 //    cout << "Filesize in elements: " << size << endl;
	// cout << "Numbers of chunks: " << chunk_number << endl;

	// Opening necessary files
	FILE *inFile = fdopen(fdInput, "r");
	FILE *outFile = fdopen(fdOutput, "w");
	FILE *files[chunk_number];

	

	// Allocate memory buffer
	uint64_t* buffer = (uint64_t *) malloc(chunkSize * sizeof(uint64_t));

	// Read chunks and short them separately
	uint64_t i = 0;
	uint64_t elements_read;
	while ( ( elements_read = fread(buffer, sizeof(uint64_t), chunkSize, inFile) ) ) {
		std::stringstream s;
		s << "tmp" << i;
		string name = s.str();
		files[i] = fopen(name.c_str(), "w");
		std::sort(buffer, buffer+chunkSize, [](uint64_t a, uint64_t b) {  return a < b; } );
		fwrite(buffer, sizeof(uint64_t), elements_read, files[i]);
		fclose(files[i]);
		++i;
	}
	free(buffer);
	fclose(inFile);


	// Merging chunks
	buffer_size = min(buffer_size, chunkSize/2);
	// cout << "Buffer size is: " << buffer_size << endl;
	for (uint64_t i=0; i<chunk_number; i++) {
		std::stringstream s;
		s << "tmp" << i;
		string name = s.str();
		files[i] = fopen(name.c_str(), "r");
	}


	/* -------------- JUST COPYING -----------------*/
	// inputBuffer = (uint64_t *) malloc(buffer_size*sizeof(uint64_t));
	// outputBuffer = (uint64_t *) malloc(buffer_size*sizeof(uint64_t));
	// memset(inputBuffer, 0, buffer_size*sizeof(uint64_t));
	// memset(outputBuffer, 0, buffer_size*sizeof(uint64_t));
	// for (uint64_t i=0; i<chunk_number; i++) {
	// 	uint64_t * temp;
	// 	while ( (temp = getNextElement(files[i]) ) ) {
	// 		write_to_file(outFile, *temp);
	// 	}

	// }
	/* -------------- JUST COPYING -----------------*/


	
	/* -------------- ACTUAL SORTING -----------------*/
	inputBuffer = (uint64_t *) malloc(buffer_size*sizeof(uint64_t));
	for (uint64_t i=0; i<chunk_number; i++) {
		uint64_t *temp = getNextElement(files[i]);
		if (temp) {
			my_tuple elem = {*temp, i};
			my_queue.push(elem);
		}

	}	

	
	outputBuffer = (uint64_t *) malloc(buffer_size*sizeof(uint64_t));
	memset(outputBuffer, 0, buffer_size*sizeof(uint64_t));
	my_tuple temp;
	while (!my_queue.empty()) {
		// Remove min element
		temp = my_queue.top();
		my_queue.pop();
		
		// Write it to output file
		write_to_file(outFile, temp.num);
		
		// Bring next element from input file piece 
		uint64_t *t = getNextElement(files[temp.i]);
		if (t) {
			my_tuple elem = {*t, temp.i};
			my_queue.push(elem);
		}
	}
	/* -------------- ACTUAL SORTING -----------------*/
	
	flush(outFile);
	free(inputBuffer);
	free(outputBuffer);
	for (uint64_t i=0; i<chunk_number; i++) {
		fclose(files[i]);
		std::stringstream s;
		s << "tmp" << i;
		string name = s.str();
		remove(name.c_str());
	}
	fclose(outFile);
}