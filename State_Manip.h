
#ifndef STATE_FUNC_H
#define STATE_FUNC_H

#include "structs.h"

Types::Price_Bids checkClashBidwithState(Bid b,State &s)
{
//    returns list of bids in state with which b clashes + total cost of clsshing bids.
	std::set<int> bid_regs = b.Regions;
	std::unordered_set<int> bids_clashing;
	int clash_cost = 0;
    std::unordered_set<int> regions_clash;
    int no_regs = 0;
	for (auto it = bid_regs.begin() ; it != bid_regs.end() ; it ++)
	{
		int reg = *it;
		int bid_state = s.Regions_assigned[reg];
		if (bid_state != -1 && bids_clashing.find(bid_state) == bids_clashing.end())
		{
			bids_clashing.insert(bid_state);
            // outfile << b.Bid_Id << " clashing with " << bid_state << std::endl;	
            clash_cost += allBids[bid_state].Price;
            Bid c = allBids[bid_state];
            for (auto it2 = c.Regions.begin() ; it2 != c.Regions.end() ; it2 ++)
            {
                if (regions_clash.find(*it2) == regions_clash.end())
                {
                    regions_clash.insert(*it2);
                    no_regs += 1;
                }
            }
		}
	}
    int comp_bid = s.Bids_Company[b.Company];
    if ( comp_bid < B && comp_bid > -1 && bids_clashing.find(comp_bid) == bids_clashing.end())
    {
        // std::cout << "Bid : " << comp_bid << std::endl;
        clash_cost += allBids[comp_bid].Price;
        // outfile << b.Bid_Id << " clashing with " << comp_bid << std::endl;
        bids_clashing.insert(comp_bid);
        std::set<int> c = allBids[comp_bid].Regions;
        for (auto it3 = c.begin() ; it3 != c.end() ; it3 ++)
        {
            if (regions_clash.find(*it3) == regions_clash.end())
            {
                no_regs += 1;
                regions_clash.insert(*it3);
            }
        }
    }
	return std::make_pair(no_regs, std::make_pair(clash_cost, bids_clashing));
}

void deleteState(std::unordered_set<int> bids,State &s){
    for (auto it = bids.begin(); it != bids.end(); it++)
    {
        int bidId = *it;
        Bid b = (allBids[bidId]);
        s.Profit -= b.Price;
        // outfile << "Deleting Bid " << b.Bid_Id << std::endl;
        for (auto it2 = b.Regions.begin(); it2 != b.Regions.end(); it2++){
            int region = *it2;
            s.Regions_assigned[region] = -1;
        }
        s.Bids_Company[b.Company] = -1;
    }
}

void deletandAdd(Bid b, Types::Price_Bids &clash, State &s){

    deleteState(clash.second.second,s);
    s.Bids_Company[b.Company] = b.Bid_Id;
    s.Profit += b.Price;
    for (auto it = b.Regions.begin(); it != b.Regions.end(); it++)
    {
        int region = *it;
        s.Regions_assigned[region] = b.Bid_Id;
    }
}

bool addBidtoState(Bid b,State &s, Types::Price_Bids &clash)
{
    // update State.
    // outfile << "Add called \n";
    if (clash.second.second.size()==0)
    {
        // if no clash, simply add to the state
        s.Bids_Company[b.Company] = b.Bid_Id;
        s.Profit += b.Price;
        for (auto it = b.Regions.begin(); it != b.Regions.end(); it++){
            int region = *it;
            s.Regions_assigned[region] = b.Bid_Id;
        }
        return true;
    }
    else{
        //compare the costs of bid andclashing states
        // WORKS GOOD ONLY IF EACH BID HAS LOTSSS OF REGIONS. -> check avg!!! TODO
        int regs_bid = b.Regions.size();
        if(clash.second.first < b.Price && regs_bid <= 1.5*clash.first) {
            //remove clashing states and add the new one
            deletandAdd(b,clash,s);
            return true;
        }
        else if(b.Price >= clash.first*0.9 && regs_bid <= 1.85*clash.first){ //multiplication factor
            //randomly chose one
            double random = ((double) rand() / (RAND_MAX));
            if (random >= 0.52) //probability factor
            {
                deletandAdd(b,clash,s);
                return true;
            }
            else
            {
                return false;
            }
        }
        else if (b.Price >= clash.first*0.8 && regs_bid <= 1.8*clash.first)
        {
            double random = ((double) rand() / (RAND_MAX)) ;
            if (random >= 0.6) //probability factor
            {
                deletandAdd(b,clash,s);
                return true;
            }
            else
            {
                return false;
            }  
        }
    }
}


#endif
