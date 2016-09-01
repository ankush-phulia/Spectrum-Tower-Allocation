#include "structs.h"

// NOT NEEDED?
typedef std::vector<std::set<int> > Vec_of_Maps;   // company to set of Bid IDs.
Vec_of_Maps Company_Bids;
std::vector<Bid> allBids;
std::vector<Bid> Sorted_Bids;
int Start;
double Time;



//int getCompanyWithMostBids(Vec_of_Maps Company_Bids, int C){
//    int maxbids = 0;
//    int maxcomp = 0;
//    for (int i = 0;i<C;i++){
//        int k = Company_Bids[i].size();
//        if (k>maxbids){
//            maxbids = k;
//            maxcomp = i;
//        }
//        else if (k==maxbids){
//            double random = ((double) rand() / (RAND_MAX)) + 1 ;
//            if (random>=0.5){
//                maxcomp = i;
//            }
//        }
//    }
//    return maxcomp;
//}

// global sorted array of bids.



std::pair<int,std::unordered_set<int> >  checkClashBidwithState(Bid b,State &s)
{
//    returns list of bids in state with which b clashes + total cost of clsshing bids.
	std::set<int> bid_regs = b.Regions;
	std::unordered_set<int> bids_clashing;
	int clash_cost = 0;
	for (auto it = bid_regs.begin() ; it != bid_regs.end() ; it ++)
	{
		int reg = *it;
		int bid_state = s.Regions_assigned[reg];
		if (bid_state != -1 && bids_clashing.find(bid_state) == bids_clashing.end())
		{
			bids_clashing.insert(bid_state);
			clash_cost += allBids[bid_state].Price;			
		}
	}
	return std::make_pair(clash_cost, bids_clashing);
}


void addBidtoState(Bid b,State &s)
{
    // update State. TODO : ANKUSH
}


State HillClimb()
{
    // start state determined by var State
}

int main(){

    //take input file as argument
    std::string infile = "/home/ankush/Desktop/COL 333 C++/Assignment_1_Local_Search/1.txt";
    std::ifstream f_in;
    f_in.open(infile);
    std::cout << f_in.is_open();

    if (f_in.is_open()){

        f_in >> Time;
        int M,B,C;
        f_in >> M >> B >> C;
        std::cout << M << " " <<  B << " " << C << std::endl;
        //std::unordered_map<int, Bid> X;
        Company_Bids = std::vector<std::set<int> > (C);
        allBids = std::vector<Bid> (B);
        Sorted_Bids = std::vector<Bid> (B);

        for (int i = 0 ; i < B ; i ++){

            // parse Bids
            Bid xi;							  //ith bid
            int comp_i = 0; 				 //company making the ith bid
            double price_i = 0.0;   		//price of ith bid
            std::set<int> regs;            //regions bid for
            std::string region = "";

            f_in >> comp_i;
            f_in >> price_i;

            xi.Bid_Id = i;
            xi.Price = price_i;

            f_in >> region;
            while (region != "#"){
                // parse Bids.
                //std::cout << region << " Region \n";
                regs.insert(atoi(region.c_str()));
                f_in >> region;
            }
            xi.Regions = regs;
            Company_Bids[comp_i].insert(i);
            allBids[i] = xi;
            Sorted_Bids[i] = xi;
        }
        // all Bids parsed
        std::sort(Sorted_Bids.begin(),Sorted_Bids.end());
        //std::cout << getCompanyWithMostBids(Company_Bids,C) << '\n' ;
        Start = 0;
        std::cout << Sorted_Bids[0].Price;
        State Curr;
        Curr.Profit = 0;
        while (Start < B)
        {
            State ith = HillClimb();
            if (ith.Profit > Curr.Profit)
                Curr = ith;
            Start += 1;
        }
    }
    return 0;
}



/*
//UNOPTIMISED BULLSHIT
int checkRegionClashBetweenBids(Bid b1, Bid b2){

    int r1 = b1.Regions.size();
    int r2 = b2.Regions.size();

    //whether any region in b2 is already present in b1, take intersection
    std::vector<int> regIntersection(r1+r2);
    std::vector<int>::iterator it;
    it=std::set_intersection (b1.Regions, b1.Regions+r1, b1.Regions, b1.Regions+r2, regIntersection.begin());

    regIntersection.resize(it-regIntersection.begin());

    if (regIntersection.size()==0){
        //0 conflicts
        return 2;
    }
    else if (b1.Price>b2.Price){
        return 0;
    }
    else if (b2.Price>b1.Price){
        return 1;
    }
    else{
        int random = (int)(10*(((double) rand() / (RAND_MAX)) + 1)) ;
        return random % 2;
    }
}

//GENERATE START STATE WITH BULLSHIT ---INCOMPLETE
State genStartState(Vec_of_Maps CompanyBids, int C){
    State startState;
    //get company with most bids
    int firstComp = getCompanyWithMostBids(CompanyBids, C);

    //pick random bid from its bids
    int random = ;
    Bid b = CompanyBids[firstComp][random];

    //add this bid to the state
    startState.Company_Bid.add(b);

    //add the regions catered to by this bid


    //now loop over all other companies
    int i = 0;
    while (i<C){
        if (i!=firstComp){
            //try to add the bids without conflicts with values in non-decreasing order
            // we will need a list of all regions catered to by the current state and a function to check clash like the one between bids
            // State.Regions is a map Region no->bid no is it?
        }
    }

}
*/
//

