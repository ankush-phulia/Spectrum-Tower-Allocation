
#include "Structs.h"

// NOT NEEDED?
typedef std::vector<std::unordered_map<int, Bid> > Vec_of_Maps;
Vec_of_Maps Company_Bids;
double Time;

int main(int argc, char const *argv[])
{
	//take input file as argument
	std::string infile = argv[1];
	std::ifstream f_in;
	f_in.open(infile);

	if (f_in.is_open())
	{
		f_in >> Time;
		int M,B,C;
		f_in >> M >> B >> C;
		// std::cout << M << " " <<  B << " " << C << std::endl;
		std::unordered_map<int, Bid> X;
		Company_Bids = std::vector<std::unordered_map<int, Bid> > (C);
		for (int i = 0 ; i < B ; i ++)
		{
			// parse Bids
			Bid xi;							  //ith bid
			int comp_i = 0; 				 //company making the ith bid
			double price_i = 0.0;   		//price of ith bid
			std::ordered_set<int> regs;    //regions bid for
			std::string region = "";

			f_in >> comp_i;
			f_in >> price_i;

			xi.Bid_Id = i;
			xi.Price = price_i;

			f_in >> region;
			while (region != "#")
			{
				// parse Bids.
				// std::cout << region << " Region \n";
				regs.insert(atoi(region.c_str()));
				f_in >> region;
			}
			xi.Regions = regs;
			Company_Bids[comp_i][i] = xi;
		}
		// all Bids parsed.
	}
	return 0;
}


//UNTESTESTED BULLSHIT
int getCompanyWithMostBids(Vec_of_Maps Company_Bids, int C){
	int maxbids = 0;
	int maxcomp = 0;
	for (int i = 0;i<C;i++){
		int k = Vec_of_Maps[i].size();
		if (k>maxbids){
			maxbids = k;
			maxcomp = i;
		}
		else if (k==maxbids){
			double random = ((double) rand() / (RAND_MAX)) + 1 ;
			if (random>=0.5){
				maxcomp = i;
			}
		}
	}
	return maxcomp;
}

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

bool checkRegionClashBetweenBidAndState(Bid b,Regions r){
	//check clash between regions catered to by the current state and bids
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

