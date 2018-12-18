// Kimberly Duffy – 1001607648
#ifndef VENDING_MACHINE_H
#define VENDING_MACHINE_H

class VendingMachine {
    public:
        // Methods
        VendingMachine(std::string name = "New Machine", int change = 500);
        std::string getMachineName() const;
        void setMachineName(std::string);
        int getChangeLevel() const;
        bool incrementChangeLevel(int);
        int getMaxChangeCapacity() const;
        std::string displayMoney(int);
        virtual bool incrementInventory(int) = 0;
        virtual int getMaxInventoryCapacity() = 0;
        virtual int getInventoryLevel() = 0;
        virtual ~VendingMachine () {};

    private:
        // Data Members
        std::string machineName;
        int changeLevel;
        int maxChangeCapacity{5000};
};

#endif