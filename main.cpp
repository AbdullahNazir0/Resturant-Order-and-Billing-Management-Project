#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <iomanip>

using namespace std;

void displayLoginPage();
void displayHomePage();
void takeOrder(string items[], double prices[], int cart[], int itemsCount);
void showTotalBills();
void searchForBills();
void deleteBill();
bool checkName(string);

int main()
{

    displayLoginPage();

    return 0;
}

void displayLoginPage()
{

    int userId, userPassword;
    
    system("clear");

    while(true)
    {

        cout << "------------------Login Page------------------" << endl;

        cout << "Enter User Id: ";
        // cin >> userId;
        if(!(cin >> userId))
        {
            system("clear");
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Enter a numerical id: " << endl;
        }
        else
        {
            cout << "Enter User Password: ";
            // cin >> userPassword;
            if(!(cin >> userPassword))
            {

                system("clear");
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Enter a numerical password: " << endl;
            }
            else
            {

                if(userId == 123)
                {

                    if(userPassword == 123)
                    {

                        cout << "Login Successfull" << endl;
                        displayHomePage();
                        break;
                    }
                    else 
                    {

                        cout << "Wrong Password. Please Try Again." << endl;
                        system("clear");
                    }
                }
                else
                {

                    cout << "Wrong User Id. Please Try Again." << endl;
                    system("clear");
                }
            }
        }
    }
}

void displayHomePage()
{

    system("clear");
    cout << "------------------Home Page------------------" << endl;

    string items[100];       // Parallel array 1.
    double prices[100];      // Parallel array 2.
    int cart[100] = {0};     // Parallel array 3.
    int itemsCount = 0;

    ifstream fin;
    fin.open("itemsData.txt");

    if( fin.is_open() )
    {
        while( !fin.eof() )
        {
            
            getline(fin, items[itemsCount], ' ');
            fin >> prices[itemsCount];
            fin.ignore();
            itemsCount++;

        }       

        while( true )
        {

            int choice;

            cout << "1: Take Order\n"
                    "2: Show Total Bills\n"
                    "3: Search a Bill\n"
                    "4: Delete a Bill\n"
                    "5: Exit Program\n"
                    "Your choice: ";
            // cin >> choice;
            if(!(cin >> choice))
            {
                system("clear");
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Enter a numerical choice value: " << endl;
                continue;
            }

            switch( choice )
            {
                case 1:
                
                    takeOrder(items, prices, cart, itemsCount);
                    break;

                case 2:

                    showTotalBills();
                    break;

                case 3:

                    searchForBills();
                    break;

                case 4:

                    deleteBill();
                    break;

                case 5:
                    exit(0);

                default:
                    cout << "Invalid Input. Please Input a Number <1-5>" << endl;
                    system("clear");
            }
        }

        fin.close();

    }
    else
    {

        cout << "File not found." << endl;
        cout << "No data to show." << endl;
        return;

    }


}

void takeOrder(string items[], double prices[], int cart[], int itemsCount)
{

    system("clear");

    for(int i = 0; i < itemsCount; i++)
    {
        cart[i] = 0;        // As array already exists, we have to 0 each index seperately.
    }

    string customerName = "";
    int billId;
    int menuChoice;
    double totalBill = 0;
    int itemQuantity;
    int orderQuantity = 0;
    char completeOrderChoice;

    ifstream fin;
    fin.open("lastBillId.txt");

    if( fin.is_open())
    {
        fin >> billId;
        billId++;
        fin.close();
    }
    else
        billId = 1;
    

    cin.ignore();
    cout << "Enter Customer's Name: ";
    getline(cin, customerName);

    while( true )
    {
        if(checkName(customerName))
        {
            for(int i = 0; i < customerName.length(); i++)
            {
                if(customerName[i] == '-')
                    continue;
                customerName[i] = toupper(customerName[i]);
            }
            break;
        }
        else
        {
            cout << "Invalid Attempt. Please Don't use Numbers. Enter Name with Characters between <a-z and dashes'-'>" << endl;
            cout << "Enter Customer's Name: ";
            getline(cin, customerName);
        }
    }


    ofstream fout;
    fout.open("ordersInfo.txt", ios::app);



    fout << endl << endl << customerName << " " << billId << " ";

    while( true )
    {

        cout << setw(3) << left << "Sr#" << "\t" << setw(30) << "Item Names" << "\t" << fixed << setprecision(2) << "Prices" << endl;
        for(int i = 0; i < itemsCount; i++)
        {
            cout << setw(3) << i + 1 << "\t" << setw(30) << items[i] << "\t" << "$" << prices[i] << endl;
        }
        cout << "Your choice: ";
        // cin >> menuChoice;
        if(!(cin >> menuChoice))
        {
            system("clear");
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Enter a numerical menu choice value: " << endl;
            continue;
        }

        if(menuChoice > itemsCount)
        {
            cout << "Invalid Input. Please Input a Number <1-" << itemsCount << "> " << endl;
        }

        cout << "Enter quantity of " << items[menuChoice - 1] << ": ";
        cin >> itemQuantity;
        if(cart[menuChoice - 1] == 0)
            orderQuantity++;
        cart[menuChoice - 1] += itemQuantity;

        // cout << "Your Total Bill is $" << totalBill << endl;

        while( true )
        {
            
            cout << "Do You Want to Complete the Order(y/n): ";
            cin >> completeOrderChoice;

            if( completeOrderChoice == 'y' || completeOrderChoice == 'Y')
            {

                for(int i = 0; i < itemsCount; i++)
                {
                    totalBill += (prices[i] * cart[i]);
                }

                system("clear");

                cout << "-----------------Lunarsi Restaurant-----------------\n\n";
                cout << setw(11) << "\t" << "Reciept of Sales\n\n\n";
                cout << "Customer's Name: " << customerName << endl;
                cout << "Bill Id: " << billId << endl;
                cout << "----------------------------------------------------\n\n";
                cout << setw(3) << "QTY" << "\t" << setw(30) << "ITEM" << "\t" << "AMT" << endl; 
                cout << "----------------------------------------------------\n\n";
                fout << orderQuantity << endl;
                for(int i = 0; i < itemsCount; i++)
                {

                    if(cart[i] != 0)
                    {
                        cout << setw(3) << cart[i] << "\t" << setw(30) << items[i] << "\t$" << fixed << setprecision(2) << (prices[i] * cart[i]) << endl; 
                        fout << cart[i] << " " << items[i] << " " << fixed << setprecision(2) << (prices[i] * cart[i]) << endl; 

                    }

                }

                ofstream fout2;
                fout2.open("lastBillId.txt");
                fout2 << billId;
                fout2.close();

                cout << "\n----------------------------------------------------\n\n";
                cout << "\t" << setw(32) << "Total" << fixed << setprecision(2) << "$" << totalBill << endl;
                fout << fixed << setprecision(2) << totalBill;
                cout << "\n----------------------------------------------------\n\n";
                cout << setw(10) << "\t" << "Thanks for Visiting\n";
                cout << "\n----------------------------------------------------\n\n";

                fout.close();

                return;

            }
            else if( completeOrderChoice == 'n' || completeOrderChoice == 'N')
            {
                break;
            }
            else
            {
                cout << "Enter your choice as 'y' or 'n' only." << endl;
            }
        }

    }

}

void showTotalBills()
{

    ifstream fin;
    fin.open("ordersInfo.txt");

    string customerName, itemName;
    int id, count, quantity;
    double itemPrice, totalPrice;
    char temp;

    if( fin.is_open() )
    {
        while( !fin.eof() )
        {

            fin >> customerName >> id >> count;
            cout << left;
            cout << "-----------------Lunarsi Restaurant-----------------\n\n";
            cout << setw(11) << "\t" << "Reciept of Sales\n\n\n";
            cout << "Customer's Name: " << customerName << endl;
            cout << "Bill Id: " << id << endl;
            cout << "----------------------------------------------------\n\n";
            cout << setw(3) << "QTY" << "\t" << setw(30) << "ITEM" << "\t" << "AMT" << endl; 
            cout << "----------------------------------------------------\n\n";
            for(int i = 0; i < count; i++)
            {
                fin >> quantity >> itemName >> itemPrice;
                cout << setw(3) << quantity << "\t" << setw(30) << itemName << "\t$"  << itemPrice << endl;
            }
            fin >> totalPrice;
            cout << "\n----------------------------------------------------\n\n";
            cout << "\t" << setw(32) << "Total" << fixed << setprecision(2) << "$" << totalPrice << endl;
            cout << "\n----------------------------------------------------\n\n";
            cout << setw(10) << "\t" << "Thanks for Visiting\n";
            cout << "\n----------------------------------------------------\n\n";

        }
        fin.close();
    }
    else
    {
        cout << "Total Bills File Not Found." << endl;
        return;
    }

}

void searchForBills()
{

    int searchBillId;

    system("clear");
    
    while( true )
    {

        cout << "Enter Bill Id you want to search: ";
        // cin >> searchBillId;
        if(!(cin >> searchBillId))
        {
            system("clear");
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Enter a numerical bill id to search: " << endl;
            continue;
        }
        else
            break;
    }

    ifstream fin;
    fin.open("ordersInfo.txt");

    string customerName, itemName;
    int id, count, quantity;
    double itemPrice, totalPrice;
    char temp;

    if( fin.is_open())
    {
        while( !fin.eof() )
        {

            fin >> customerName >> id >> count;
            if(id == searchBillId)
            {
                cout << left;
                cout << "-----------------Lunarsi Restaurant-----------------\n\n";
                cout << setw(11) << "\t" << "Reciept of Sales\n\n\n";
                cout << "Customer's Name: " << customerName << endl;
                cout << "Bill Id: " << id << endl;
                cout << "----------------------------------------------------\n\n";
                cout << setw(3) << "QTY" << "\t" << setw(30) << "ITEM" << "\t" << "AMT" << endl; 
                cout << "----------------------------------------------------\n\n";
                for(int i = 0; i < count; i++)
                {
                    fin >> quantity >> itemName >> itemPrice;
                    cout << setw(3) << quantity << "\t" << setw(30) << itemName << "\t$"  << itemPrice << endl;
                }
                fin >> totalPrice;
                cout << "\n----------------------------------------------------\n\n";
                cout << "\t" << setw(32) << "Total" << fixed << setprecision(2) << "$" << totalPrice << endl;
                cout << "\n----------------------------------------------------\n\n";
                cout << setw(10) << "\t" << "Thanks for Visiting\n";
                cout << "\n----------------------------------------------------\n\n";
                return;
            }
            else
            {
                for(int i = 0; i < count; i++)
                {
                    fin >> quantity >> itemName >> itemPrice;
                }
                fin >> totalPrice;
            }
        }

        cout << "\n\nEntered Bill doesn't exist.\n\n" << endl;
        fin.close();
    }
    else
    {
        cout << "\n\nTotal Bills File Not Found.\n\n" << endl;
        return;
    }
}

void deleteBill()
{
        
    int deleteBillId;

    system("clear");
    
    while(true)
    {

        cout << "Enter Bill Id you want to delete: ";
        // cin >> deleteBillId;
        if(!(cin >> deleteBillId))
        {
            system("clear");
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Enter a numerical bill id to delete: " << endl;
            continue;
        }
        else
            break;
    }

    ifstream fin;
    fin.open("ordersInfo.txt");

    string customerName, itemName;
    int id, count, quantity;
    double itemPrice, totalPrice;
    char temp;

    if( fin.is_open())
    {

        ofstream fout;
        fout.open("temp.txt");

        while( fin >> customerName >> id >> count )
        {

            if(id != deleteBillId)
            {
                
                fout << endl << customerName << " " << id << " " << count << endl;
                for(int i = 0; i < count; i++)
                {
                    fin >> quantity >> itemName >> itemPrice;
                    fout << quantity << " " << itemName << " " << itemPrice << endl;
                }
                fin >> totalPrice;
                fout << totalPrice;
            }
            else
            {
                for (int i = 0; i < count; i++) 
                {
                    fin >> quantity >> itemName >> itemPrice;
                }
                fin >> totalPrice;
            }
        }

        remove("ordersInfo.txt");
        rename("temp.txt", "ordersInfo.txt");

        cout << "Bill deleted successfully." << endl;

        fin.close();
        fout.close();
    }
    else
    {
        cout << "\n\nTotal Bills File Not Found.\n\n" << endl;
        return;
    }
}

bool checkName(string name)
{
    bool flag = true;
    for(int i = 0; i < name.length(); i++)
    {
        if( !isalpha(name[i]) && !(name[i] == '-') )
        {
            flag = false;
            break;
        }
    }

    return flag;
}
