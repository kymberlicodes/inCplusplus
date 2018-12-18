// Kimberly Duffy – 1001607648
#include <cmath>
#include <string>


class CokeMachine {
    public:
        // Methods  
        CokeMachine(std::string name, int cost, int change, int inventory)
        : machineName(name), CokePrice(cost), changeLevel(change), inventoryLevel(inventory)
        {}
        
        std::string getMachineName()
        {
            return machineName;
        };

        bool buyACoke(int payment, std::string change, int &action)
        {

            if (inventoryLevel == 0) {
                // NOINVENTORY machine doesn't have enough inventory
                action = 1;
            } else if (stoi(change) > changeLevel) {
                // NOCHANGE machine doesn't have enough change
                action = 2;
            } else if (payment < CokePrice) {
                // INSUFFICIENTFUNDS not enough money from user
                action = 3;
            } else if (payment == 50) {
                // EXACTCHANGE user put in exact change
                action = 4;
                inventoryLevel--;
                changeLevel += 50;
            } else {
                // OK customer had enough money, machine had enough inventory and change
                action = 0;
                inventoryLevel--;
                changeLevel = (changeLevel + (payment)) - (payment - 50);
                change = payment - 50;
            }

            return !(action%4);
        };

        int getInventoryLevel() {
            return inventoryLevel;
        };

        int getMaxInventoryCapacity() {
            return maxInventoryCapacity;
        };

        bool incrementInventory(int amountToAdd) {
            if((amountToAdd + inventoryLevel) <= maxInventoryCapacity) {
                inventoryLevel = inventoryLevel + amountToAdd;
                return true;
            } else {
                return false;
            }

        };

        std::string getChangeLevel() {
            return displayMoney(changeLevel);
        }

        bool incrementChangeLevel(int amountToAdd){
            if (amountToAdd + changeLevel <= maxChangeCapacity){
                changeLevel = changeLevel + amountToAdd;
                return true;
            } else {
                return false;
            }
        }

        std::string getMaxChangeCapacity() {  
            return displayMoney(maxChangeCapacity);
        };

        std::string getCokePrice() {
            return displayMoney(CokePrice);
        };

        std::string displayMoney(int amount) {
            std::string amountReturn;
            std::string dollars{std::to_string(amount / 100)};

	        std::string cents{std::to_string(abs(amount % 100))};
	
	        amountReturn = "$" + dollars + "." + (cents.size() == 1 ? "0" : "") + cents;

            return amountReturn;
        };

    private:
        // Data Members
        std::string machineName;
        int changeLevel;
        int maxChangeCapacity{5000};
        int CokePrice;
        int inventoryLevel;
        int maxInventoryCapacity{100};
};

