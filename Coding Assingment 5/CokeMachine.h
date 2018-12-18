// Kimberly Duffy – 1001607648
#ifndef COKE_MACHINE_H
#define COKE_MACHINE_H

#include "VendingMachine.h"

class CokeMachine : public VendingMachine {
    public:
        // Methods
        CokeMachine(std::string name = "New Machine", int cost = 50, int change = 500, int inventory = 100);
        bool buyACoke(int, std::string&, int&);
        int getInventoryLevel();
        int getMaxInventoryCapacity();
        bool incrementInventory(int);
        std::string getCokePrice();
        void setCokePrice(int);
        friend std::ostream& operator<<(std::ostream&, const CokeMachine&);
        friend std::string CreateCokeOutputLine(CokeMachine& readIn);
        int getPayment();
        int restockAmount();
        int addChange();
        ~CokeMachine();

    private:
        // Data Members
        int CokePrice;
        int inventoryLevel;
        int maxInventoryCapacity{100};
};

#endif