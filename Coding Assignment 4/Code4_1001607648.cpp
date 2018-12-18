// Kimberly Duffy – 1001607648
#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include "CokeMachine.h"
#include "CokeLib.h"
#include "VendingMachine.h"

using namespace std;

void get_command_line_params(int argc, char *argv[], string& inputFile, string& outputFile) {
    string INPUTFILENAME, OUTPUTFILENAME, cla;
    for (int i = 1; i < argc; i++) {
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
    map<string, int> receiptMap;
    CokeMachine MyCokeMachine("CSE 1325 Coke Machine", 50, 500, 100);
    
    try {
        get_command_line_params(argc, argv, INPUTFILENAME, OUTPUTFILENAME);
    } catch (invalid_argument& missingFileName) {
        cerr << "Missing command line parameters - - Usage : INPUTFILENAME= OUTPUTFILENAME=" << missingFileName.what() << endl;
        exit(1);
    }

    ifstream CokeInputFile{INPUTFILENAME};
    ofstream CokeOutputFile;

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
        
        int num = 0;

        for (auto i : SetOfCokeMachines)
            cout << ++num << ". " << i.getMachineName() << endl;

        cout << SetOfCokeMachines.size()+1 << ". Add a new machine" << endl << "Enter choice: ";
        cin >> choice1;

        if(choice1 == 0) {
            CokeOutputFile.open(OUTPUTFILENAME, ios::out);
            if(CokeOutputFile.is_open()) {
                for (int i = 0; i < SetOfCokeMachines.size(); i++) {
                    CokeOutputFile << CreateCokeOutputLine(SetOfCokeMachines[i]);
                }
            } else {
                cout << "File could not open for writing." << endl;
            }
            CokeOutputFile.close();
            
            cout << "Your Coke Receipt" << endl;
            for(auto it : receiptMap) {
                cout << it.first << ": " << it.second << endl;
            }

            exit(1);
        } else if (choice1 == 1+SetOfCokeMachines.size()) {
            CokeMachine();
            SetOfCokeMachines.push_back(CokeMachine());
            cout << "New machine added." << endl;
        } else if (choice1 >= 1 || choice1 <= 5) {
            do {
            cout << endl << "===== " << SetOfCokeMachines[choice1-1].getMachineName() << " =====" << endl << "0. Walk Away" << endl << "1. Buy a Coke" << endl << "2. Restock Machine" << endl << "3. Add change" << endl << "4. Display Machine Info" << endl << "Please make a selection: ";
            cin >> choice2;           
                switch(choice2) {
                    case 0:
                        cout << "Are you sure you aren't really THIRSTY and need a Coke?" << endl;
                        break;
                    case 1:
                        cout << "You have chosen to buy a coke." << endl << "Insert Payment: " << endl;
                        cin >> payment;
                        if(SetOfCokeMachines[choice1-1].buyACoke(payment, change, action)) {
                            if(action==ACTION(OK))
                            {
                                cout << endl << "Here's your Coke and change of " + SetOfCokeMachines[choice1-1].displayMoney(stoi(change)) + '.' << endl;
                            } else if (action==ACTION(EXACTCHANGE)) {
                                cout << endl << "Thank you for exact change." << endl << "Here's your Coke." << endl;
                            }

                            // Add to receiptMap
                            if (receiptMap.find(SetOfCokeMachines[choice1-1].getMachineName()) == receiptMap.end() ) {
                                receiptMap.insert(pair<string, int> ( SetOfCokeMachines[choice1-1].getMachineName(), 1));
                                //cout << "TEST" << receiptMap[SetOfCokeMachines[choice1-1].getMachineName()] << "TEST" << endl;
                            } else {
                                receiptMap[SetOfCokeMachines[choice1-1].getMachineName()]++;
                                //cout << "TEST" << receiptMap[SetOfCokeMachines[choice1-1].getMachineName()] << "TEST" << endl;
                            }
                            // End of receiptMap

                        } else {
                            if(action == ACTION(NOINVENTORY)){
                                cout << endl << "Sorry, we're all out of Coke!" << endl;
                            } else if (action == ACTION(NOCHANGE)) {
                                cout << endl << "Unable to give change at this time...returning your payment." << endl;
                            } else if (action == ACTION(INSUFFICIENTFUNDS)) {
                                cout << endl << "Insufficient payment...returning your payment." << endl;
                            }
                        }
                        break;
                    case 2: 
                        cout << "How much product are you adding to the machine? " << endl;
                        cin >> restock;
                        if(SetOfCokeMachines[choice1-1].getInventoryLevel() < SetOfCokeMachines[choice1-1].getMaxInventoryCapacity()) {
                            cout << "Your machine has been restocked." << endl;
                            SetOfCokeMachines[choice1-1].incrementInventory(restock);
                            cout << "Your inventory level is now " << to_string(SetOfCokeMachines[choice1-1].getInventoryLevel()) << "." << endl;
                            restock = 0;
                        } else {
                            cout << "You have exceded your machine's max capacity." << endl << "Your inventory level is now " << to_string(SetOfCokeMachines[choice1-1].getInventoryLevel()) << "." << endl;
                        }
                        break;
                    case 3:
                        cout << "How much change are you adding to the machine? " << endl;
                        cin >> changeIncrease;
                        if (SetOfCokeMachines[choice1-1].getChangeLevel() < SetOfCokeMachines[choice1-1].getMaxChangeCapacity()) {
                            SetOfCokeMachines[choice1-1].incrementChangeLevel(changeIncrease);
                            cout << "Your change level has been updated." << endl << "Your change level is now " << SetOfCokeMachines[choice1-1].getChangeLevel() << endl;
                            changeIncrease = 0;
                        } else {
                            cout << "You have exceeded your machine's max change capacity." << endl << "Your change level is now " << SetOfCokeMachines[choice1-1].getChangeLevel() << endl;
                        }
                        break;
                    case 4:
                        cout << SetOfCokeMachines[choice1-1];
                        break;
                    default:
                        cout << "Invalid entry. Try again." << endl;
                        break;
                }

            } while (choice2 != 0);
    }
    } while(choice1 != 0);

    return 0;
}

