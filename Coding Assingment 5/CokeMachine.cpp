// Kimberly Duffy – 1001607648
#include <iostream>
#include <cmath>
#include <sstream>
#include <string>
#include "VendingMachine.h"
#include "CokeMachine.h"
#include "CokeLib.h"

using namespace std;

CokeMachine::CokeMachine(string name, int cost, int change, int inventory)
        : CokePrice(cost), inventoryLevel(inventory), VendingMachine(name, change)
        { }

bool CokeMachine::buyACoke(int payment, string &change, int &action)
{
    int makeChange;
    if (inventoryLevel == 0) {
    // NOINVENTORY machine doesn't have enough inventory
        action = 1;
    } else if ((payment - CokePrice) > getChangeLevel()) {
    // NOCHANGE machine doesn't have enough change
        action = 2;
    } else if (payment < CokePrice) {
    // INSUFFICIENTFUNDS not enough money from user
        action = 3;
    } else if (payment == CokePrice) {
    // EXACTCHANGE user put in exact change
        action = 4;
        inventoryLevel--;
        makeChange = getChangeLevel() + CokePrice;
    } else {
    // OK customer had enough money, machine had enough inventory and change
        action = 0;
        inventoryLevel--;
        makeChange = (getChangeLevel() +  (payment)) - (payment - CokePrice);
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

string CokeMachine::getCokePrice() {
    return displayMoney(CokePrice);
}

void CokeMachine::setCokePrice(int newCost) {
    CokePrice = newCost;
}

string CreateCokeOutputLine(CokeMachine& readIn) {
    ostringstream newFile;
    newFile << readIn.getMachineName() << "|" << readIn.CokePrice << "|" << readIn.getChangeLevel() << "|" << readIn.inventoryLevel << endl;
    return newFile.str();
}

int CokeMachine::getPayment() {
    int payment;
    cin >> payment;
    return payment;
}

int CokeMachine::restockAmount() {
    int amountToAdd;
    cin >> amountToAdd;
    return amountToAdd;
}

int CokeMachine::addChange() {
    int amountToAdd;
    cin >> amountToAdd;
    return amountToAdd;
}

ostream& operator<<(ostream& output, const CokeMachine& DrinkMachine) {
    output << endl << "You have chosen to display machine info of " << DrinkMachine.getMachineName() << ".\n" << endl 
        << "Current Inventory Level:" << "\t\t" << DrinkMachine.inventoryLevel << endl
        << "Max Inventory Capacity:" << "\t\t" << DrinkMachine.maxInventoryCapacity << endl
        << "Current Change Level:" << "\t\t" << DrinkMachine.getChangeLevel() << endl
        << "Max Change Capacity:" << "\t\t" << DrinkMachine.getMaxChangeCapacity() << endl
        << "Current Coke Price:" << "\t\t\t" << DrinkMachine.CokePrice << endl;
        return output;
}

CokeMachine::~CokeMachine() {
    // cout << getMachineName() << " has been destroyed." << endl;
}