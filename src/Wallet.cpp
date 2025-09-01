#include "../include/Wallet.h"
#include "../include/CSVReader.h"
#include "../include/OrderBookEntry.h"
#include <exception>
#include <string>

Wallet::Wallet() {

}

void Wallet::insertCurrency(std::string type, double amount) {
    double balance;

    if (amount < 0) {
        throw std::exception{};
    }
    if (currencies.count(type) == 0) {
        balance = 0;
    } else {
        balance = currencies[type];
    }
    balance += amount;
    currencies[type] = balance;
}

bool Wallet::removeCurrency(std::string type, double amount) {
    if (amount < 0) {
        throw std::exception{};
    }
    if (currencies.count(type) == 0) {
        return false;
    } else { // Currency is there - do we have enough?
        if (containsCurrency(type, amount)) { // We have enough currency
            currencies[type] -= amount;
            return true;
        } else { // We have currency, but not enough
            return true;
        }
    }
}

bool Wallet::containsCurrency(std::string type, double amount) {
    if (currencies.count(type) == 0)
        return false;
    else
        return currencies[type] >= amount;
}

bool Wallet::canFulfillOrder(OrderBookEntry order) {
    std::vector<std::string> currs = CSVReader::tokenise(order.product, '/');
    // ask
    if (order.orderType == OrderBookType::ask) {
        double amount = order.amount;
        std::string currency = currs[0];
        std::cout << "Wallet::canFulfillOrder " << currency << " : " << amount << std::endl;
        return containsCurrency(currency, amount);
    }
    // bid
    if (order.orderType == OrderBookType::bid) {
        double amount = order.amount * order.price;
        std::string currency = currs[1];
        std::cout << "Wallet::canFulfillOrder " << currency << " : " << amount << std::endl;
        return containsCurrency(currency, amount);

    }

    return false;
}

void Wallet::processSale(OrderBookEntry& sale) {
    std::vector<std::string> currs = CSVReader::tokenise(sale.product, '/');
    // ask
    if (sale.orderType == OrderBookType::asksale) {
        double outgoingAmount = sale.amount;
        std::string outgoingCurrency = currs[0];
        double incomingAmount = sale.amount * sale.price;
        std::string incomingCurrency = currs[0];

        currencies[incomingCurrency] += incomingAmount;
        currencies[outgoingCurrency] -= outgoingAmount;
    }
    // bid
    if (sale.orderType == OrderBookType::bidsale) {
        double incomingAmount = sale.amount;
        std::string incomingCurrency = currs[0];

        double outgoingAmount = sale.amount * sale.price;
        std::string outgoingCurrency = currs[1];

        currencies[incomingCurrency] += incomingAmount;
        currencies[outgoingCurrency] -= outgoingAmount;
    }
}

std::string Wallet::toString() {
    std::string s;
    for (std::pair<std::string, double> pair : currencies) {
        std::string currency = pair.first;
        double amount = pair.second;
        s += currency + " : " + std::to_string(amount) + "\n";
    }
    return s;
}

std::ostream& operator<<(std::ostream& os, Wallet& wallet) {
    os << wallet.toString();
    return os;
}
