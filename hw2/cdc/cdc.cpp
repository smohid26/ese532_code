#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <iostream>
#include <chrono>

#define WIN_SIZE 16
#define PRIME 3
#define MODULUS 256
#define TARGET 0

uint64_t hash_func(unsigned char *input, unsigned int pos)
{
	uint64_t hash = 0;
  for (int i = 0; i < WIN_SIZE; i++){
    hash += input[pos+WIN_SIZE-1-i]*(std::pow(PRIME, i+1));
	}
  return hash;
}

void cdc(unsigned char *buff, unsigned int buff_size)
{
	for (unsigned int i = WIN_SIZE; i < buff_size-WIN_SIZE; i++){
    if(((hash_func(buff, i) % MODULUS)) == TARGET){
      std::cout << i << " "; 
		}
	}

	std::cout << std::endl;

}

void cdc_v2(unsigned char *buff, unsigned int buff_size)
{
	uint64_t hash = hash_func(buff, WIN_SIZE);
	for (unsigned int i = WIN_SIZE; i < buff_size-WIN_SIZE; i++){
    if(((hash % MODULUS)) == TARGET){
      //std::cout << i << " "; 
		}
		hash = hash*PRIME - buff[i]*std::pow(PRIME, WIN_SIZE+1) + buff[i+WIN_SIZE]*PRIME;
	}

	std::cout << std::endl;

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

	std::chrono::time_point<std::chrono::high_resolution_clock> start_time, end_time;
	start_time = std::chrono::high_resolution_clock::now();

	cdc(buff, file_size);

	end_time = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time-start_time).count();   
	std::cout << "elapsed time: " << elapsed << " ns." << std::endl;
	
	start_time = std::chrono::high_resolution_clock::now();

	cdc_v2(buff, file_size);

	end_time = std::chrono::high_resolution_clock::now();
	elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time-start_time).count();   
	std::cout << "elapsed time v2: " << elapsed << " ns." << std::endl;

    free(buff);
    return;
}

int main()
{
	test_cdc("prince.txt");
	return 0;
}