#pragma once
#include <vector>
#include <map>
#include "OrderBook.h"
#include "OrderBookEntry.h"
#include "Wallet.h"

class MerkelMain
{
    public:
        MerkelMain() = default;
        /** Call this to start the sim */
        void init();
    private:
        void printMenu();
        void printHelp();
        void printMarketStats();
        void enterOffer();
        void enterAsk();
        void enterBid();
        void printWallet();
        void printMarketMetrics();
        void gotoNextTimeframe();
        int getUserOption();
        void processUserOption(int userOption);

        std::string currentTime;
        OrderBook orderBook{"resources/20200317.csv"};

        Wallet wallet;
};
