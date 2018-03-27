//driver for Assignment 2

#include <iostream>
#include <string>
#include "../include/VolImage.h"

using namespace std;

int main(int argc, char const *argv[])
{
	/* code */
	string imageBaseName;
	string output_name;
	int parameters = 0;
	
	bool option_d = false;
	int d_i;
	int d_j;

	bool option_x = false;
	int x_i;

	bool option_g = false;
	int g_i;

	if (argc == 1)//if no imageName is given
	{
		cout << "Usage: volimage <imageBase> [-d i j output_name] [-x i output_name] [-g i output_name]" << endl;
		return 0;
	}

	imageBaseName = string(argv[1]);

	for (int i = 2; i < argc; ++i)
	{
		if(string(argv[i]) == "-d")//if -d command detected
		{
			parameters++;//increase the number of commands used
			option_d = true;
			d_i = stoi(string(argv[i+1]));//the i parameter converted to int
			d_j = stoi(string(argv[i+2]));//the j parameter converted to int
			output_name = string(argv[i+3]);//the output name
		}
		if(string(argv[i]) == "-x")//if -x detected
		{
			parameters++;
			option_x = true;
			x_i = stoi(string(argv[i+1]));
			output_name = string(argv[i+2]);
		}

		if(string(argv[i]) == "-g")
		{
			parameters++;
			option_g = true;
			g_i = stoi(string(argv[i+1]));
			output_name = string(argv[i+2]);
		}
	}//end for

	if(parameters > 1)//if for than one of the commands are called
	{
		cout << "More than 1 operations cannot be invoked at the same time.\nProgram exiting..." << endl;
		return 0;
	}

	else
	{
		cout << "imageBase = " << imageBaseName << endl;
		cout << "Program will search in ../lib/" << imageBaseName << "/ for data and raw files" << endl;
		AMDMIK002::VolImage VI;
		bool good = VI.readImages(imageBaseName);
		if(option_d)
		{
			VI.diffmap(d_i, d_j, output_name);
			cout << "Difference map bewteen images " << d_i << " and " << d_j << " has been completed" << endl;
		}
		else if(option_x)
		{
			VI.extract(x_i, output_name);
			cout << "Extraction of image " << d_i << " has been completed" << endl;
		}
		else if(option_g)
		{
			VI.row_extract(g_i, output_name);
			cout << "Row Extraction for row " << g_i << " has finished" << endl;
		}
		return 0;
	}

	
}