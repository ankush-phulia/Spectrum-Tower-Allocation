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
#include <functional>

struct Bid{
    int Bid_Id;
    int Company;
    double Price;
    std::set<int> Regions;

    //to compare based on price
    bool operator < (const Bid& str) const{
        return (Price/Regions.size()) >= (str.Price/str.Regions.size());
    }

};

struct State{
//    std::set<int> Bid_ids;
    int Profit;
    std::vector<int> Bids_Company;       // size = C
    std::vector<int> Regions_assigned;  // size = M
};

//  Array of vector(unordered map) of bids Company -> Set of Bids. GLOBAL CONST

#endif
