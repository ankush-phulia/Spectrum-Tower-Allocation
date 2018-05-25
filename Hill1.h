
#ifndef HILL1_H
#define HILL1_H

#include "structs.h"
#include "State_Manip.h"

State HillClimb(State &s, int i,int cnt, int C, int passes, std::mt19937 & rng){
    // start state determined by var State
    bool chk = false;
    std::set<Bid> bidsofCompany = Company_Bids[i];
    int max_profit = INT_MIN;
    // long int max_clashamt_regs = 0; // find bid with minimum clash amt*(bid regions - clash regions).
    Bid bestbid;
    Types::Price_Bids best_clash;
    // outfile << "Company " << i << std::endl;
    int noBids = bidsofCompany.size();

    // IF NO BIDS THEN DONT DO ANYTHING :----->

    if (noBids == 0) return s;
    std::vector<int> bidsofCompanyVec (noBids);
    int j = 0;
    double random = ((double) rand() / (RAND_MAX));
    //get random bid id
    std::uniform_int_distribution<std::mt19937::result_type> randomBidGen(0,noBids-1);
    // std::mt19937 rng;
    int randomBidId = randomBidGen(rng);
    Types::Price_Bids rand_clash;

    // std::cout << randomBidId << " company : " << i << std::endl;

    for (auto it = bidsofCompany.begin(); it != bidsofCompany.end(); it++){
        Bid b = *it;
        bidsofCompanyVec[j] = b.Bid_Id;
        //find the clash
        Types::Price_Bids clash = checkClashBidwithState(b,s);
        if (j==randomBidId){
            rand_clash = clash;
            if (random <= 0.005)
                break;
        }
        // long profit = b.Price - clash.second.first;
        long profit = f(b,clash);
        if (profit >= max_profit)
        {
            max_profit = profit;
            bestbid = b;
            best_clash = clash;
        }
        j ++;
    }

    if (random<=0.0008){
        Bid randomBid = allBids[bidsofCompanyVec[randomBidId%noBids]%B];
        // std::cout << randomBid.Bid_Id << " is random ID \n";
        rand_clash = checkClashBidwithState(randomBid, s);
        addBidtoState(randomBid, s, rand_clash, true);
    }
    else
    {
        if (max_profit == INT_MIN)
        {
            if (random<=0.01)
            {
                Bid randomBid = allBids[bidsofCompanyVec[randomBidId%noBids]%B];
                // std::cout << randomBid.Bid_Id << " is random ID \n";
                rand_clash = checkClashBidwithState(randomBid, s);
                addBidtoState(randomBid, s, rand_clash, true);                
            }
        }
        else
        {
            // std::cout << bestbid.Bid_Id << " is best ID \n";
            addBidtoState(bestbid, s, best_clash, true);               
        }
    }


    //get a random double
    // std::cout << random << std::endl;
    // outfile << "Company " << i << "Profit : " << s.Profit << std::endl;
    if ((time(0) - Start_Time > (60*Time - 3))  || cnt >= C*passes){
        return s;
    }
   // else if (cnt>=2*C || cnt < C){
   //      return HillClimb(s,(i+1)%C,cnt+1,C, passes);
   // }
    else{
       return HillClimb(s,(i+1)%C,cnt+1,C, passes, rng);
    }
}

void Restart_Hill(State & BestState)
{
    // RANDOM RESTART FOR NOOB LS:
    // MLock.lock();
    std::mt19937 rng;
    rng.seed(std::random_device()());
    //std::cout << (60*Time) << std::endl;

    int i = 0;
    // int last = 0;
    while ((time(0) - Start_Time < 60*Time - 2) && !Over)
    {
    	//std::cout << "1: " << time(0) - Start_Time;
    	//std::cout << " " << 60*Time - 3 << std::endl;
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
        Types::Price_Bids empty_clash = std::make_pair(0, std::make_pair(0, empty_set));
        addBidtoState(randomBid, Curr2, empty_clash, true);

       /* randomBidId = randomBidGen(rng)%B;
        randomBid = allBids[randomBidId];
        Types::Price_Bids clash2 = checkClashBidwithState(randomBid,Curr2);
        while (clash2.second.second.size() != 0){
            randomBidId = randomBidGen(rng)%B;
            randomBid = allBids[randomBidId];
            clash2 = checkClashBidwithState(randomBid,Curr2);
        }
        addBidtoState(randomBid, Curr2, clash2, true);*/

        Curr2 = HillClimb(Curr2 , (i+1)%C , 0 , C, 5, rng); //number of passes
        if (Curr2.Profit > BestState.Profit)
            BestState = Curr2;
        // std::cout << "Hill 1 :: " << Curr2.Profit << " Best yet of Hill1 : " << BestState.Profit << std::endl;
        /*if (time(0)%60 ==0){
			std::cout << "Hill 1 :: " << Curr2.Profit << " Best yet of Hill1 : " << BestState.Profit << std::endl;
        }*/
        // outfile << 
        // outfile << "\n \n \n";
        i ++;
        // if ()
        /*if ((time(0) - Start_Time > (60*Time - 2.5))){
            //std::cout << "YOOO" << std::endl;
            break;            
        }*/
    }
    //std::cout << " >>>>>> BESTSTATE 1 IS  >>>>>>>> \n";
    //std::cout << "Profit : " << BestState.Profit << std::endl;
    // int p = 0;
    // for (int i = 0 ; i < C ; i ++)
    // {
    //     int x = BestState.Bids_Company[i];
    //     if (x > -1 && x < B)
    //     {
    //         std::cout << BestState.Bids_Company[i] << " ";
    //         // p += allBids[x].Price;       
    //     }
    // }
    //std::cout << "#";
    // outfile << "\n Profit P1 : " << p << std::endl;
    
    //outfile << " >>>>>> BESTSTATE IS  >>>>>>>> \n";
    //std::cout << "Hill 1 ended" << std::endl;
}

#endif
