#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string>
#include "Utilities.h"

#define WIN_SIZE 16
#define PRIME 3
#define MODULUS 256
#define TARGET 0
#define NUM_THREADS 4

uint64_t hash_func(unsigned char *input, unsigned int pos)
{
	uint64_t hash = 0;
  for (int i = 0; i < WIN_SIZE; i++){
    hash += input[pos+WIN_SIZE-1-i]*(std::pow(PRIME, i+1));
	}
  return hash;
}

void cdc(unsigned char *buff, int start_index, int end_index, std::string* output)
{
	for (unsigned int i = start_index; i < end_index; i++){
    if(((hash_func(buff, i) % MODULUS)) == TARGET){
      *output += std::to_string(i) + " "; 
		}
	}

}

void test_cdc( const char* file )
{
	FILE* fp = fopen(file,"r" );
	if(fp == NULL ){
		perror("fopen error");
		return;
	}

	fseek(fp, 0, SEEK_END); // seek to end of file
	int file_size = ftell(fp); // get current file pointer
	fseek(fp, 0, SEEK_SET); // seek back to beginning of file

	unsigned char* buff = (unsigned char *)malloc((sizeof(unsigned char) * file_size ));	
	if(buff == NULL)
	{
		perror("not enough space");
		fclose(fp);
		return;
	}

	int bytes_read = fread(&buff[0],sizeof(unsigned char),file_size,fp);

	// parallelize cdc over 4 threads here
	int input_size = ((file_size/4)*WIN_SIZE)/WIN_SIZE;

	std::string output1, output2, output3, output4;

	std::vector<std::thread> ths;
  ths.push_back(std::thread(&cdc, buff, WIN_SIZE, input_size, &output1));
	ths.push_back(std::thread(&cdc, buff, input_size, input_size*2, &output2));
	ths.push_back(std::thread(&cdc, buff, input_size*2, input_size*3, &output3));
	ths.push_back(std::thread(&cdc, buff, input_size*3, file_size - WIN_SIZE, &output4));

  pin_thread_to_cpu(ths[0], 0);
  pin_thread_to_cpu(ths[1], 1);
	pin_thread_to_cpu(ths[2], 2);
  pin_thread_to_cpu(ths[3], 3);

  for (auto &th : ths)
  {
    th.join();
  }

	std::cout << output1 << output2 << output3 << output4 << std::endl;
	// cdc(buff, file_size);

    free(buff);
    return;
}

int main()
{
	test_cdc("../data/prince.txt");
	return 0;
}