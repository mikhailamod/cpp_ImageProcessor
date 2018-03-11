//AMDMIK002

#include "../include/VolImage.h"
#include <string>
#include <vector>
#include <iostream>

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

	//populate object with images in stack and
	//set member variables
	bool VolImage::readImages(std::string baseName)
	{
		return true;//change
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

