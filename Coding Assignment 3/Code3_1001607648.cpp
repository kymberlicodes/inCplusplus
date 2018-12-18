// Kimberly Duffy – 1001607648
#include <iostream>
#include <vector>
#include <fstream>
#include "CokeMachine.h"
#include "CokeLib.h"

using namespace std;

void get_command_line_params(int argc, char *argv[], string& inputFile, string& outputFile) {
    string INPUTFILENAME, OUTPUTFILENAME, cla;
    for (int i = 1; i < argc; i++){
        cla = argv[i];

        if (cla.substr(0, cla.find("=")) == "INPUTFILENAME")
        {
            INPUTFILENAME = cla.substr(cla.find("=")+1, cla.length());
        } else if (cla.substr(0, cla.find("=")) == "OUTPUTFILENAME") {
            OUTPUTFILENAME = cla.substr(cla.find("=")+1, cla.length());
        } else {
            throw invalid_argument("Missing command line parameters - - Usage : INPUTFILENAME= OUTPUTFILENAME=");
        }
        inputFile = INPUTFILENAME;
        outputFile = OUTPUTFILENAME;
    }
}

int main(int argc, char *argv[])
{
    int choice1 = 20; // As a placeholder until the user updates this value
    int choice2 = 20; // As a placeholder until the user updates this value
    int payment, restock, dollars, cents, inventoryAmt, changeLvl, changeIncrease, action, cokePrice;
    string change, INPUTFILENAME, OUTPUTFILENAME, CokeMachineLine;
    vector<string> ConstructorValues(4);
    enum ACTION {OK, NOINVENTORY, NOCHANGE, INSUFFICIENTFUNDS, EXACTCHANGE};
    vector<CokeMachine> SetOfCokeMachines;
    CokeMachine MyCokeMachine("CSE 1325 Coke Machine", 50, 500, 100);
    
    try {
        get_command_line_params(argc, argv, INPUTFILENAME, OUTPUTFILENAME);
    } catch (invalid_argument& missingFileName) {
        cerr << "Missing command line parameters - - Usage : INPUTFILENAME= OUTPUTFILENAME=" << missingFileName.what() << endl;
        exit(1);
    }

    ifstream CokeInputFile{INPUTFILENAME};
    ofstream CokeOutputFile{OUTPUTFILENAME, ios::out};

    if(CokeInputFile.is_open()) {
        while(getline(CokeInputFile, CokeMachineLine)) {
            if(ParseCokeLine(CokeMachineLine, ConstructorValues)) {
                CokeMachine tempCokeMachine(ConstructorValues[0], stoi(ConstructorValues[1]), stoi(ConstructorValues[2]), stoi(ConstructorValues[3]));
                SetOfCokeMachines.push_back(tempCokeMachine);
            } else {
                cout << "Unable to open file." ;
                exit(1);
            }
        }
    } else {
        cout << "Unable to open file";
        exit(1);
    }
    
    do {
        cout << endl << "===== Pick a Coke Machine =====" << endl << "0. Exit" << endl;
        for(int j = 0; j < SetOfCokeMachines.size(); j++) {
            cout << j+1 << ". " << SetOfCokeMachines[j].getMachineName() << endl;    
        }
        cout << SetOfCokeMachines.size()+1 << ". Add a new machine" << endl << "Enter choice: ";
        cin >> choice1;

        if(choice1 == 0) {
            if(CokeOutputFile.is_open()) {
                for (int i = 0; i < SetOfCokeMachines.size(); i++) {
                    CokeOutputFile << CreateCokeOutputLine(SetOfCokeMachines[i]);
                }
            } else {
                cout << "File could not open for writing." << endl;
            }
            CokeOutputFile.close();
            exit(1);
        } else if (choice1 == 1+SetOfCokeMachines.size()) {
            CokeMachine();
            SetOfCokeMachines.push_back(CokeMachine());
            cout << "New machine added." << endl;
        } else if (choice1 >= 1 || choice1 <= 5) {
            do {
            cout << "\n" << SetOfCokeMachines[choice1-1].getMachineName() << endl;
            cout << "\n0. Walk Away\n" << endl;
            cout << "1. Buy a Coke\n" << endl;
            cout << "2. Restock Machine\n" << endl;
            cout << "3. Add change\n" << endl;
            cout << "4. Display Machine Info\n" << endl;
            cout << "Please make a selection: ";
            cin >> choice2;
            
                switch(choice2) {
                    case 0:
                        cout << "\nAre you sure you aren't really THIRSTY and need a Coke?\n" << endl;
                        break;
                    case 1:
                        cout << "\nYou have chosen to buy a coke.\n" << endl << "Insert Payment: " << endl;
                        //cin.clear();
                        //getline(cin, payment);
                        cin >> payment;
                        //payment = 400;
                        //change = to_string(payment - 50);
                        if(MyCokeMachine.buyACoke(payment, change, action)) {
                            if(action==ACTION(OK))
                            {
                                cout << "\nHere's your Coke and change of " + MyCokeMachine.displayMoney(stoi(change)) + '.' << endl;
                            } else if (action==ACTION(EXACTCHANGE)) {
                                cout << "\nThank you for exact change." << endl << "Here's your Coke.\n" << endl;
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
                            cout << "\nYou have exceded your machine's max capacity.\n" << endl << "\nYour inventory level is now " << to_string(MyCokeMachine.getInventoryLevel()) << ".\n" << endl;
                        }
                        break;
                    case 3:
                        cout << "\nHow much change are you adding to the machine? " << endl;
                        cin >> changeIncrease;
                        if (MyCokeMachine.incrementChangeLevel(changeIncrease)) {
                            cout << "\nYour change level has been updated." << endl << "\nYour change level is now " << MyCokeMachine.getChangeLevel() << endl;
                        } else {
                            cout << "\nYou have exceeded your machine's max change capacity.\n" << endl << "\nYour change level is now " << MyCokeMachine.getChangeLevel() << endl;
                        }
                        break;
                    case 4:
                        //cout << "\nYou have chosen to display machine info." << endl
                        //     << "\nCurrent Inventory Level:" << "\t" << MyCokeMachine.getInventoryLevel() << endl
                        //     << "Max Inventory Capacity:" << "\t\t" << MyCokeMachine.getMaxInventoryCapacity() << endl
                        //     << "\nCurrent Change Level:" << "\t\t" << MyCokeMachine.getChangeLevel() << endl
                        //     << "Max Change Capacity:" << "\t\t" << MyCokeMachine.getMaxChangeCapacity() << endl
                        //     << "\nCurrent Coke Price:" << "\t\t" << MyCokeMachine.getCokePrice() << endl;
                        cout << SetOfCokeMachines[choice1-1];
                        break;
                    default:
                        cout << "\nInvalid entry. Try again.\n" << endl;
                        break;
                }

            } while (choice2 != 0);
    }
    } while(choice1 != 0);
    
    return 0;
}

