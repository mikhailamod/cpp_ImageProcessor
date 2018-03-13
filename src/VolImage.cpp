//AMDMIK002

#include "../include/VolImage.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

namespace AMDMIK002
{
	VolImage::VolImage()
	{
		width = 0;
		height = 0;
		slices.resize(0);	
	}

	VolImage::~VolImage()
	{
		
	}

	//get information from header file
	std::vector<int> getHeader(std::string baseName)
	{
		std::vector<int> line_vector;//for split words

		std::string header_file = "../lib/brain_mri_raws/" + baseName + ".data";
		std::ifstream header(header_file.c_str());
		if(!header)
		{
			std::cout << "Couldnt open " << header_file << std::endl;
			return line_vector;
		}
		while(!header.eof())
		{
			std::string line;
			std::getline(header, line);//read data from file and store in line
			
			std::istringstream iss(line);//initialize string stream from line
			std::string token;

			//tokenize the string, using ' ' as delimiter
			while(getline(iss, token, ' '))
			{
				line_vector.push_back(std::stoi(token));//add number to vector
			}
		}//end inner while
		return line_vector;
	}

	//populate object with images in stack and
	//set member variables
	bool VolImage::readImages(std::string baseName)
	{
		int num_files = 0;
		std::vector<int> header_data = AMDMIK002::getHeader(baseName);

		VolImage::width = header_data[0];
		VolImage::height = header_data[1];
		num_files = header_data[2];

		//loop through each file
		for (int file_num = 0; file_num < num_files; ++file_num)
		{
			std::string file = "../lib/brain_mri_raws/" + baseName + std::to_string(file_num) + ".raw";
			std::ifstream raw_file(file.c_str(), ios::binary);

			if(!raw_file)
			{
				std::cout << "Error: Could not open " + file << std::endl;
				return false;
			}

			int line_count = 0;
			unsigned char * cols = new unsigned char *[VolImage::width];
			unsigned char ** rows = new unsigned char*[VolImage::height];

			//read through each line
			while(!raw_file.eof())
			{
				
				line_count++;
			}
		}

		return true;
		
	}

	//compute difference map and write out
	void VolImage::diffmap(int sliceI, int sliceJ, std::string output_prefix)
	{
		std::cout << "this function has not been coded bc im lazy" << std::endl;
	}

	//extract slice 'sliceId' and write out
	void VolImage::extract(int sliceId, std::string output_prefix)
	{
		std::cout << "this function has not been coded bc im lazy" << std::endl;
	}

	//num of bytes used to store image data bytes
	//and pointers (ignore vector<> container, dims etc)
	int VolImage::volImageSize(void)
	{
		return 1;
	}
}

