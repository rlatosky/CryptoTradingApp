#pragma once
#include <iostream>
#include <vector>

enum class OrderBookType{ask, bid, unknown, asksale, bidsale};

class OrderBookEntry {
    public:
        double price;
        double amount;
        std::string timestamp;
        std::string product;
        OrderBookType orderType;
        std::string username;

        OrderBookEntry(
            double price,
            double amount,
            std::string timestamp,
            std::string product,
            OrderBookType orderType,
            std::string username = "dataset"
        );

        static OrderBookType stringToOrderBookType(std::string);
        static bool compareByTimestamp(OrderBookEntry& e1, OrderBookEntry& e2)
        {
            return e1.timestamp < e2.timestamp;
        }
        static bool compareByPriceAsc(OrderBookEntry& e1, OrderBookEntry& e2)
        {
            return e1.price < e2.price;
        }
        static bool compareByPriceDesc(OrderBookEntry& e1, OrderBookEntry& e2)
        {
            return e1.price > e2.price;
        }

};
