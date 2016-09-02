#include "structs.h"

// NOT NEEDED?
typedef std::vector<std::set<Bid> > Vec_of_Maps;   // company to set of Bid IDs.
Vec_of_Maps Company_Bids;
std::vector<std::reference_wrapper<Bid> > allBids;
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
            clash_cost += (allBids[bid_state]).get().Price;
		}
	}
	return std::make_pair(clash_cost, bids_clashing);
}

void deleteState(std::unordered_set<int>bids,State &s){
    for (auto it = bids.begin(); it != bids.end(); it++){
        int bidId = *it;
        Bid b = (allBids[bidId]).get();
        for (auto it2 = b.Regions.begin(); it2 != b.Regions.end(); it2++){
            int region = *it2;
            s.Regions_assigned[region] = -1;
        }
        s.Bids_Company[b.Company] = -1;
    }
}

void deletandAdd(Bid &b, std::pair<int, std::unordered_set<int> > &clash, State &s){

    deleteState(clash.second,s);
    s.Bids_Company[b.Company] = b.Bid_Id;

    for (auto it = b.Regions.begin(); it != b.Regions.end(); it++){
        int region = *it;
        s.Regions_assigned[region] = b.Bid_Id;
    }
}

boolean addBidtoState(Bid b,State &s)
{
    // update State.
    std::pair<int,std::unordered_set<int> > clash = checkClashBidwithState(b,s);
    if (clash.second.size()==0){
        // if no clash, simply add to the state
        s.Bids_Company[b.Company] = b.Bid_Id;
        for (auto it = b.Regions.begin(); it != b.Regions.end(); it++){
            int region = *it;
            s.Regions_assigned[region] = b.Bid_Id;
        }
        return true;
    }
    else{
        //compare the costs of bid andclashing states
        if(clash.first < b.Price){
            //remove clashing states and add the new one
            deletandAdd(b,clash,s);
            return true;
        }
        else if(clash.first == b.Price){
            //randomly chose one
            double random = ((double) rand() / (RAND_MAX)) + 1 ;
            if (random >= 0.5){
                deletandAdd(b,clash,s);
                return true;
            }
            else{
                return false;
            }
        }
        else{
            //(clash.first > b.Price){
            //keep the original states
            return false;
        }
    }
}


State HillClimb(State &s, int i,int cnt, int C){
    // start state determined by var State
    bool chk = false;
    std::set<int> bidsofCompany = Company_Bids[i];
    for (auto it = bidsofCompany.begin(); it<bidsofCompany.end(); it++){
        Bid b = *it;
        chk = addBidtoState(b,s);
        if (chk)
        {
            break;
        }
    }
    if (cnt >= C){
        return s;
    }
    else{
        return HillClimb(s,(i+1)%C,cnt+1,C);
    }

}

int main(){

    //take input file as argument
    std::string infile = "/home/ankush/Desktop/COL 333 C++/Assignment_1_Local_Search/1.txt";
    std::ifstream f_in;
    f_in.open(infile);
    //std::cout << f_in.is_open();

    if (f_in.is_open()){

        f_in >> Time;
        int M,B,C;
        f_in >> M >> B >> C;
        std::cout << M << " " <<  B << " " << C << std::endl;
        //std::unordered_map<int, Bid> X;
        Company_Bids = std::vector<std::set<Bid> > (C);
//        allBids = std::vector<Bid& > ();
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
            Company_Bids[comp_i].insert(xi);
            allBids.push_back(xi);
            Sorted_Bids[i] = xi;
        }
        // all Bids parsed
        std::sort(Sorted_Bids.begin(),Sorted_Bids.end());
        //std::cout << getCompanyWithMostBids(Company_Bids,C) << '\n' ;
        Start = 0;
        std::cout << Sorted_Bids[0].Price;
        State Curr;
        Curr.Profit = 0;
//        while (Start < B)
//        {
//            State ith = HillClimb();
//            if (ith.Profit > Curr.Profit)
//                Curr = ith;
//            Start += 1;
//        }
    }
    return 0;
}


