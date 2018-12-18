// Kimberly Duffy – 1001607648
#include <iostream>
#include <cmath>
#include <sstream>
#include <string>
#include "VendingMachine.h"
#include "CokeLib.h"

using namespace std;

VendingMachine::VendingMachine(string name, int change)
        : machineName(name), changeLevel(change)
        { }

string VendingMachine::getMachineName() const
{
    
    return machineName;
}

void VendingMachine::setMachineName(std::string newName) {
    machineName = newName;
}

int VendingMachine::getChangeLevel() const {
    return changeLevel;
}

bool VendingMachine::incrementChangeLevel(int amountToAdd) {
    if (amountToAdd + changeLevel <= maxChangeCapacity) {
        changeLevel = changeLevel + amountToAdd;
        return true;
    } else {
        return false;
    }
}

int VendingMachine::getMaxChangeCapacity() const {  
    return maxChangeCapacity;
}

string VendingMachine::displayMoney(int amount) {
    string amountReturn;
    string dollars{to_string(amount / 100)};

    string cents{to_string(abs(amount % 100))};
	
	amountReturn = "$" + dollars + "." + (cents.size() == 1 ? "0" : "") + cents;

    return amountReturn;
}