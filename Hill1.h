
#ifndef HILL1_H
#define HILL1_H

#include "structs.h"
#include "State_Manip.h"

// State HillClimb(State &s, int i,int cnt, int C, int passes);

// State randomHillClimb(State &s, int i,int cnt, int C, int passes){

//     // start state determined by var State
//     bool chk = false;
//     std::set<Bid> bidsofCompany = Company_Bids[i];
//     int max_profit = INT_MIN;
//     Bid bestbid;
//     Types::Price_Bids best_clash;
//     outfile << "Company " << i << std::endl;
//     for (auto it = bidsofCompany.begin(); it != bidsofCompany.end(); it++){
//         Bid b = *it;
//         Types::Price_Bids clash = checkClashBidwithState(b,s);
//         if ((b.Price - clash.first) > max_profit)
//         {
//             max_profit = b.Price - clash.first;
//             bestbid = b;
//             best_clash = clash;
//         }
//     }
//     if (max_profit > 0)
//     {
//         addBidtoState(bestbid, s, best_clash);

//     }
//     outfile << "Company " << i << "Profit : " << s.Profit << std::endl;
//     if (cnt >= C*passes){
//         return s;
//     }
//     else if (cnt>=2*C){
//         return HillClimb(s,(i+1)%C,cnt+1,C, passes);
//     }
//     else{
//         int randomComp = i;
//         while (randomComp == i){
//         //rnjesus to get random state for start
//             std::mt19937 rng;
//             rng.seed(std::random_device()());
//             std::uniform_int_distribution<std::mt19937::result_type> randomCompGen(0,C-1);
//             randomComp = randomCompGen(rng);
//         }
//         return randomHillClimb(s,randomComp,cnt+1,C, passes);
//     }
// }

State HillClimb(State &s, int i,int cnt, int C, int passes){
    // start state determined by var State
    bool chk = false;
    std::set<Bid> bidsofCompany = Company_Bids[i];
    int max_profit = INT_MIN;
    Bid bestbid;
    Types::Price_Bids best_clash;
    outfile << "Company " << i << std::endl;
    int noBids = bidsofCompany.size();
    std::vector<int> bidsofCompanyVec (noBids);
    int j = 0;

    //get random bid id

    // std::mt19937 rng;
    // rng.seed(std::random_device()());
    // std::uniform_int_distribution<std::mt19937::result_type> randomBidGen(0,noBids-1);
    // int randomBidId = randomBidGen(rng);
    // Types::Price_Bids rand_clash;

    for (auto it = bidsofCompany.begin(); it != bidsofCompany.end(); it++){
        Bid b = *it;
        bidsofCompanyVec[j] = b.Bid_Id;
        //find the clash
        Types::Price_Bids clash = checkClashBidwithState(b,s);
        // if (j==randomBidId){
        //     rand_clash = clash;
        // }

        if ((b.Price - clash.first) > max_profit) 
        {
            max_profit = b.Price - clash.first;
            bestbid = b;
            best_clash = clash;
        }
        j ++;
    }
    //get a random double
    double random = ((double) rand() / (RAND_MAX));
    // std::cout << random << std::endl;
    // if (random<=0.001){
    //     Bid randomBid = allBids[bidsofCompanyVec[randomBidId]];
    //     addBidtoState(randomBid, s, rand_clash);
    // }
    // else{
    // }
            addBidtoState(bestbid, s, best_clash);
    outfile << "Company " << i << "Profit : " << s.Profit << std::endl;
    if (cnt >= C*passes){
        return s;
    }
//    else if (cnt>=C){
//        return randomHillClimb(s,(i+1)%C,cnt+1,C, passes);
//    }
    else{
        return HillClimb(s,(i+1)%C,cnt+1,C, passes);
    }
}

void Restart_Hill()
{
    // RANDOM RESTART FOR NOOB LS:
    State BestState;
    BestState.Profit = 0;
    for (int i = 0 ; i < C ; i ++)
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

        Curr2 = HillClimb(Curr2 , (i+1)%C , 0 , C, 4);
        if (Curr2.Profit > BestState.Profit)
            BestState = Curr2;
        outfile << "\n \n \n";
    }
    outfile << " >>>>>> BESTSTATE IS  >>>>>>>> \n";
    outfile << "Profit : " << BestState.Profit << std::endl;
}

#endif
