#ifndef HILL5_H
#define HILL5_H

#include "Hill4.h"
#include "structs.h"
#include "State_Manip.h"


State AddSwap(State & s, int i, int cnt)
{
	if (cnt >= C/10)
		return s;
	std::cout << cnt << std::endl;
	Bid b = Sorted_Bids[i];
	Types::Price_Bids clash = checkClashBidwithState(b, s);
	int max_profit = f(b,clash);
	int addthis = i;

	for (int count = 0 ; count < B/4 ; count ++)
	{
		Bid ith = Sorted_Bids[(i+count)%B];
		if (s.Bids_Company[ith.Company] != ith.Bid_Id)
		{
			Types::Price_Bids clash2 = checkClashBidwithState(ith,s);
			long f_ic = f(ith, clash);
			if (f_ic >= max_profit)
			{
				addthis = (i+count)%B;
				max_profit = f_ic;
				clash = clash2;
				b = ith;
			}
		}
	}
	// found the best:
	bool x = addBidtoState(b, s, clash, true);
	int count = 0;
	while (!x && count < 2)
		x = addBidtoState(b,s,clash,true);
	if (x)
	{
		return AddSwap(s, (i+B/4)%B , cnt + 1);
		std::cout<< "Yo \n";
	}
	else
		return s;
}

void Restart_Hill5(State & best)
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
        Curr2 = AddSwap(Curr2 , (i+1)%B, 1);
        // all those added which can be added.
        // std::cout << Curr2.Profit << std::endl;

        if (Curr2.Profit > best.Profit)
        {
            best = Curr2;
        }
        // if (checkValidity(best))
        //     std::cout << "ALL COOL! \n";
        std::cout << "Hill 5 :: " << Curr2.Profit << " Best yet of Hill5 : " << best.Profit << std::endl;
        if ((time(0) - Start_Time > (60*Time - 3))){
            break;
        }
        //outfile << "\n \n \n";
    }
    //outfile << " >>>>>> BESTSTATE IS  >>>>>>>> \n";
    std::cout << "BESTSTATE 5 Profit : " << best.Profit << std::endl;
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