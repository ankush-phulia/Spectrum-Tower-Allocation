
#include "Structs.h"


int main(int argc, char const *argv[])
{
	std::string infile = argv[0];
	std::ifstream fin;
	fin.open(infile);
	if (fin.is_open())
	{
		double Time;
		fin >> Time;
		int M,B,C;
		fin >> M >> B >> C;
		for (int i = 0 ; i < B ; i ++)
		{
			// parse Bids.
		}
	}
	return 0;
}