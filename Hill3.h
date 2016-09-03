
#ifndef HILL3_H
#define HILL3_H

#include "structs.h"
#include "State_Manip.h"

State HillClimb3(State &s, int i, int cnt, int passes){
    // start state determined by var State
    if (cnt > passes*B){
        return s;
    }
    else{
        Bid b = Sorted_Bids[i];
        bool chk2 = addBidtoState(b,s,clash);
        return HillClimb3(s, (i+1)%B, cnt+1, passes);
        Types::Price_Bids clash = checkClashBidwithState(b, s);
    }
    std::cout << "Pass 1 : Profit->" << s.Profit << std::endl;
    }
//    for (int cnt = 0 ; cnt <= passes*B ; cnt ++)
//    {
//        Bid b = Sorted_Bids[i];
//        Types::Price_Bids clash = checkClashBidwithState(b, s);
//        bool chk2 = addBidtoState(b,s,clash);
//        i = (i+1)%B;
//        if (cnt%B == 0)
//            std::cout << "Pass 1 : Profit->" << s.Profit << std::endl;
//    }
//    std::cout << "Profit->" << s.Profit << std::endl;

}

void Restart_Hill3()
{
    // RANDOM RESTART FOR NOOB LS:
    State BestState;
    BestState.Profit = 0;
    for (int i = 0 ; i < 3*C ; i ++)
    {
        State Curr2;
        Curr2.Profit = 0;
        Curr2.Bids_Company = std::vector<int> (C,-1);
        Curr2.Regions_assigned = std::vector<int> (M,-1);

        //rnjesus to get random state for start
//        std::mt19937 rng;
//        rng.seed(std::random_device()());
//        std::uniform_int_distribution<std::mt19937::result_type> randomBidGen(0,Company_Bids[i].size()-1);

//        //add this to empty state
//        int randomBid = randomBidGen(rng);
//        Bid b = (Company_Bids[i])[randomBid];
//        Curr2.Bids_Company[b.Company] = b.Bid_Id;
//        Curr2.Profit += b.Price;
//        for (auto it = b.Regions.begin(); it != b.Regions.end(); it++){
//            int region = *it;
//            Curr2.Regions_assigned[region] = b.Bid_Id;
//        }
        std::mt19937 rng;
        rng.seed(std::random_device()());
        std::uniform_int_distribution<std::mt19937::result_type> randomBidGen(0,B-1);
        int randomBidId = randomBidGen(rng)%B;
        Bid randomBid = allBids[randomBidId];
        std::unordered_set<int> empty_set;
        Types::Price_Bids empty_clash = std::make_pair(0, empty_set);
        
        addBidtoState(randomBid, Curr2, empty_clash);

        int passes = 10;
        if  ((B/C)>=3 && 5>(B/C)){
            passes = 2*(B/C)-1;
        }
        else if ((B/C)<=2 ){
            passes = 3*(B/C) + 1;
        }
        else{
            if (C>=5){
                passes = 6;
            }
            else{
                passes = 4;
            }
        }

        Curr2 = HillClimb3(Curr2 , (i+1)%B, 0, passes);
        //std::cout << Curr2.Profit << std::endl;

        if (Curr2.Profit > BestState.Profit){
            BestState = Curr2;
        }
        //outfile << "\n \n \n";
    }
    outfile << " >>>>>> BESTSTATE IS  >>>>>>>> \n";
    outfile << "Profit : " << BestState.Profit << std::endl;

//    for (int j = 0;j<C;j++){

//        int bid = BestState.Bids_Company[j]
//        if (bid != -1){
//           for (int k = 0;k<M;k++){

//            }
//        }
//    }
}

#endif
