#include "structs.h"
#include "State_Manip.h"
#include "Hill1.h"
#include "Hill2.h"
#include "Hill3.h"
#include "Hill4.h"

// NOT NEEDED?
double Time;
int M,B,C;
// std::mutex MLock;

Types::Vec_of_Maps Company_Bids;
std::vector<Bid> allBids;
std::vector<Bid> Sorted_Bids;
std::ofstream outfile;
std::mt19937 rng;
int Avg_regions, Max_regions;
time_t Start_Time;
bool Over;
// approach 2 -> 1 company ki keep adding/swapping

int main(int argc, char const *argv[])
{
    Over = false;
    Start_Time = time(0);
    //take input file as argument
    std::string infile = argv[1];
    std::ifstream f_in;
    f_in.open(infile);

    outfile.open(argv[2]);
    //outfile << f_in.is_open() << std::endl;
    std::cout << infile << std::endl;
    Avg_regions = 0;
    Max_regions = 0;

    if (f_in.is_open())
    {
        f_in >> Time;
        f_in >> M >> B >> C;
        // outfile << M << " " <<  B << " " << C << std::endl;
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
        //std::cout << "Input parsed \n";
        std::sort(Sorted_Bids.begin(),Sorted_Bids.end());
        //outfile << getCompanyWithMostBids(Company_Bids,C) << '\n' ;
        Start = 0;

        std::vector<State> Start (4);
        for (int i = 0 ; i < 4 ; i ++)
            Start[i].Profit = 0;
        std::thread t1(Restart_Hill, std::ref(Start[0]));
        std::thread t2(Restart_Hill2, std::ref(Start[1]));
        std::thread t3(Restart_Hill3, std::ref(Start[2]));
        std::thread t4(Restart_Hill4, std::ref(Start[3]));

/*        t1.join();
        t2.join();
        t3.join();
        t4.join();*/

        while (time(0) - Start_Time < 60*Time - 2)
        {
            
        }
        Over = true;
/*        t1.~thread();
        t2.~thread();
        t3.~thread();
        t4.~thread();*/

        //time_t end_Time = time(0);
        //time_t taken = end_Time - Start_Time;
        // outfile << "Time taken : " << taken << std::endl;


        //get the values from each


        State bestestState = Start[0];
        for (int i = 1 ; i < 4; i ++)
        {
            if (bestestState.Profit < Start[i].Profit)
                bestestState = Start[i];
        }

        std::cout << bestestState.Profit << " : FINAL profit" << std::endl;
        //print the result
        for (int i = 0 ; i < C ; i ++){
            int k = bestestState.Bids_Company[i];
            if (k != -1){
                outfile << k << " ";
            }
        }
        outfile << "#" << std::endl;

        //happy debugging lols HEHE

        //Restart_Hill3();
        time_t taken3 = time(0) - Start_Time;
        std::cout << "Total Time taken : " << taken3 << std::endl;
        /*if (checkValidity(bestestState))
            std::cout << "YAYYYY!!";
        else
            std::cout << "KATTA!!";*/
        exit(0);
    }
    return 0;
}


