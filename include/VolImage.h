//header for VolImage.cpp
//AMDMIK002

#ifndef VOLIMAGE_H
#define VOLIMAGE_H
#include <string>
#include <vector>
namespace AMDMIK002
{
	class VolImage
	{
	private:
		int width, height;
		std::vector<unsigned char**> slices;
		std::vector<int> getHeader(std::string baseName);
	public:
		VolImage();
		~VolImage();

		bool readImages(std::string baseName);
		void diffmap(int sliceI, int sliceJ, std::string output_prefix);
		void extract(int sliceId, std::string output_prefix);
		int volImageSize(void);
		void print(int num);
	};
}

#endif