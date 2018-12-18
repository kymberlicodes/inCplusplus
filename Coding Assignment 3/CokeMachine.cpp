// Kimberly Duffy – 1001607648
#include <iostream>
#include <cmath>
#include <sstream>
#include <string>
#include "CokeMachine.h"
#include "CokeLib.h"

using namespace std;

CokeMachine::CokeMachine(string name, int cost, int change, int inventory)
        : machineName(name), CokePrice(cost), changeLevel(change), inventoryLevel(inventory)
        {}

string CokeMachine::getMachineName() const
{
    return machineName;
}

bool CokeMachine::buyACoke(int payment, string &change, int &action)
{

    if (inventoryLevel == 0) {
    // NOINVENTORY machine doesn't have enough inventory
        action = 1;
    } else if ((payment - CokePrice) > changeLevel) {
    // NOCHANGE machine doesn't have enough change
        action = 2;
    } else if (payment < CokePrice) {
    // INSUFFICIENTFUNDS not enough money from user
        action = 3;
    } else if (payment == CokePrice) {
    // EXACTCHANGE user put in exact change
        action = 4;
        inventoryLevel--;
        changeLevel += CokePrice;
    } else {
    // OK customer had enough money, machine had enough inventory and change
        action = 0;
        inventoryLevel--;
        changeLevel = (changeLevel + (payment)) - (payment - CokePrice);
        change = to_string(payment - CokePrice);
    }

    return !(action%4);
}

int CokeMachine::getInventoryLevel() {
    return inventoryLevel;
}

int CokeMachine::getMaxInventoryCapacity() {
    return maxInventoryCapacity;
}

bool CokeMachine::incrementInventory(int amountToAdd) {
    if((amountToAdd + inventoryLevel) <= maxInventoryCapacity) {
        inventoryLevel = inventoryLevel + amountToAdd;
        return true;
    } else {
        return false;
    }
}

string CokeMachine::getChangeLevel() {
    return displayMoney(changeLevel);
}

bool CokeMachine::incrementChangeLevel(int amountToAdd) {
    if (amountToAdd + changeLevel <= maxChangeCapacity){
        changeLevel = changeLevel + amountToAdd;
        return true;
    } else {
        return false;
    }
}

string CokeMachine::getMaxChangeCapacity() {  
    return displayMoney(maxChangeCapacity);
}

string CokeMachine::getCokePrice() {
    return displayMoney(CokePrice);
}

string CokeMachine::displayMoney(int amount) {
    string amountReturn;
    string dollars{to_string(amount / 100)};

    string cents{to_string(abs(amount % 100))};
	
	amountReturn = "$" + dollars + "." + (cents.size() == 1 ? "0" : "") + cents;

    return amountReturn;
}

void CokeMachine::setMachineName(std::string newName) {
    machineName = newName;
}

void CokeMachine::setCokePrice(int newCost) {
    CokePrice = newCost;
}

string CreateCokeOutputLine(CokeMachine& readIn) {
    ostringstream newFile;
    newFile << readIn.machineName << "|" << readIn.CokePrice << "|" << readIn.changeLevel << "|" << readIn.inventoryLevel << endl;
    return newFile.str();
}

ostream& operator<<(ostream& output, const CokeMachine& DrinkMachine) {
    output << "\nYou have chosen to display machine info." << endl 
        << "\nCurrent Inventory Level:" << "\t" << DrinkMachine.inventoryLevel << endl
        << "Max Inventory Capacity:" << "\t\t" << DrinkMachine.maxInventoryCapacity << endl
        << "\nCurrent Change Level:" << "\t\t" << DrinkMachine.changeLevel << endl
        << "Max Change Capacity:" << "\t\t" << DrinkMachine.maxChangeCapacity << endl
        << "\nCurrent Coke Price:" << "\t\t" << DrinkMachine.CokePrice << endl;
        return output;
}

CokeMachine::~CokeMachine() {
    cout << getMachineName() << " has been destroyed." << endl;
}