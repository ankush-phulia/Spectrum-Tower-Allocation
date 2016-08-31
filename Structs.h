
#include <iostream>
#include <unordered_set>
#include <fstream>

struct Bid
{
	int Bid_Id;
	int Company;
	float Price;
	std::unordered_set<int> Regions;
};

struct State
{
	std::vector<Bid> Company_Bid;
	std::unordered_map<int, int> Regions;
};



//  Array of vector(unordered map) of bids Company -> Set of Bids. GLOBAL CONST