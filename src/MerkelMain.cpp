#include "../include/MerkelMain.h"
#include "../include/CSVReader.h"
#include <iostream>
#include <ostream>
#include <vector>
#include <string>
#include <istream>
#include <limits>

/** Your main function should call this */
void MerkelMain::init() {
    int input;
    currentTime = orderBook.getEarliestTime();

    wallet.insertCurrency("BTC", 10);
    while (true) {
        printMenu();
        input = getUserOption();
        processUserOption(input);
    }
}

// void MerkelMain::setupMenu() {
//     menu[1] = printHelp;
//     menu[2] = printMarketStats;
//     menu[3] = enterAsk;
//     menu[4] = enterBid;
//     menu[5] = printWallet;
//     menu[6] = gotoNextTimeframe;
// }

void MerkelMain::printMenu() {
    std::cout << "1: Print help" << std::endl;
    std::cout << "2: Print exchange stats" << std::endl;
    std::cout << "3: Place an ask" << std::endl;
    std::cout << "4: Place a bid" << std::endl;
    std::cout << "5: Print wallet" << std::endl;
    std::cout << "6: Continue" << std::endl;
    std::cout << "=================" << std::endl;
    std::cout << "Current time is: " << currentTime << std::endl;
    std::cout << "Type in 1-6" << std::endl;
}

void MerkelMain::printHelp() {
    std::cout << "Help - choose options from the menu" << std::endl;
    std::cout << "and follow the on screen instructions." << std::endl;
}

void MerkelMain::printMarketStats() {

    for (std::string const& p : orderBook.getKnownProducts()) {
        std::cout << "Product: " << p << std::endl;
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, p, currentTime);
        std::cout << "Asks seen: " << entries.size() << std::endl;
        std::cout << "Max ask: " << OrderBook::getHighPrice(entries) << std::endl;
        std::cout << "Min ask: " << OrderBook::getLowPrice(entries) << std::endl;
    }
    // std::cout << "OrderBook contains: " << orders.size() << " entries" << std::endl;
    // unsigned int bids = 0;
    // unsigned int asks = 0;
    // for (OrderBookEntry& e : orders) {
    //     if (e.orderType == OrderBookType::ask)
    //         asks++;
    //     if (e.orderType == OrderBookType::bid)
    //         bids++;
    // }
    // std::cout << "OrderBook contains: " << asks << " asks" << std::endl;
    // std::cout << "OrderBook contains: " << bids << " asks" << std::endl;

}

void MerkelMain::enterOffer() {
}

void MerkelMain::enterAsk() {
    std::cout << "Make an ask - enter the amount: product, price, amount, eg ETH/BTC,200,0.5" << std::endl;
    std::string input;
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3) {
        std::cout << "Bad input! " << input << std::endl;
    } else {
        try {
            OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2],
                currentTime,
                tokens[0],
                OrderBookType::ask
            );
            obe.username = "simuser";
            if (wallet.canFulfillOrder(obe)) {
                std::cout << "Wallet looks good." << std::endl;
                orderBook.insertOrder(obe);
            } else {
                std::cout << "Wallet has insufficient funds." << std::endl;
            }
            orderBook.insertOrder(obe);
        } catch (const std::exception& e) {
            std::cout << "MerkelMain::enterAsk Bad input!" << std::endl;
        }
    }

    std::cout << "You typed:" << input << std::endl;
}

void MerkelMain::enterBid() {
    std::cout << "Make a bid - enter the amount: product, price, amount, eg ETH/BTC,200,0.5" << std::endl;
    std::string input;
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3) {
        std::cout << "Bad input! " << input << std::endl;
    } else {
        try {
            OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2],
                currentTime,
                tokens[0],
                OrderBookType::bid
            );
            obe.username = "simuser";
            if (wallet.canFulfillOrder(obe)) {
                std::cout << "Wallet looks good." << std::endl;
                orderBook.insertOrder(obe);
            } else {
                std::cout << "Wallet has insufficient funds." << std::endl;
            }
            orderBook.insertOrder(obe);
        } catch (const std::exception& e) {
            std::cout << "MerkelMain::enterBid Bad input!" << std::endl;
        }
    }

    std::cout << "You typed:" << input << std::endl;
}

void MerkelMain::printWallet() {
    std::cout << wallet.toString() << std::endl;
}

void MerkelMain::gotoNextTimeframe() {
    std::cout << "Going to the next timeframe..." << std::endl;
    for (std::string p : orderBook.getKnownProducts()) {
        std::cout << "Matching " << p << std::endl;
        std::vector<OrderBookEntry> sales = orderBook.matchAsksToBids(p, currentTime);
        std::cout << "Number of Sales: " << sales.size() << std::endl;
        for (OrderBookEntry& sale: sales) {
            std::cout << "Sale price: " << sale.price << " amount " << sale.amount << std::endl;
            if (sale.username == "simuser") {
                // Update the wallet
                wallet.processSale(sale);
            }
        }
    }
    currentTime = orderBook.getNextTime(currentTime);
}

void MerkelMain::printMarketMetrics() {
    for (std::string const& p : orderBook.getKnownProducts()) {
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, p, currentTime);
        std::cout << "Open price: " << OrderBook::getOpenPrice(entries, p) << " " << p << std::endl;
        std::cout << "Closing price: " << OrderBook::getClosingPrice(entries, p) << " " << p << std::endl;
    }
}

int MerkelMain::getUserOption() {
    int userOption;
    std::string line;

    std::getline(std::cin, line);

    try {
        userOption = std::stoi(line);
    } catch (const std::exception& e) {

    }

    return userOption;
}

void MerkelMain::processUserOption(int userOption) {
    if (userOption == 0)
    {
        std::cout << "Invalid choice. Choose 1-7" << std::endl;
    }
    if (userOption == 1)
    {
        printHelp();
    }
    if (userOption == 2)
    {
        printMarketStats();
    }
    if (userOption == 3)
    {
        enterAsk();
    }
    if (userOption == 4)
    {
        enterBid();
    }
    if (userOption == 5)
    {
        printWallet();
    }
    if (userOption == 6)
    {
        gotoNextTimeframe();
    }
    // if (userOption == 7)
    // {
    //     gotoNextTimeframe();
    // }
}
