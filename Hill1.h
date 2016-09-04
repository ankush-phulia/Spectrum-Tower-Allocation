
#ifndef HILL1_H
#define HILL1_H

#include "structs.h"
#include "State_Manip.h"

State HillClimb(State &s, int i,int cnt, int C, int passes){
    // start state determined by var State
    bool chk = false;
    std::set<Bid> bidsofCompany = Company_Bids[i];
    int max_profit = INT_MIN;
    Bid bestbid;
    Types::Price_Bids best_clash;
    // outfile << "Company " << i << std::endl;
    int noBids = bidsofCompany.size();
    std::vector<int> bidsofCompanyVec (noBids);
    int j = 0;
    double random = ((double) rand() / (RAND_MAX));
    //get random bid id
    std::uniform_int_distribution<std::mt19937::result_type> randomBidGen(0,noBids-1);
    // std::mt19937 rng;
    int randomBidId = randomBidGen(rng);
    Types::Price_Bids rand_clash;

    if (random<=0.0008){
        Bid randomBid = allBids[bidsofCompanyVec[randomBidId]];
        rand_clash = checkClashBidwithState(randomBid, s);
        addBidtoState(randomBid, s, rand_clash);
    }
    else{
            for (auto it = bidsofCompany.begin(); it != bidsofCompany.end(); it++){
                Bid b = *it;
                bidsofCompanyVec[j] = b.Bid_Id;
                //find the clash
                Types::Price_Bids clash = checkClashBidwithState(b,s);
                if (j==randomBidId){
                    rand_clash = clash;
                }

                if ((b.Price - clash.first) > max_profit) 
                {
                    max_profit = b.Price - clash.first;
                    bestbid = b;
                    best_clash = clash;
                }
                j ++;
            }
            addBidtoState(bestbid, s, best_clash);
    }


    //get a random double
    // std::cout << random << std::endl;
    // outfile << "Company " << i << "Profit : " << s.Profit << std::endl;
    if ((time(0) - Start_Time > (60*Time - 10))  || cnt >= C*passes){
        return s;
    }
   // else if (cnt>=C){
   //     return randomHillClimb(s,(i+1)%C,cnt+1,C, passes);
   // }
    else{
        return HillClimb(s,(i+1)%C,cnt+1,C, passes);
    }
}

void Restart_Hill()
{
    // RANDOM RESTART FOR NOOB LS:
    State BestState;
    BestState.Profit = 0;
    rng.seed(std::random_device()());


    for (int i = 0 ; i < 4*C ; i ++)
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

        Curr2 = HillClimb(Curr2 , (i+1)%C , 0 , C, 4); //number of passes
        if (Curr2.Profit > BestState.Profit)
            BestState = Curr2;
        // outfile << 
        // outfile << "\n \n \n";
        if ((time(0) - Start_Time > (60*Time - 9))){
            break;
        }
    }
    //outfile << " >>>>>> BESTSTATE IS  >>>>>>>> \n";
    std::cout << "Profit : " << BestState.Profit << std::endl;
}

#endif
