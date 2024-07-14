#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <iomanip>
using namespace std;

// Computer Rental System

struct PlayerAccount {
    string name;
    string password;
    string filePath;
    float credits = 0.0;
    int totalHours = 0;
    int remainingHours = 0;
    PlayerAccount* next = nullptr; // Initialize next to nullptr
};

// Function declarations
PlayerAccount* createAcc(const string& filePath);
void addAcc(PlayerAccount*& head, PlayerAccount* newUser);
void viewAcc(PlayerAccount*& head, const string& filePath);
void addCredits(PlayerAccount*& head, PlayerAccount* chosen, int c);
void addTime(PlayerAccount*& head, PlayerAccount* chosen, int c);
void deductTime(PlayerAccount*& head, PlayerAccount* chosen, int c);
void writeToFile(const string& filePath, const string& data);
void updateFile(PlayerAccount* head, const string& filePath);
void loadAccounts(PlayerAccount*& head, const string& filePath);
void clearList(PlayerAccount*& head);
void transactionHistory(const string& playerName);

string getCurrentDay() {
    time_t now = time(0);
    tm* localTime = localtime(&now);

    string currentDay = to_string(localTime->tm_mday) + "/" +
                        to_string(localTime->tm_mon + 1) + "/" +
                        to_string(localTime->tm_year + 1900);

    return currentDay;
}

string getCurrentTime() {
    time_t now = time(0);
    tm* localTime = localtime(&now);

    string currentTime = to_string(localTime->tm_hour) + ":" +
                         to_string(localTime->tm_min);
                         to_string(localTime->tm_min);
    return currentTime;
}

int main() {
    PlayerAccount* head = nullptr;

    while (true) {
        cout << "\nComputer Rental System\n" << endl;
        cout << "\t\t[1] User Account Options" << endl;
        cout << "\t\t[2] View Statistics" << endl;
        cout << "\t\t[3] Exit Program" << endl;
        cout << "\t\t\nChoice: ";
        int choice1;
        cin >> choice1;
        switch (choice1)
        {
	        case 1:{
	            cout << "\nUser Account Options\n" << endl;
	            cout << "\t\t[1] Add New Player Account" << endl;
	            cout << "\t\t[2] View Player Account" << endl;
	            cout << "\t\t[3] Delete Player Account" << endl;
	            cout << "\t\t[4] Go back to main menu" << endl;
	            cout << "\t\t\nChoice: ";
	            int choice2;
	            cin >> choice2;
	
	            switch (choice2) {
	                case 1: {
	                    string filePath = "playerData.txt";
	                    addAcc(head, createAcc(filePath));
	                    break;
	                }
	                case 2: {
	                    string filePath = "playerData.txt";
	                    viewAcc(head, filePath);
	                    break;
	                }
	                case 3: {
	                    cout << "Delete Player Account" << endl;
	                    break;
	                }
	                case 4: {
	                    clearList(head); // Clear the linked list before exiting
	                    main();
	                    break;
	                }
	                default: {
	                    cout << "Invalid choice. Please try again." << endl;
	                    break;
	                }
	            }
	            break;
	        }
	        case 2:{
	            cout << "\nView Statistics\n" << endl;
	            cout << "\t\t[1] Leaderboards" << endl;
	            cout << "\t\t[2] Average Earnings" << endl;
	            cout << "\t\t[3] Revenue" << endl;
	            cout << "\t\t[4] Expenses" << endl;
	            cout << "\t\t[5] Income" << endl;
	            cout << "\t\t[6] Go back to main menu" << endl;
	            cout << "\t\t\nChoice: ";
	            int choice4;
	            cin >> choice4;
	            switch(choice4){
	                case 1:{
	                    cout << "\n\t\tLeaderboards" << endl;
	                    break;
	                }
	                case 2:{
	                    cout << "\n\t\tAverage Earnings" << endl;
	                    cout << "\t\t[1] Per Day" << endl;
	                    cout << "\t\t[2] Per Week" << endl;
	                    cout << "\t\t\nChoice: ";
	                    int choice5;
	                    cin >> choice5;
	                    switch (choice5)
	                    {
	                        case 1:{
	                            cout << "\t\tPer Day" << endl;
	                            break;
	                        }case 2:{
	                            cout << "\t\tPer Week" << endl;
	                            break;
	                        }
	                        case 3:{
	                            main();
	                            break;
	                        }
	                        default:
	                            break;
	                    }
	                	break;
	                } case 3:{
	                    cout << "Revenue for today" << endl;
	                	break;
	                } case 4:{
	                    cout << "Expenses for today" << endl;
	                	break;
	                } case 5:{
	                    cout << "Income for today" << endl;
	                	break;
	                }
	            }
	            break;
	        }
	        case 3: {
	            cout << "Closing program... Nice work today!" << endl;
	            return(0);
	            break;
	        }
	        default:{
	        	cout << "Invalid input. Please try again." << endl;
	        	main();
				break;
			}
        }
    }
    return 0;
}

// Create a new player account
PlayerAccount* createAcc(const string& filePath) {
    PlayerAccount* newUser = new PlayerAccount;
    cin.ignore();

    while (true) {
        cout << "Name: ";
        getline(cin, newUser->name);

        ifstream file(filePath);
        if (file.is_open()) {
            string line;
            bool exists = false;
            while (getline(file, line)) {
                stringstream ss(line);
                string n, pw, cred, total_hrs, rem_hrs;
                getline(ss, n, ',');
                getline(ss, pw, ',');
                getline(ss, cred, ',');
                getline(ss, rem_hrs, ',');
                getline(ss, total_hrs, ',');
                if (newUser->name == n) {
                    cout << "Player Account Already Exists. Please use a different name." << endl;
                    exists = true;
                    break;
                }
            }
            file.close();
            if (!exists) {
                break;
            }
        } else {
            cout << "Unable to open file: " << filePath << endl;
            delete newUser;
            return nullptr;
        }
    }

    cout << "Password: ";
    getline(cin, newUser->password);
    
    maxCredit:
    cout << "Credits: ";
    cin >> newUser->credits;
    	if (newUser->credits > 1000 || newUser->credits < 20){
    		cout << "Maximum value of top-up reached. Please input a value between 20-1000 only." << endl;
    		goto maxCredit;
		}

    newUser->filePath = filePath;
    return newUser;
}

// Add a new player account to the linked list and save it to the file
void addAcc(PlayerAccount*& head, PlayerAccount* newUser) {
    if (head == nullptr) {
        head = newUser;
    } else {
        PlayerAccount* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newUser;
    }

    string userData = newUser->name + ',' + newUser->password + ',' + to_string(newUser->credits) + ',' + to_string(newUser->totalHours) + ',' + to_string(newUser->remainingHours) + "\n";
    writeToFile(newUser->filePath, userData);
    cout << "Player Account Successfully added!" << endl;
}

// View player accounts and their details
void viewAcc(PlayerAccount*& head, const string& filePath) {
    loadAccounts(head, filePath); // Load accounts into the linked list

    if (head == nullptr) {
        cout << "No player accounts available." << endl;
        return;
    }

    cout << "Existing player accounts:" << endl;
    PlayerAccount* current = head;
    int index = 1;
    while (current != nullptr) {
        cout << index << ". " << current->name << endl;
        current = current->next;
        index++;
    }

    cout << "\nEnter the name of the player to view their details: ";
    string name;
    cin.ignore(); // Clear the input buffer
    getline(cin, name);

    // Search for the player in the linked list
    current = head;
    while (current != nullptr) {
        if (name == current->name) {
        	AccountOptions:
//        	system("cls");
            cout << "Name: " << current->name << endl;
            cout << "Password: " << current->password << endl;
            cout << "Credits: " << current->credits << endl;
            cout << "Remaining Hours: " << current->remainingHours << endl << endl;
            cout << "Accumulated Hours: " << current->totalHours << endl << endl;
            
            cout << "\t\t\t[1] Add Credits" << endl;
            cout << "\t\t\t[2] Add Time" << endl;
            cout << "\t\t\t[3] Deduct Time" << endl;
            cout << "\t\t\t[4] Transaction History" << endl;
            cout << "\t\t\t[5] Go back to main menu" << endl;
            cout << "\t\t\nChoice: ";
            int choice3;
        	cin >> choice3;
            switch (choice3)
            {
            	case 1:{
            		string filePath = "playerData.txt";
            		cout << "How much credits would you like to add?" << endl;
            		cout << "Input: ";
            		float addedCreditsValue = 0.0;
            		cin >> addedCreditsValue;
					
					addCredits(head, current, addedCreditsValue);
					goto AccountOptions;
					break;
				}
                case 2:{
                	string filePath = "playerData.txt";
                    cout << "Add Time" << endl;
					cout << "How many hours would you like to add?" << endl;
                    cout << "1. 1 hour" << endl;
                    cout << "2. 3 hours" << endl;
                    cout << "3. 6 hours" << endl;
                    cout << "4. 10 hours" << endl;
                    cout << "5. 24 hours\n" << endl;
                    cout << "Choice: ";
                    int timeChoice;
                    cin >> timeChoice;

                    addTime(head, current, timeChoice);
                    goto AccountOptions;
                    break;
                }
                case 3:{
                    string filePath = "playerData.txt";
                    cout << "Deduct Time" << endl;
					cout << "How many hours would you like to play?" << endl;
                    cout << "1. 1 hour" << endl;
                    cout << "2. 3 hours" << endl;
                    cout << "3. 6 hours" << endl;
                    cout << "4. 10 hours" << endl;
                    cout << "5. 24 hours\n" << endl;
                	cout << "Choice: ";
                    int timeChoice;
                    cin >> timeChoice;

                    deductTime(head, current, timeChoice);
                    goto AccountOptions;
                    break;
                }
                case 4:{
                    cout << "Transaction History" << "\n" << endl;
                    transactionHistory(current->name);
                    system("pause");
                    goto AccountOptions;
                    break;
                }
                case 5:{
                    main();
                    break;
                }
                default:
                    break;
                }
        	}
        	current = current->next;
    	}
    cout << "Player not found." << endl;
    return;
}

// Write data to the file
void writeToFile(const string& filePath, const string& data) {
    ofstream file(filePath, ios::app);
    if (file.is_open()) {
        file << data;
        file.close();
    } else {
        cout << "Unable to open file: " << filePath << endl;
    }
}

// Update the file with the current linked list data
void updateFile(PlayerAccount* head, const string& filePath) {
    ofstream file(filePath);
    if (file.is_open()) {
        PlayerAccount* current = head;
        while (current != nullptr) {
            file << current->name << ',' << current->password << ',' << current->credits << ',' << current->totalHours << ',' << current->remainingHours << '\n';
            current = current->next;
        }
        file.close();
    } else {
        cout << "Unable to open file: " << filePath << endl;
    }
}

// Load player accounts from the file into the linked list
void loadAccounts(PlayerAccount*& head, const string& filePath) {
    clearList(head); // Clear existing linked list
    ifstream file(filePath);
    if (!file.is_open()) {
        cout << "Unable to open file: " << filePath << endl;
        return;
    }

    PlayerAccount* current = nullptr;
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name, password, cred, total_hrs, rem_hrs;
        getline(ss, name, ',');
        getline(ss, password, ',');
        getline(ss, cred, ',');
        getline(ss, total_hrs, ',');
        getline(ss, rem_hrs, ',');

        PlayerAccount* newUser = new PlayerAccount;
        newUser->name = name;
        newUser->password = password;
        // Convert credits, total hours, and remaining hours
        stringstream(cred) >> newUser->credits;
        stringstream(total_hrs) >> newUser->totalHours;
        stringstream(rem_hrs) >> newUser->remainingHours;
        newUser->filePath = filePath;

        if (head == nullptr) {
            head = newUser;
            current = head;
        } else {
            current->next = newUser;
            current = current->next;
        }
    }
    file.close();
}

void addCredits(PlayerAccount*& head, PlayerAccount* chosen, int c) {
	float creditsAdded = 0.0;
	chosen->credits += c;
	creditsAdded += c;
	
	updateFile(head, chosen->filePath);

    string transactionData = chosen->name + "," + "Added credits" + "," + to_string(creditsAdded) + "," + getCurrentDay() + "," + getCurrentTime() + "\n";
    writeToFile("TransactionsFile.txt", transactionData);
}

// Add hours and balance to a player's account
void addTime(PlayerAccount*& head, PlayerAccount* chosen, int c) {
    float creditsDeducted = 0.0;
    int hoursAdded = 0;
    
    switch (c) {
        case 1:
            chosen->remainingHours += 1;
            chosen->totalHours += 1;
            creditsDeducted = 25.0;
            hoursAdded = 1;
            cout << "Successfully added 1 hour to account hour balance." << endl;
            break;
        case 2:
            chosen->remainingHours += 3;
            chosen->totalHours += 3;
            creditsDeducted = 70.0;
            hoursAdded = 3;
            cout << "Successfully added 3 hours to account hour balance." << endl;
            break;
        case 3:
            chosen->remainingHours += 6;
            chosen->totalHours += 6;
            creditsDeducted = 140.0;
            hoursAdded = 6;
            cout << "Successfully added 6 hours to account hour balance." << endl;
            break;
        case 4:
            chosen->remainingHours += 10;
            chosen->totalHours += 10;
            creditsDeducted = 250.0;
            hoursAdded = 10;
            cout << "Successfully added 10 hours to account hour balance." << endl;
            break;
        case 5:
            chosen->remainingHours += 24;
            chosen->totalHours += 24;
            creditsDeducted = 500.0;
            hoursAdded = 24;
            cout << "Successfully added 24 hours to account hour balance." << endl;
            break;
        default:
            cout << "Invalid choice for time addition." << endl;
            return;
    }
    
    chosen->credits -= creditsDeducted;
    updateFile(head, chosen->filePath);

    string transactionData = chosen->name + "," + "Added" + "," + to_string(hoursAdded) + "," + getCurrentDay() + "," + getCurrentTime() + "\n";
    writeToFile("TransactionsFile.txt", transactionData);
}

// Deduct time from a player account and update the file
void deductTime(PlayerAccount*& head, PlayerAccount* chosen, int c) {
    int hoursDeducted = (c == 1) ? 1 : 3; // Determine the hours to deduct based on user

    if (hoursDeducted <= chosen->remainingHours) {
        chosen->remainingHours -= hoursDeducted;
        if (c==1){
        	cout << "Successfully deducted 1 hour from account hour balance." << endl;
		}
		else if (c==2){
			cout << "Successfully deducted 3 hour from account hour balance." << endl;
		}
		else {
			cout << "Invalid input. Please input a valid number of hours." << endl;
		}
        updateFile(head, chosen->filePath);

        string transactionData = chosen->name + ", " + "Deducted" + ", " + to_string(hoursDeducted) + ", " + getCurrentDay() + ", " + getCurrentTime() + "\n";
        writeToFile("TransactionsFile.txt", transactionData);
    } else {
        cout << "Insufficient hours in account." << endl;
    }
}

// Clear the linked list
void clearList(PlayerAccount*& head) {
    PlayerAccount* current = head;
    while (current != nullptr) {
        PlayerAccount* temp = current;
        current = current->next;
        delete temp;
    }
    head = nullptr;
}

void transactionHistory(const string& playerName) {
    ifstream file("TransactionsFile.txt");
    if (file.is_open()) {
        string line;
        bool found = false;
        cout << "Transaction Type   |   Amount   |      Date      |      Time" << endl;
        while (getline(file, line)) {
            stringstream ss(line);
            string name, transactionType, amount, date, time;
            getline(ss, name, ',');
            getline(ss, transactionType, ',');
            getline(ss, amount, ',');
            getline(ss, date, ',');
            getline(ss, time, ',');

            if (name == playerName) {
            	cout << setw(20) << left << transactionType << setw(14) << left << amount + " hour/s" << setw(19) << left << date << setw(10) << left << time << endl;
                found = true;
            }
        }
        file.close();
        cout << "\n" << endl;

        if (!found) {
            cout << "No transaction history found for " << playerName << endl;
        }
    } else {
        cout << "Unable to open file: transactionHistory.txt" << endl;
    }
}
