// Kimberly Duffy – 1001607648
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <gtkmm.h>
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

void cokeMenuDisplay() {
    cout << "0. Walk Away" << endl << "1. Buy a Coke" << endl << "2. Restock Machine" << endl << "3. Add change" << endl << "4. Display Machine Info" << endl << "5. Update Machine Name" << endl << "6. Update Coke Price" << endl << "Please make a selection: " << endl;
}

int main(int argc, char *argv[])
{
    Gtk::Main kit(argc, argv);
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
                cout << endl << "===== " << SetOfCokeMachines[choice1-1].getMachineName() << " =====" << endl;
                cokeMenuDisplay();
                // Create MyWindow
                Gtk::Dialog *MyWindow = new Gtk::Dialog();
                // Show the MyWindow
                MyWindow->set_title("CSE Coke Machine");
                Gtk::Label *MyLabel = Gtk::manage(new Gtk::Label("Please make a selection."));
                MyWindow->get_content_area()->pack_start(*MyLabel);
                MyLabel->show();
                std::vector<std::string> buttons = {"Walk Away", "Buy a Coke", "Restock", "Add Change", "Display Machine Info", "Update Machine Name", "Update Coke Price"};
                for (int i = 0; i < buttons.size(); i++) {
                        MyWindow->add_button(buttons[i], i);
                }
                MyWindow->set_default_response(1);
                int choice2 = MyWindow->run();
                MyWindow->close();
                delete MyWindow;
                switch(choice2) {
                    case 0:
                    {
                        cout << "Are you sure you aren't really THIRSTY and need a Coke?" << endl;
                        break;
                    }
                    case 1:
                    {
                        cout << "You have chosen to buy a coke." << endl << "Insert Payment: " << endl;
                        payment = SetOfCokeMachines[choice1-1].getPayment();
                        if(SetOfCokeMachines[choice1-1].buyACoke(payment, change, action)) {
                            if(action==ACTION(OK))
                            {
                                Gtk::MessageDialog *okDialog = new Gtk::MessageDialog{"Here's your Coke and change of " + SetOfCokeMachines[choice1-1].displayMoney(stoi(change)) + "."};
                                okDialog->set_title("Here is your Coke!");
                                int result = okDialog->run();
                                okDialog->close();
                                delete okDialog;
                            } else if (action==ACTION(EXACTCHANGE)) {
                                Gtk::MessageDialog *exactDialog = new Gtk::MessageDialog{"Thank you for exact change. Here's your Coke."};
                                exactDialog->set_title("Thank you!");
                                int result = exactDialog->run();
                                exactDialog->close();
                                delete exactDialog;
                            }
                            // Add to receiptMap
                            if (receiptMap.find(SetOfCokeMachines[choice1-1].getMachineName()) == receiptMap.end() ) {
                                receiptMap.insert(pair<string, int> ( SetOfCokeMachines[choice1-1].getMachineName(), 1));
                            } else {
                                receiptMap[SetOfCokeMachines[choice1-1].getMachineName()]++;
                            }
                            // End of receiptMap
                        } else {
                            if(action == ACTION(NOINVENTORY)){
                                Gtk::MessageDialog *outOfCokeDialog = new Gtk::MessageDialog{"We're all out of Coke!"};
                                outOfCokeDialog->set_title("Sorry");
                                int result = outOfCokeDialog->run();
                                outOfCokeDialog->close();
                                delete outOfCokeDialog;
                            } else if (action == ACTION(NOCHANGE)) {
                                Gtk::MessageDialog *noChangeDialog = new Gtk::MessageDialog{"Unable to give change at this time...returning your payment."};
                                noChangeDialog->set_title("Sorry");
                                int result = noChangeDialog->run();
                                noChangeDialog->close();
                                delete noChangeDialog;
                            } else if (action == ACTION(INSUFFICIENTFUNDS)) {
                                Gtk::MessageDialog *insufficientDialog = new Gtk::MessageDialog{"Insufficient payment...returning your payment."};
                                insufficientDialog->set_title("Insufficient Funds");
                                int result = insufficientDialog->run();
                                insufficientDialog->close();
                                delete insufficientDialog;
                            }
                        }
                        break;
                    }
                    case 2: 
                    {
                        cout << "How much product are you adding to the machine? " << endl;
                        restock = SetOfCokeMachines[choice1-1].restockAmount() + SetOfCokeMachines[choice1-1].getInventoryLevel();
                        if(restock < SetOfCokeMachines[choice1-1].getMaxInventoryCapacity()) {
                            Gtk::MessageDialog *restockedDialog = new Gtk::MessageDialog{"Your machine has been restocked. Your inventory level is now " + to_string(restock) + "."};
                            restockedDialog->set_title("Restocked");
                            int result = restockedDialog->run();
                            restockedDialog->close();
                            delete restockedDialog;
                            SetOfCokeMachines[choice1-1].incrementInventory(restock);
                            restock = 0;
                        } else {
                            Gtk::MessageDialog *restockedDialog = new Gtk::MessageDialog{"You have exceded your machine's max capacity. Your inventory level is currently " + to_string(SetOfCokeMachines[choice1-1].getInventoryLevel()) + "."};
                            restockedDialog->set_title("Cannot Restock");
                            int result = restockedDialog->run();
                            restockedDialog->close();
                            delete restockedDialog;
                        }
                        break;
                    }
                    case 3:
                    {
                        cout << "How much change are you adding to the machine? " << endl;
                        changeIncrease = SetOfCokeMachines[choice1-1].addChange() + SetOfCokeMachines[choice1-1].getChangeLevel();
                        if (changeIncrease < SetOfCokeMachines[choice1-1].getMaxChangeCapacity()) {
                            Gtk::MessageDialog *reloadedDialog = new Gtk::MessageDialog{"Your change level has been updated. Your change level is now " + to_string(changeIncrease) + "."};
                            reloadedDialog->set_title("Restocked");
                            int result = reloadedDialog->run();
                            reloadedDialog->close();
                            delete reloadedDialog;
                            SetOfCokeMachines[choice1-1].incrementChangeLevel(changeIncrease);
                            changeIncrease = 0;
                        } else {
                            Gtk::MessageDialog *reloadedDialog = new Gtk::MessageDialog{"You have exceeded your machine's max change capacity. Your change level is currently " + to_string(SetOfCokeMachines[choice1-1].getChangeLevel()) + "."};
                            reloadedDialog->set_title("Restocked");
                            int result = reloadedDialog->run();
                            reloadedDialog->close();
                            delete reloadedDialog;
                            cout << "You have exceeded your machine's max change capacity." << endl << "Your change level is now " << SetOfCokeMachines[choice1-1].getChangeLevel() << endl;
                        }
                        break;
                    }
                    case 4:
                    {
                        ostringstream machineInfo;
                        machineInfo << SetOfCokeMachines[choice1-1];
                        Gtk::MessageDialog *machineInfoDialog = new Gtk::MessageDialog{machineInfo.str()};
                        machineInfoDialog->set_title(SetOfCokeMachines[choice1-1].getMachineName());
                        int result = machineInfoDialog->run();
                        machineInfoDialog->close();
                        delete machineInfoDialog;
                        cout << SetOfCokeMachines[choice1-1];
                        break;
                    }
                    case 5:
                    {
                        string newMachineName;
                        cout << "Enter in a new name: " << endl;
                        cin.ignore();
                        getline(cin, newMachineName);
                        SetOfCokeMachines[choice1-1].setMachineName(newMachineName);
                        Gtk::MessageDialog *machineNameDialog = new Gtk::MessageDialog{"Your machine name has been updated to " + SetOfCokeMachines[choice1-1].getMachineName() + "."};
                        machineNameDialog->set_title("Machine Name Updated");
                        int result = machineNameDialog->run();
                        machineNameDialog->close();
                        delete machineNameDialog;
                        break;
                    }
                    case 6:
                    {
                        int newPrice;
                        cout << "Enter in a new Coke price: " << endl;
                        cin.ignore();
                        cin >> newPrice;
                        SetOfCokeMachines[choice1-1].setCokePrice(newPrice);
                        Gtk::MessageDialog *cokePriceDialog = new Gtk::MessageDialog{"Coke price was updated to " + SetOfCokeMachines[choice1-1].getCokePrice() + "."};
                        cokePriceDialog->set_title("Coke Price Updated");
                        int result = cokePriceDialog->run();
                        cokePriceDialog->close();
                        delete cokePriceDialog;
                        break;
                    }
                    default:
                    {
                        cout << "Invalid entry. Try again." << endl;
                        break;
                    }
                }
                if(choice2 == 0) {
                    break;
                }
            } while (choice2 != 0);
    }
    } while(choice1 != 0);

    return 0;
}
