#pragma once
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <string>
#include <vector>

class OrderBook {
    public:
        /** Construct, reading a csv data file */
        OrderBook(std::string filename);
        /** Return vector of all known products in the dataset */
        std::vector<std::string> getKnownProducts();
        /** Return vector of Orders according to the sent filters */
        std::vector<OrderBookEntry> getOrders(OrderBookType type,
                                                std::string product,
                                                std::string timestamp);

        /** returns the earliest time in the orderbook */
        std::string getEarliestTime();
        /** returns the next time after the sent time in the orderbook */
        std::string getNextTime(std::string timestamp);

        void insertOrder(OrderBookEntry& order);

        std::vector<OrderBookEntry> matchAsksToBids(std::string product, std::string timestamp);

        static double getHighPrice(std::vector<OrderBookEntry>& orders);
        static double getLowPrice(std::vector<OrderBookEntry>& orders);
        /** Get opening price for the timestamp */
        static double getOpenPrice(std::vector<OrderBookEntry>& orders, std::string product);
        /** Get closing price for the timestamp */
        static double getClosingPrice(std::vector<OrderBookEntry>& orders, std::string product);

    private:
        std::vector<OrderBookEntry> orders;
};
