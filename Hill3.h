
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
        Types::Price_Bids clash = checkClashBidwithState(b, s);
        bool chk2 = addBidtoState(b,s,clash);
        return HillClimb3(s, (i+1)%B, cnt+1, passes);
    }
    std::cout << "Pass 1 : Profit->" << s.Profit << std::endl;

}

State Restart_Hill3()
{
    // RANDOM RESTART FOR NOOB LS:
    State BestState;
    BestState.Profit = 0;
    for (int i = 0 ; i < 4*C ; i ++) //number of restarts
    {
        State Curr2;
        Curr2.Profit = 0;
        Curr2.Bids_Company = std::vector<int> (C,-1);
        Curr2.Regions_assigned = std::vector<int> (M,-1);

        //random start state added
        std::mt19937 rng;
        rng.seed(std::random_device()());
        std::uniform_int_distribution<std::mt19937::result_type> randomBidGen(0,B-1);
        int randomBidId = randomBidGen(rng)%B;
        Bid randomBid = allBids[randomBidId];
        std::unordered_set<int> empty_set;
        Types::Price_Bids empty_clash = std::make_pair(0, empty_set);
        
        addBidtoState(randomBid, Curr2, empty_clash);

        randomBidId = randomBidGen(rng)%B;
        randomBid = allBids[randomBidId];
        Types::Price_Bids clash2 = checkClashBidwithState(randomBid,Curr2);
        while (clash2.second.size() != 0){
            randomBidId = randomBidGen(rng)%B;
            randomBid = allBids[randomBidId];
            clash2 = checkClashBidwithState(randomBid,Curr2);
        }
        addBidtoState(randomBid, Curr2, clash2);

        int passes = 10;
        if  ((B/C)>=3 && 5>(B/C)){
            passes = 2*(B/C) + 1;
        }
        else if ((B/C)<=2 ){
            passes = 3*(B/C) + 3;
        }
        else{
            if (C>=5){
                passes = 7;
            }
            else{
                passes = 5;
            }
        }

        Curr2 = HillClimb3(Curr2 , (i+1)%B, 0, passes);
        //std::cout << Curr2.Profit << std::endl;

        if (Curr2.Profit > BestState.Profit){
            BestState = Curr2;
        }
        if ((time(0) - Start_Time > (60*Time - 9))){
            break;
        }
        //outfile << "\n \n \n";
    }
    //outfile << " >>>>>> BESTSTATE IS  >>>>>>>> \n";
    std::cout << "Profit : " << BestState.Profit << std::endl;
//    for (int i = 0 ; i < C ; i ++){
//        int k = BestState.Bids_Company[i];
//        if (k!=-1){
//            outfile << k << " ";
//        }
//    }
//    outfile << "#";
    return BestState;
}

#endif
