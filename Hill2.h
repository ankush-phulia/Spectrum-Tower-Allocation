
#ifndef HILL2_H
#define HILL2_H

#include "structs.h"
#include "State_Manip.h"

State HillClimb2(State &s, int i,int cnt, int C)
{
    // start state determined by var State
    bool chk = false;
    std::set<Bid> bidsofCompany = Company_Bids[i];
    outfile << "Company " << i << std::endl;
    for (auto it = bidsofCompany.begin(); it != bidsofCompany.end(); it++){
        Bid b = *it;
        Types::Price_Bids clash = checkClashBidwithState(b,s);
        chk = addBidtoState(b, s, clash);
    }
    outfile << "Company " << i << "Profit : " << s.Profit << std::endl;
    if (cnt >= C){
        return s;
    }
    else{
        return HillClimb2(s,(i+1)%C,cnt+1,C);
    }

}

void Restart_Hill2()
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
        Curr2 = HillClimb2(Curr2 , i%C , 0 , C);
        if (Curr2.Profit > BestState.Profit)
            BestState = Curr2;
        outfile << "\n \n \n";
    }
    outfile << " >>>>>> BESTSTATE IS  >>>>>>>> \n";
    outfile << "Profit : " << BestState.Profit << std::endl;
}

#endif
