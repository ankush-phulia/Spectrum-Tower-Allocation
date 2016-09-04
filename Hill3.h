
#ifndef HILL3_H
#define HILL3_H

#include "structs.h"
#include "State_Manip.h"

State HillClimb3(State &s, int i, int cnt, int passes, std::mt19937 & rng){
    // start state determined by var State
    if (cnt > passes*B){
        return s;
    }
    else{
        // if (cnt%B == 0)
        //     std::cout << cnt << " : cnt \n";
        Bid b = Sorted_Bids[i];
        Types::Price_Bids clash = checkClashBidwithState(b, s);
        bool chk2 = addBidtoState(b,s,clash, false);
        // if (cnt%B == 0)
        //     std::cout << "YO" << s.Profit << std::endl;
        return HillClimb3(s, (i+1)%B, cnt+1, passes, rng);
    }
    // std::cout << "Pass 1 : Profit->" << s.Profit << std::endl;
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

// void Restart_Hill3()
// {
//     std::cout << "Pass 1 : Profit->" << s.Profit << std::endl;
// }

void Restart_Hill3(State & best)
{
    // MLock.lock();
    // RANDOM RESTART FOR NOOB LS:
    // State best;
    // best.Profit = 0;
    std::mt19937 rng;

    for (int i = 0 ; i < 4*C ; i ++) //number of restarts
    {
        State Curr2;
        Curr2.Profit = 0;
        Curr2.Bids_Company = std::vector<int> (C,-1);
        Curr2.Regions_assigned = std::vector<int> (M,-1);

        //random start state added
        rng.seed(std::random_device()());
        std::uniform_int_distribution<std::mt19937::result_type> randomBidGen(0,B-1);
        int randomBidId = randomBidGen(rng)%B;
        Bid randomBid = allBids[randomBidId];
        std::unordered_set<int> empty_set;
        Types::Price_Bids empty_clash = std::make_pair(0,std::make_pair(0, empty_set));
        
        addBidtoState(randomBid, Curr2, empty_clash, true);

        randomBidId = randomBidGen(rng)%B;
        randomBid = allBids[randomBidId];
        Types::Price_Bids clash2 = checkClashBidwithState(randomBid,Curr2);
        while (clash2.second.second.size() != 0){
            randomBidId = randomBidGen(rng)%B;
            randomBid = allBids[randomBidId];
            clash2 = checkClashBidwithState(randomBid,Curr2);
        }
        addBidtoState(randomBid, Curr2, clash2, false);

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
        // outfile << "Start : " << randomBidId << std::endl;
        Curr2 = HillClimb3(Curr2 , (i+1)%B, 0, passes, rng);
        // std::cout << Curr2.Profit << std::endl;
        if (Curr2.Profit > best.Profit)
        {
            best = Curr2;
        }
        std::cout << "Hill 3 :: " << Curr2.Profit << " Best yet of Hill3 : " << best.Profit << std::endl;
        if ((time(0) - Start_Time > (60*Time - 9))){
            break;
        }
        //outfile << "\n \n \n";
    }
    //outfile << " >>>>>> BESTSTATE IS  >>>>>>>> \n";
    std::cout << "BESTSTATE 3 Profit : " << best.Profit << std::endl;
//    for (int i = 0 ; i < C ; i ++){
//        int k = BestState.Bids_Company[i];
//        if (k!=-1){
//            outfile << k << " ";
//        }
//    }
//    outfile << "#";
    // return BestState;
}

#endif
