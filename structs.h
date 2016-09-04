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
#include <limits.h>
#include <ctime>
#include <thread>
#include <future>

int Start;
extern double Time;
extern int M,B,C;


struct Bid{
    int Bid_Id;
    int Company;
    double Price;
    std::set<int> Regions;

    //to compare based on price
    bool operator < (const Bid& str) const{
        if ((Regions.size()) != (str.Regions.size())){
            return (Regions.size()) < (str.Regions.size());
        }
        else{
            return Price >= str.Price;
        }
        //return (Price) >= (str.Price);
    }

};

struct State{
//    std::set<int> Bid_ids;
    int Profit;
    std::vector<int> Bids_Company;       // size = C
    std::vector<int> Regions_assigned;  // size = M
};

namespace Types
{
    typedef std::vector<std::set<Bid> > Vec_of_Maps;   // company to set of Bid IDs.
    typedef std::pair<int,std::unordered_set<int> > Price_Bids;
}
extern Types::Vec_of_Maps Company_Bids;
extern std::vector<Bid> allBids;
extern std::vector<Bid> Sorted_Bids;
extern std::ofstream outfile;
extern std::mt19937 rng;
extern int Avg_regions;
extern int Max_regions;
extern time_t Start_Time;
//  Array of vector(unordered map) of bids Company -> Set of Bids. GLOBAL CONST

#endif
