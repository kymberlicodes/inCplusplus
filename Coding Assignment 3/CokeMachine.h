// Kimberly Duffy – 1001607648
#ifndef COKE_MACHINE_H
#define COKE_MACHINE_H

class CokeMachine {
    public:
        // Methods
        CokeMachine(std::string = "New Machine", int = 50, int = 500, int = 100);
                  
        std::string getMachineName() const;

        bool buyACoke(int, std::string&, int&);

        int getInventoryLevel();

        int getMaxInventoryCapacity();

        bool incrementInventory(int);

        std::string getChangeLevel();

        bool incrementChangeLevel(int);

        std::string getMaxChangeCapacity();

        std::string getCokePrice();

        std::string displayMoney(int);

        void setMachineName(std::string);

        void setCokePrice(int);

        friend std::ostream& operator<<(std::ostream&, const CokeMachine&);

        friend std::string CreateCokeOutputLine(CokeMachine& readIn);

        ~CokeMachine();

    private:
        // Data Members
        std::string machineName;
        int changeLevel;
        int maxChangeCapacity{5000};
        int CokePrice;
        int inventoryLevel;
        int maxInventoryCapacity{100};
};

#endif