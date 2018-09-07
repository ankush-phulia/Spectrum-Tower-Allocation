#ifndef HILL2_H
#define HILL2_H

#include "State_Manip.h"
#include "structs.h"

State HillClimb2(State &s, int i, int cnt, int passes, std::mt19937 &rng) {
    // start state determined by var State
    if (cnt > passes * B) {
        return s;
    } else {
        // if (cnt%B == 0)
        //     std::cout << cnt << " : cnt \n";

        double random = ((double)rand() / (RAND_MAX));
        if (random > (0.5)) {
            std::uniform_int_distribution<std::mt19937::result_type>
                randomBidGen(0, B - 1);
            int randomBidId = randomBidGen(rng);
            Bid bb = allBids[randomBidId];
            Types::Price_Bids cclash = checkClashBidwithState(bb, s);
            addBidtoState(bb, s, cclash, false);
        } else {
            Bid b = Sorted_Bids[i];
            Types::Price_Bids clash = checkClashBidwithState(b, s);
            bool chk2 = addBidtoState(b, s, clash, false);
        }
        // if (cnt%B == 0)
        //     std::cout << "YO" << s.Profit << std::endl;
        return HillClimb2(s, (i + 1) % B, cnt + 1, passes, rng);
    }
    // std::cout << "Pass 1 : Profit->" << s.Profit << std::endl;
}

void Restart_Hill2(State &best) {
    // MLock.lock();
    // RANDOM RESTART FOR NOOB LS:
    // State best;
    // best.Profit = 0;
    std::mt19937 rng;

    int i = 0;
    // int last = 0;
    while ((time(0) - Start_Time < 60 * Time - 2) && !Over) {
        // std::cout << "2: " << time(0) - Start_Time;
        // std::cout << " " << 60*Time - 3 << std::endl;
        State Curr2;
        Curr2.Profit = 0;
        Curr2.Bids_Company = std::vector<int>(C, -1);
        Curr2.Regions_assigned = std::vector<int>(M, -1);

        // random start state added
        rng.seed(std::random_device()());
        std::uniform_int_distribution<std::mt19937::result_type> randomBidGen(
            0, B - 1);
        int randomBidId = randomBidGen(rng) % B;
        Bid randomBid = allBids[randomBidId];
        std::unordered_set<int> empty_set;
        Types::Price_Bids empty_clash =
            std::make_pair(0, std::make_pair(0, empty_set));

        addBidtoState(randomBid, Curr2, empty_clash, true);

        randomBidId = randomBidGen(rng) % B;
        randomBid = allBids[randomBidId];
        Types::Price_Bids clash2 = checkClashBidwithState(randomBid, Curr2);
        while (clash2.second.second.size() != 0) {
            randomBidId = randomBidGen(rng) % B;
            randomBid = allBids[randomBidId];
            clash2 = checkClashBidwithState(randomBid, Curr2);
        }
        addBidtoState(randomBid, Curr2, clash2, false);

        int passes = 10;
        if ((B / C) >= 3 && 5 > (B / C)) {
            passes = 2 * (B / C) + 1 + 1;
        } else if ((B / C) <= 2) {
            passes = 3 * (B / C) + 3 + 1;
        } else {
            if (C >= 5) {
                passes = 7 + 1;
            } else {
                passes = 6 + 1;
            }
        }
        // outfile << "Start : " << randomBidId << std::endl;
        Curr2 = HillClimb2(Curr2, (i + 1) % B, 0, passes, rng);
        // std::cout << Curr2.Profit << std::endl;
        if (Curr2.Profit > best.Profit) {
            best = Curr2;
        }
        // std::cout << "Hill 2 :: " << Curr2.Profit << " Best yet of Hill2 : "
        // << best.Profit << std::endl;
        /*if (time(0)%60 ==0){
        }*/
        i++;
        /*if ((time(0) - Start_Time > (60*Time - 2.5))){
            break;
        }*/
        // outfile << "\n \n \n";
    }
    // outfile << " >>>>>> BESTSTATE IS  >>>>>>>> \n";
    std::cout << "BESTSTATE 3 Profit : " << best.Profit << std::endl;
    //    for (int i = 0 ; i < C ; i ++){
    //        int k = BestState.Bids_Company[i];
    //        if (k!=-1){
    //            outfile << k << " ";
    //        }
    //    }
    //    outfile << "#";
    // return BestState;
    // std::cout << "Hill 2 ended" << std::endl;
}

#endif
