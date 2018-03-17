//driver for Assignment 2

#include <iostream>
#include <string>
#include "../include/VolImage.h"

using namespace std;

int main(int argc, char const *argv[])
{
	/* code */
	string imageBaseName;
	
	bool option_d = false;
	string output_name_d;
	int d_i;
	int d_j;

	bool option_x = false;
	string output_name_x;
	int x_i;

	if (argc == 1)
	{
		cout << "Usage: volimage <imageBase> [-d i j output_name] [-x i output_name]" << endl;
		return 0;
	}
	imageBaseName = string(argv[1]);
	for (int i = 2; i < argc; ++i)
	{
		if(string(argv[i]) == "-d")
		{
			option_d = true;
			d_i = stoi(string(argv[i+1]));
			d_j = stoi(string(argv[i+2]));
			output_name_d = string(argv[i+3]);
		}
		if(string(argv[i]) == "-x")
		{
			option_x = true;
			x_i = stoi(string(argv[i+1]));
			output_name_x = string(argv[i+2]);
		}
	}//end for

	if(option_d && option_x)
	{
		cout << "Both operations cannot be invoked at the same time.\nProgram exiting..." << endl;
		return 0;
	}
	else
	{
		cout << "imageBase = " << imageBaseName << endl;
		if(option_d)
		{
			cout << "-d is true\n" << "map between " << d_i << " and " << d_j << endl;
			cout << "Output to " << output_name_d << endl;
		}
		else if(option_x)
		{
			cout << "-x is true\n" << "extract number " << x_i << endl;
			cout << "Output to " << output_name_x << endl;
		}//edn if
		AMDMIK002::VolImage VI;
		bool good = VI.readImages(imageBaseName);
		if(option_d)
		{
			VI.diffmap(d_i, d_j, output_name_d);
			cout << "Difference map bewteen images " << d_i << " and " << d_j << " has been completed" << endl;
		}
		else if(option_x)
		{
			VI.extract(x_i, output_name_x);
			cout << "Extraction of image " << d_i << " has been completed" << endl;
		}
		//VI.print(1);
		return 0;
	}

	
}