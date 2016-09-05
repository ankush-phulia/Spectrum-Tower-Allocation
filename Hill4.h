
#ifndef HILL4_H
#define HILL4_H

#include "structs.h"
#include "State_Manip.h"

State HillClimb4(State &s, int i, int cnt, int passes, std::mt19937 & rng){
    // start state determined by var State
    if (cnt > passes*B || ((time(0) - Start_Time) >  (60*M - 3))){
        return s;
    }
    else{
        if (cnt%B == 0)
            std::cout << s.Profit << " counting \n";
        int max_profit = INT_MIN;
        int best_id = i;
        Types::Price_Bids best_clash;
        for (int count = -3 ; count < 3 ; count ++)
        {
            Bid b = Sorted_Bids[(i+count+B)%B];
            if (s.Bids_Company[b.Company] != b.Bid_Id)
            {
                Types::Price_Bids clash = checkClashBidwithState(b, s);
                // more prof, more clash.first-b.Regions.
                if ((b.Price - clash.second.first) >= max_profit)
                {
                    best_id = (i+count+B)%B;
                    best_clash = clash;          
                }          
            }
        }
        if (max_profit != INT_MIN)
        {
            bool chk2 = addBidtoState(Sorted_Bids[best_id],s,best_clash, false);
            if (chk2)
                return HillClimb4(s, (i+3)%B, cnt+1, passes, rng);
            else
                return HillClimb4(s, (best_id+4)%B, cnt+1, passes, rng);
        }
        else
        {
            // add i itself.
            Bid b = Sorted_Bids[i];
            best_clash = checkClashBidwithState(b,s);
            addBidtoState(b, s, best_clash, false);
            return HillClimb4(s, (i+2)%B , cnt + 1, passes, rng);
        }
            
        // if (cnt%B == 0)
        //     std::cout << "YO" << s.Profit << std::endl;
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


void Restart_Hill4(State & best)
{
    // MLock.lock();
    // RANDOM RESTART FOR NOOB LS:
    // State best;
    // best.Profit = 0;
    // std::cout << (60*Time) << " hill 4 CALLED! \n";
    std::mt19937 rng;

    for (int i = 0 ; i < 5*C/2 ; i ++) //number of restarts
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

        // randomBidId = randomBidGen(rng)%B;
        // randomBid = allBids[randomBidId];
        // Types::Price_Bids clash2 = checkClashBidwithState(randomBid,Curr2);
        // while (clash2.second.second.size() != 0){
        //     randomBidId = randomBidGen(rng)%B;
        //     randomBid = allBids[randomBidId];
        //     clash2 = checkClashBidwithState(randomBid,Curr2);
        // }
        // addBidtoState(randomBid, Curr2, clash2, false);

        int passes = 10;
        if  ((B/C)>=3 && 5>(B/C)){
            passes = 2*(B/C) - 1;
        }
        else if ((B/C)<=2 ){
            passes = 3*(B/C) - 1;
        }
        else{
            if (C>=5){
                passes = 5;
            }
            else{
                passes = 4;
            }
        }
        // outfile << "Start : " << randomBidId << std::endl;
        Curr2 = HillClimb4(Curr2 , (i+1)%B, 0, passes, rng);
        // std::cout << Curr2.Profit << std::endl;
        if (Curr2.Profit > best.Profit)
        {
            best = Curr2;
        }
        // if (checkValidity(best))
        //     std::cout << "ALL COOL! \n";
        std::cout << "Hill 4 :: " << Curr2.Profit << " Best yet of Hill4 : " << best.Profit << std::endl;
        if ((time(0) - Start_Time > (60*Time - 3))){
            break;
        }
        //outfile << "\n \n \n";
    }
    //outfile << " >>>>>> BESTSTATE IS  >>>>>>>> \n";
    std::cout << "BESTSTATE 4 Profit : " << best.Profit << std::endl;
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
