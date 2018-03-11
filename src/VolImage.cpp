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

	std::vector<int>* getHeader(std::string baseName)
	{
		std::vector<int> line_vector;//for split words
		line_vector.resize(3);
		std::vector<int>* vec_ptr = line_vector;

		std::string header_file = "../lib/" + baseName + ".data";
		std::ifstream header(header_file.c_str());
		if(!header)
		{
			std::cout << "Couldnt open " << header_file << std::endl;
			return vec_ptr;
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
		return vec_ptr;
	}

	//populate object with images in stack and
	//set member variables
	bool VolImage::readImages(std::string baseName)
	{
		int num_files = 0;
		std::vector<int>* header_data = AMDMIK002::getHeader(baseName);
		VolImage::width = header_data[0];
		VolImage::height = header_data[1];
		num_files = header_data[2];
		std::cout << "Width: " << VolImage::width << "\nHeight: " << VolImage::height << "\nNum Images " << num_files << std::endl;
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

