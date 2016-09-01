#ifndef STRUCTS_H
#define STRUCTS_H

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <random>
#include <map>
#include <set>

struct Bid
{
    int Bid_Id;
    int Company;
    double Price;
    std::set<int> Regions;
};

struct State
{
    std::vector<Bid> Company_Bid;
    std::unordered_map<int, int> Regions;
};



//  Array of vector(unordered map) of bids Company -> Set of Bids. GLOBAL CONST

#endif // STRUCTS_H
