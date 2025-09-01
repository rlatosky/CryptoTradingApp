#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "../include/MerkelMain.h"
#include "../include/CSVReader.h"
#include "../include/Wallet.h"


int main() {
    MerkelMain app{};
    app.init();
    // Wallet myWallet{};
    // std::cout << "Inserting 10 BTC" << std::endl;
    // myWallet.insertCurrency("BTC", 10);
    // std::cout << "Wallet:"  << std::endl << myWallet << std::endl;
    // std::cout << "Inserting 1 ETH" << std::endl;
    // myWallet.insertCurrency("ETH", 1);
    // std::cout << "Wallet:"  << std::endl << myWallet << std::endl;
    // std::cout << "Inserting 5 BTC" << std::endl;
    // myWallet.insertCurrency("BTC", 5);
    // std::cout << "Wallet:"  << std::endl << myWallet << std::endl;

    // // std::cout << "Inserting -1 BTC (Bad input)" << std::endl;
    // // myWallet.insertCurrency("BTC", -1);

    // std::cout << "Removing 7 BTC - Return: " << myWallet.removeCurrency("BTC", 7) << std::endl;
    // std::cout << "Wallet:"  << std::endl << myWallet << std::endl;
    // std::cout << "Removing 10 BTC - Return: " << myWallet.removeCurrency("BTC", 10) << std::endl;
    // std::cout << "Wallet:"  << std::endl << myWallet << std::endl;
    // std::cout << "Removing 9 BTC - Return: " << myWallet.removeCurrency("BTC", 9) << std::endl;
    // std::cout << "Wallet:"  << std::endl << myWallet << std::endl;

    // std::cout << "Wallet contains at least 1 BTC - Return: " << myWallet.containsCurrency("BTC", 1) << std::endl;
    // std::cout << "Wallet contains at least 0.4 ETH - Return: " << myWallet.containsCurrency("ETH", 0.4) << std::endl;

    // std::cout << "Wallet contains at least 10 ETH - Return: " << myWallet.containsCurrency("ETH", 10) << std::endl;



    // myWallet.insertCurrency("BTC", 5);
    // myWallet.insertCurrency("USDT", 10000);
    // myWallet.removeCurrency("USDT", 1000);
    // std::cout << myWallet.toString() << std::endl;
}
