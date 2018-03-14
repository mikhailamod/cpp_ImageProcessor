//AMDMIK002

#include "../include/VolImage.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

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
		std::ifstream header(header_file);
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
		unsigned char * cols;

		//loop through each file
		for (int file_num = 0; file_num < num_files; ++file_num)
		{
			std::string file = "../lib/brain_mri_raws/" + baseName + std::to_string(file_num) + ".raw";
			std::ifstream raw_file(file, std::ios::binary);

			if(!raw_file)
			{
				std::cout << "Error: Could not open " + file << std::endl;
				return false;
			}
			unsigned char ** rows = new unsigned char*[VolImage::height];

			//read through each line
			while(!raw_file.eof())
			{
				for (int i = 0; i < VolImage::height; ++i)
				{
					cols = new unsigned char[VolImage::width];//a new array for columns
					raw_file.read((char *)cols, VolImage::width);//read from raw file and store WIDTH items in cols Array
					rows[i] = cols;
					delete cols;
				}//end for
			}//end while
			slices.push_back(rows);
		}//end for

		return true;
		
	}//end

	//DEBUG
	void VolImage::print(int num)
	{
		for (int i = 0; i < num; ++i)
		{
			for (int j = 0; j < VolImage::height; ++j)
			{
				for (int k = 0; k < VolImage::width; ++k)
				{
					std::cout << (int)slices[i][j][k];
				}
				std::cout << std::endl;
			}
			std::cout << "----NEW SLICE----" << std::endl;
		}
	}

	//compute difference map and write out
	//(unsigned char)(abs((float)volume[i][r][c] - (float)volume[j][r][c])/2)
	void VolImage::diffmap(int sliceI, int sliceJ, std::string output_prefix)
	{
		unsigned char ** array_i = slices[sliceI];
		unsigned char ** array_j = slices[sliceJ];
		std::ofstream outfile(output_prefix, std::ios::out | std::ios::app  | std::ios::binary);
		for (int i = 0; i < VolImage::height; ++i)
		{
			unsigned char * row = new unsigned char[VolImage::width];
			for (int j = 0; j < VolImage::width; ++j)
			{
				unsigned char c_i = array_i[i][j];
				unsigned char c_j = array_j[i][j];
				float pixel_i = (float)(c_i);
				//std::cout << "DEBUG: " << pixel_i << std::endl;
				float pixel_j = (float)(c_j);
				float diff = pixel_i - pixel_j;
				float abs = std::abs(diff);
				float output_num = abs/2;
				//output_num = output_num*255;
				unsigned char temp = output_num;
				row[VolImage::width] = temp;
			}
			outfile.write((char*)(row), VolImage::width);
			delete row;
		}
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

