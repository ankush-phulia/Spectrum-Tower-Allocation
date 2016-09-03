#include "structs.h"
#include "State_Manip.h"
#include "Hill1.h"
#include "Hill2.h"
#include "Hill3.h"

// NOT NEEDED?
double Time;
int M,B,C;

Types::Vec_of_Maps Company_Bids;
std::vector<Bid> allBids;
std::vector<Bid> Sorted_Bids;
std::ofstream outfile;
// approach 2 -> 1 company ki keep adding/swapping

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



int main()
{

    //take input file as argument
    std::string infile = "4.txt";
    std::ifstream f_in;
    f_in.open(infile);

    outfile.open("HRandom_4.txt");
    outfile << f_in.is_open() << std::endl;

    if (f_in.is_open())
    {

        f_in >> Time;
        f_in >> M >> B >> C;
        outfile << M << " " <<  B << " " << C << std::endl;
        //std::unordered_map<int, Bid> X;
        Company_Bids = std::vector<std::set<Bid> > (C);
        allBids = std::vector<Bid> (B);
        Sorted_Bids = std::vector<Bid> (B);

        State Curr;
        Curr.Regions_assigned = std::vector<int> (M,-1);
        Curr.Bids_Company = std::vector<int> (C,-1);
        Curr.Profit = 0;


        for (int i = 0 ; i < B ; i ++){

            // parse Bids
            Bid xi;							  //ith bid
            int comp_i = 0; 				 //company making the ith bid
            double price_i = 0.0;   		//price of ith bid
            std::set<int> regs;            //regions bid for
            std::string region = "";

            f_in >> comp_i;
            // outfile << comp_i << " Company ID, ";
            f_in >> price_i;

            xi.Bid_Id = i;
            xi.Company = comp_i;
            xi.Price = price_i;

            f_in >> region;
            while (region != "#"){
                // parse Bids.
                //outfile << region << " Region \n";
                regs.insert(atoi(region.c_str()));
                f_in >> region;
            }
            xi.Regions = regs;
            Company_Bids[comp_i].insert(xi);
            // Bid_Wrap bdwi (xi);
            allBids[i] = xi;
            // outfile << allBids[i].get().Price << " Added \n";
            Sorted_Bids[i] = xi;

            // outfile << "Step " << i << std::endl;
            // Bid ith = allBids[i].get();
            // outfile << ith.Company << " Company, " << ith.Price << " price of ith bid " << i << std::endl;
            // addBidtoState((Bid)ith, Curr);

            // outfile << Curr.Profit << " Cost after Step " << i << " over! \n";

        }
        // all Bids parsed
        // outfile << "Input parsed \n";
        std::sort(Sorted_Bids.begin(),Sorted_Bids.end());
        //outfile << getCompanyWithMostBids(Company_Bids,C) << '\n' ;
        Start = 0;
        // outfile << Sorted_Bids[0].Price;
        // ABSOLUTE NOOB:
        // for (int i = 0 ; i < B ; i ++)
        // {
        //     outfile << "Step " << i << std::endl;
        //     Bid ith = allBids[i];
        //     // outfile << ith.Company << " Company, " << ith.Price << " price of ith bid " << i << std::endl;
        //     Price_Bids clash = checkClashBidwithState(ith, Curr);
        //     addBidtoState((Bid)ith, Curr, clash);
        //     // addBidtoState((Bid)(allBids[i].get()), Curr);            
        //     // for (int i = 0 ; i < C  ; i ++)
        //     // {
        //     //     // if (Curr.Bids_Company[i] != -1)
        //     //         outfile << Curr.Bids_Company[i] << " Bid, ";
        //     // }
        //     outfile << Curr.Profit << " Cost after Step " << i << " over! \n";
        //     // outfile << "Step " << i ;
        // }
        outfile << Curr.Profit << std::endl;
//        while (Start < B)
//        {
//            State ith = HillClimb();
//            if (ith.Profit > Curr.Profit)
//                Curr = ith;
//            Start += 1;
//        }
        Restart_Hill();

    }
    return 0;
}


