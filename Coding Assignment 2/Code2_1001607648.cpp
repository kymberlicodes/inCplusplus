// Kimberly Duffy – 1001607648
#include <iostream>
#include "CokeMachine.h"

using namespace std;

int main()
{
    int choice;
    int payment;
    int restock;
    int dollars;
    int cents;
    int inventoryAmt;
    int changeLvl;
    int changeIncrease;
    string change;
    int action;
    enum ACTION {OK, NOINVENTORY, NOCHANGE, INSUFFICIENTFUNDS, EXACTCHANGE};
    CokeMachine MyCokeMachine("CSE 1325 Coke Machine", 50, 500, 100);
    
    do {
    cout << "\n" << MyCokeMachine.getMachineName() << endl;
    cout << "\n0. Walk Away\n" << endl;
    cout << "1. Buy a Coke\n" << endl;
    cout << "2. Restock Machine\n" << endl;
    cout << "3. Add change\n" << endl;
    cout << "4. Display Machine Info\n" << endl;
    cout << "Please make a selection: ";
    cin >> choice;
    
        switch(choice) {
            case 0:
                cout << "\nAre you sure you aren't really THIRSTY and need a Coke?\n" << endl;
                exit(0);

                break;
            case 1:
                cout << "\nYou have chosen to buy a coke.\n" << endl;
                cout << "Insert Payment: " << endl;
                cin >> payment;
                change = to_string(payment - 50);
                if(MyCokeMachine.buyACoke(payment, change, action)) {
                    if(action==ACTION(OK))
                    {
                        cout << "\nHere's your Coke and change of " + MyCokeMachine.displayMoney(stoi(change)) + '.' << endl;
                    } else if (action==ACTION(EXACTCHANGE)) {
                        cout << "\nThank you for exact change." << endl;
                        cout << "Here's your Coke.\n" << endl;
                    }
                } else {
                    if(action == ACTION(NOINVENTORY)){
                        cout << "\nSorry, we're all out of Coke!\n" << endl;
                    } else if (action == ACTION(NOCHANGE)) {
                        cout << "\nUnable to give change at this time...returning your payment.\n" << endl;
                    } else if (action == ACTION(INSUFFICIENTFUNDS)) {
                        cout << "\nInsufficient payment...returning your payment.\n" << endl;
                    }
                }

                break;
            case 2: 
                cout << "How much product are you adding to the machine? " << endl;
                cin >> restock;
                if(MyCokeMachine.incrementInventory(restock)) {
                    cout << "\nYour machine has been restocked.\n" << endl;
                    MyCokeMachine.incrementInventory(restock);
                    cout << "\nYour inventory level is now " << to_string(MyCokeMachine.getInventoryLevel()) << ".\n" << endl;
                } else {
                    cout << "\nYou have exceded your machine's max capacity.\n" << endl;
                    cout << "\nYour inventory level is now " << to_string(MyCokeMachine.getInventoryLevel()) << ".\n" << endl;
                }

                break;
            case 3:
                cout << "\nHow much change are you adding to the machine? " << endl;
                cin >> changeIncrease;
                if (MyCokeMachine.incrementChangeLevel(changeIncrease)) {
                    cout << "\nYour change level has been updated." << endl;
                    cout << "\nYour change level is now " << MyCokeMachine.getChangeLevel() << endl;
                } else {
                    cout << "\nYou have exceeded your machine's max change capacity.\n" << endl;
                    cout << "\nYour change level is now " << MyCokeMachine.getChangeLevel() << endl;

                }

                break;
            case 4:
                cout << "\nYou have chosen to display machine info." << endl;
                cout << "\nCurrent Inventory Level:" << "\t" << MyCokeMachine.getInventoryLevel() << endl;
                cout << "Max Inventory Capacity:" << "\t\t" << MyCokeMachine.getMaxInventoryCapacity() << endl;
                cout << "\nCurrent Change Level:" << "\t\t" << MyCokeMachine.getChangeLevel() << endl;
                cout << "Max Change Capacity:" << "\t\t" << MyCokeMachine.getMaxChangeCapacity() << endl;
                cout << "\nCurrent Coke Price:" << "\t\t" << MyCokeMachine.getCokePrice() << endl;

                break;
            default:
                cout << "\nInvalid entry. Try again.\n" << endl;
                break;
        }
    } while (choice != 0);
    return 0;
}

