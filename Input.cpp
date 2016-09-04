#include "structs.h"
#include "State_Manip.h"
#include "Hill1.h"
#include "Hill3.h"

// NOT NEEDED?
double Time;
int M,B,C;

Types::Vec_of_Maps Company_Bids;
std::vector<Bid> allBids;
std::vector<Bid> Sorted_Bids;
std::ofstream outfile;
std::mt19937 rng;
int Avg_regions, Max_regions;
time_t Start_Time;
// approach 2 -> 1 company ki keep adding/swapping

int main()
{

    Start_Time = time(0);
    //take input file as argument
    std::string infile = "/home/ankush/Desktop/COL 333 C++/Assignment_1_Local_Search/16.txt";
    std::ifstream f_in;
    f_in.open(infile);

    outfile.open("/home/ankush/Desktop/COL 333 C++/output.txt");
    //outfile << f_in.is_open() << std::endl;
    Avg_regions = 0 ;
    Max_regions = 0 ;

    if (f_in.is_open())
    {
        f_in >> Time;
        f_in >> M >> B >> C;
        std::cout << M << " " <<  B << " " << C << std::endl;
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

        //outfile << Curr.Profit << std::endl;
//        while (Start < B)
//        {
//            State ith = HillClimb();
//            if (ith.Profit > Curr.Profit)
//                Curr = ith;
//            Start += 1;
//        }
//        Restart_Hill();
//        time_t end_Time = time(0);
//        time_t taken = end_Time - start_Time;
//        outfile << "Time taken : " << taken << std::endl;

        std::future<State> parallel_process[4];
        //Launch a group of processes
        for (int i = 0; i < 4; i++) {
            //call restart hill in each
            //SOME ERROR OVER HERE
            parallel_process[i] = std::async(std::launch::async, Restart_Hill3);;
        }

        //get the values from each
        State BestStates[4];
        for (int i = 0; i < 4; i++){
            BestStates[i] = parallel_process[i].get();
        }

//        //join all of them
//        for (int i = 0; i < 4; i++) {
//            parallel_process[i].join();
//        }

        //choose best out of them
        State bestestState = BestStates[0];
        for (int i = 1;i<4;i++){
            if (BestStates[i].Profit>bestestState.Profit){
                bestestState = BestStates[i];
            }
        }

        std::cout << bestestState.Profit << std::endl;
        //print the result
        for (int i = 0 ; i < C ; i ++){
            int k = bestestState.Bids_Company[i];
            if (k!=-1){
                outfile << k << " ";
            }
        }
        outfile << "#";

        //happy debugging lols

        //Restart_Hill3();
        time_t taken3 = time(0) - Start_Time;
        std::cout << "Time taken : " << taken3 << std::endl;
    }
    return 0;
}


