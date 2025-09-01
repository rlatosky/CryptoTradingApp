#pragma once

#include "OrderBookEntry.h"
#include <map>
#include <iostream>
#include <ostream>

class Wallet {
    public:
        Wallet();
        /** Insert currency to the wallet */
        void insertCurrency(std::string type, double amount);
        /** Remove currency from the wallet */
        bool removeCurrency(std::string type, double amount);
        /** Check if the wallet contains this much currency or more */
        bool containsCurrency(std::string type, double amount);
        /** Checks if the walet can cope with this ask or bid */
        bool canFulfillOrder(OrderBookEntry order);
        /** Update the contents of the wallet
         *  assumes the order was made by the owner of the wallet
        */
        void processSale(OrderBookEntry& sale);

        /** Generate string representation of the wallet */
        std::string toString();
        friend std::ostream& operator<<(std::ostream& os, Wallet& wallet);
    private:
        std::map<std::string, double> currencies;

};
