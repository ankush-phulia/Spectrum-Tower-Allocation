
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
    outfile << "Company " << i << std::endl;
    for (auto it = bidsofCompany.begin(); it != bidsofCompany.end(); it++){
        Bid b = *it;
        Types::Price_Bids clash = checkClashBidwithState(b,s);
        if ((b.Price - clash.first) > max_profit) 
        {
            max_profit = b.Price - clash.first;
            bestbid = b;
            best_clash = clash;
        }
    }
    if (max_profit > 0)
    {
        addBidtoState(bestbid, s, best_clash);
        
    }
    outfile << "Company " << i << "Profit : " << s.Profit << std::endl;
    if (cnt >= C*passes){
        return s;
    }
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
        Curr2 = HillClimb(Curr2 , i%C , 0 , C, 2);
        if (Curr2.Profit > BestState.Profit)
            BestState = Curr2;
        outfile << "\n \n \n";
    }
    outfile << " >>>>>> BESTSTATE IS  >>>>>>>> \n";
    outfile << "Profit : " << BestState.Profit << std::endl;
}

#endif
