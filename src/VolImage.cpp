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

	VolImage::~VolImage()//deconstructor
	{
		delete rows;
		delete cols;
	}

	//get information from header file
	std::vector<int> getHeader(std::string baseName)
	{
		std::vector<int> line_vector;//for split words

		std::string header_file = "../lib/" + baseName + "/" + baseName + ".data";
		std::cout << "Reader header file from " << header_file << std::endl;

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

		//loop through each file
		for (int file_num = 0; file_num < num_files; ++file_num)
		{
			std::string file = "../lib/" + baseName + "/" + baseName  + std::to_string(file_num) + ".raw";
			std::ifstream raw_file(file, std::ios::binary);

			if(!raw_file)
			{
				std::cout << "Error: Could not open " + file << std::endl;
				return false;
			}
			//read through each line
			if(raw_file.is_open())
			{
				rows = new unsigned char*[VolImage::height];
				int pos = 0;
				for (int i = 0; i < VolImage::height; ++i)
				{
					cols = new unsigned char[VolImage::width];//a new array for columns
					raw_file.read((char *)cols, VolImage::width);//read from raw file and store WIDTH items in cols Array
					rows[i] = cols;
				}//end for

				//delete cols;//prevent memory leak

			}//end if
			slices.push_back(rows);
			raw_file.close();//close the file it's writing to
		}//end for
		std::cout << "Number of images: " << slices.size() << std::endl;
		int bytes = volImageSize();
		float mBytes = bytes/1000000;
		std::cout << "Nuber of bytes required: " << bytes << " (" << mBytes << "MB)" << std::endl;
		//delete rows;//prevent memory leak

		return true;
		
	}//end

	//compute difference map and write out
	//formula = (unsigned char)(abs((float)volume[i][r][c] - (float)volume[j][r][c])/2)
	void VolImage::diffmap(int sliceI, int sliceJ, std::string output_prefix)
	{
		unsigned char ** array_i = slices[sliceI];
		unsigned char ** array_j = slices[sliceJ];
		std::ofstream outfile(output_prefix, std::ios::out | std::ios::app  | std::ios::binary);
		for (int i = 0; i < VolImage::height; ++i)
		{
			for (int j = 0; j < VolImage::width; ++j)
			{
				//below is the diff map calculation
				unsigned char c_i = array_i[i][j];
				unsigned char c_j = array_j[i][j];
				float pixel_i = (float)(c_i);
				float pixel_j = (float)(c_j);
				float diff = pixel_i - pixel_j;
				float abs = std::abs(diff);//absolute value
				float output_num = abs/2;
				char temp = output_num;//convert to char before writing

				//write the byte to the file
				outfile.write(&temp, 1);
			}
			
			//delete row;
		}
	}

	//extract slice 'sliceId' and write out
	void VolImage::extract(int sliceId, std::string output_prefix)
	{
		std::ofstream outfile(output_prefix, std::ios::out | std::ios::app  | std::ios::binary);
		for (int i = 0; i < VolImage::height; ++i)
		{
			for (int j = 0; j < VolImage::width; ++j)
			{
				char pixel = slices[sliceId][i][j];
				outfile.write(&pixel, 1);
			}
		}
		outfile.close();
	}//end

	void VolImage::row_extract(int row_num, std::string output_prefix)
	{
		std::ofstream outfile(output_prefix, std::ios::out | std::ios::app  | std::ios::binary);
		for (int file = 0; file < slices.size(); ++file)//for each slice
		{
			for (int col = 0; col < VolImage::width; ++col)//we will access each column in the row_num
			{
				char pixel = slices[file][row_num][col];
				outfile.write(&pixel, 1);
			}//end inner for
		}//end outer for
		outfile.close();
	}

	//num of bytes used to store image data bytes
	//and pointers (ignore vector<> container, dims etc)
	int VolImage::volImageSize(void)
	{
		int total_size = slices.size()*width*height;//the total number of pixels, each 1 byte
		for (int i = 0; i < slices.size(); ++i)
		{
			total_size = total_size + sizeof(slices[i]);//size of row pointer
			for (int j = 0; j < height; ++j)
			{
				total_size += sizeof(slices[i][j]);//size of col pointer
			}//end j loop
		}//end i loop

		return total_size;
	}//end imageSize
}

