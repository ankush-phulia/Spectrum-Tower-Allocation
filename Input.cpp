
#include "Structs.h"

// NOT NEEDED?
typedef std::vector<std::unordered_map<int, Bid> > Vec_Maps;
Vec_Maps Company_Bids;
double Time;

int main(int argc, char const *argv[])
{
	std::string infile = argv[1];
	std::ifstream fin;
	fin.open(infile);
	if (fin.is_open())
	{
		fin >> Time;
		int M,B,C;
		fin >> M >> B >> C;
		// std::cout << M << " " <<  B << " " << C << std::endl;
		std::unordered_map<int, Bid> X;
		Company_Bids = std::vector<std::unordered_map<int, Bid> > (C);
		for (int i = 0 ; i < B ; i ++)
		{
			// parse Bids.
			Bid xi;
			int comp_i = 0;;
			double price_i = 0.0;
			std::unordered_set<int> regs;
			std::string region = "";

			fin >> comp_i;
			fin >> price_i;

			xi.Bid_Id = i;
			xi.Price = price_i;
			fin >> region;
			while (region != "#")
			{
				// parse Bids.
				// std::cout << region << " Region \n";
				regs.insert(atoi(region.c_str()));
				fin >> region;
			}
			xi.Regions = regs;
			Company_Bids[comp_i][i] = xi;
		}
		// all Bids parsed.
	}
	return 0;
}