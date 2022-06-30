#include <bits/stdc++.h>
#define en "\n"
#define ll long long
#define mini INT64_MIN
#define maxi INT64_MAX
#define sz size()
#define ss second
#define ff first
#define pb push_back
#define ceil(x) ceil((double)x)
using namespace std;
#define forl(i, a, b) for (ll i = a; i < b; i++)

// Its a global deque representing the shopping cart(contains product id and quantity selected by the user)
deque<pair<int, int>> cart;                             // cart contains pid and quantity selected
vector<pair<int, pair<string, string>>> productDetails; // contains pid, product name and description
vector<pair<int, pair<float, int>>> productPriceQty;    // contains pid, product price and quantity available

// This function checks if the username given by new user is available or already exists
int checkUsername(string username)
{
    vector<pair<string, string>> users;
    ifstream fin;
    fin.open("userdetails.txt", ios_base::in);
    if (fin.is_open())
    {
        string s1, s2;
        while (getline(fin, s1) && getline(fin, s2))
        {
            users.push_back(make_pair(s1, s2));
        }
        fin.close();
    }
    int flag = 0;
    for (auto user : users)
    {
        if (user.ff == username)
        {
            flag = 1;
            break;
        }
    }
    if (flag == 1)
        return 0;
    else
        return 1;
}

// The following function is used for signing up into our application
void signUp()
{
    cout << "\t\t\tUSER REGISTRATION\n\n";
    string username, e, pass; // username stores the username and pass stores the password
    ofstream fout;
    fout.open("userdetails.txt", ios_base::app);
    if (fout.is_open())
    {
        while (true)
        {
            cout << "\tEnter desired username for your account: ";
            cin >> username;
            int check = checkUsername(username);
            if (check == 1)
            {
                break;
            }
            else
                cout << "\n\tOops! The username already exists. Please Try again.\n\n";
        }

        bool checkUpperCase = false;
        bool checkLowerCase = false;
        bool checkDigit = false;
        bool special_char = false;

        regex upper_case_expression{"[A-Z]+"};
        regex lower_case_expression{"[a-z]+"};
        regex number_expression{"[0-9]+"};

        string pass;

        int regSuccess = false;

        do
        {

            cout << "\n\tSET PASSWORD\n";
            cout << "\tNOTE: Password should contain atleast 8 characters, atleast 1 uppercase, atleast 1 lowercase and atleast 1 numeric character\n\n";
            cout << "\tEnter desired password for your account: ";
            cin >> pass;

            if (pass.size() < 8)
            {
                cout << "\tIncorrect Password. Please Try again.\n\n";
            }
            else
            {

                checkUpperCase = regex_search(pass, upper_case_expression);
                checkLowerCase = regex_search(pass, lower_case_expression);
                checkDigit = regex_search(pass, number_expression);

                int sum_of_positive_results = checkUpperCase + checkLowerCase + checkDigit;

                if (sum_of_positive_results != 3)
                {
                    cout << "\tIncorrect Password. Please Try again.\n\n";
                }
                else
                {
                    regSuccess = true;
                }
            }

        } while (!regSuccess);

        fout << username << "\n"
             << pass << "\n";
        fout.close();
    }
}

// The following function is used for logging upto into our application
int login(string username, string pass)
{

    // The below vector is used to fetch username and passwords of all registers and each user's details(username,password) are stored as a pair
    vector<pair<string, string>> users;
    ifstream fin;
    fin.open("userdetails.txt", ios_base::in);
    int i = 0;
    if (fin.is_open())
    {
        string s1, s2;
        while (getline(fin, s1) && getline(fin, s2))
        {
            users.push_back(make_pair(s1, s2));
        }
        fin.close();
    }
    int flag = 0, pos;
    for (auto v : users)
    {
        if (v.ff == username && v.ss == pass)
        {
            flag = 1;
            break;
        }
    }
    if (flag == 0)
        return 0;
    else
        return 1;
}

int welcome() // The following function is used to ask the user whether they want to sign up or loginnt welcome()
{
    cout << "\t\t********************************************" << en << en;
    cout << "\t\t\t    Press 1 to Login" << en;
    cout << "\t\t\t    Press 2 to Sign Up" << en << en;
    cout << "Press 3 to see items" << en;
    cout << "\t\t********************************************" << en << en;
    cout << "\tEnter your choice: ";
    int ch;
    cin >> ch;
    cout << en;
    return ch;
}

// The following function is the main dashboard of our application
int dashboard()
{
    int ch;
    cout << "\t\tEasyBuy Dashboard" << en << en;
    cout << "Hurry! Limited Time Offer! " << en << en;
    cout << "2% Discount on Shopping above Rs.1000" << en;
    cout << "4% Discount on Shopping above Rs.10000" << en;
    cout << "10% Discount on Shopping above Rs.100000" << en;
    cout << "No Promo Code Required. Discount Will Be Automatically Applied." << en << en;
    cout << "Do you want to search for item?press 1 else 0";
    int search;
    cin >> search;
    if (search)
    {
        string name;
        cout << "enter item name you want to search";
        getline(cin,name);
        getline(cin,name);
        int flag = 0;
        for (auto i : productDetails)
        {
            if (i.second.first == name)
            {
                flag = 1;
                cout << "item is present";
                break;
            }
        }
        if (flag == 0)
            cout << "not present";
    }
    cout << "CATEGORIES AVAILABLE:" << en;
    cout << "1. Electronics" << en;
    cout << "2. Grocery" << en;
    cout << "3. Fashion" << en;
    cout << "4. Stationery" << en;

    cout << "Enter the desired category of item" << en;
    cin >> ch;
    return ch;
}

// The following function displays the electronics item and enables the user to select items from the same
int electronics()
{

    cout << "\nEASYBUY ELECTRONICS:" << en;
    while (true)
    {

        // The following variable is used to ask choice among the various catehgories of electronics from the user
        int ch;
        cout << "1. Mobiles" << en;
        cout << "2. Laptops" << en;
        cout << "3. Accesories" << en;
        cout << "Enter desired sub-category: ";
        cin >> ch;
        int error = 0;

        // The following vector is used to stores the values of quantity available of the electronics items
        vector<int> qtyAvailable;

        // The following vector is used to store the prices of the electronics items
        vector<float> itemPrices;

        // The following vector is used to store the details of the electronics items
        vector<string> itemDetails;

        for (int i = 0; i < 9; i++)
        {
            qtyAvailable.pb(productPriceQty[i].second.second);
            itemPrices.pb(productPriceQty[i].second.first);
            itemDetails.pb(productDetails[i].second.second);
        }
        // Depending on category selected by user we will display items in that category accordingly
        switch (ch)
        {
        case 1:
        {
        wrongElec1:
            cout << "\nITEM NO.\tITEM NAME\t\tQUANTITY AVAILABLE\tPRICE" << en;
            for (int i = 0; i < 3; i++)
            {
                cout << i + 1 << "\t\t" << productDetails[i].second.first << "\t" << qtyAvailable[i] << "\t\t\t" << itemPrices[i] << en;
            }
        repeatDetails1:
            cout << "\nDo you want to view the Item Description Too?\n Press 1 for Yes. 0 for No: ";
            int detailsNeeded;
            cin >> detailsNeeded;
            if (detailsNeeded == 1)
            {
                cout << "\nITEM NO.\tITEM NAME\t\tQUANTITY AVAILABLE\tPRICE\tDESCRIPTION" << en;
                for (int i = 0; i < 3; i++)
                {
                    cout << i + 1 << "\t\t" << productDetails[i].second.first << "\t" << qtyAvailable[i] << "\t\t\t" << itemPrices[i] << "\t" << itemDetails[i] << en;
                }
            }
            else if (detailsNeeded != 0)
            {
                cout << "Incorrect Input entered.Please Try Again!" << en;
                goto repeatDetails1;
            }
            int subch;
            cout << "Enter the desired item number for purchase" << en;
            cin >> subch;
            if (subch == 1 || subch == 2 || subch == 3)
            {
                int itemAlreadyExists = 0;
                for (auto item : cart)
                {
                    int pid = item.first;
                    if (pid == subch)
                    {
                        itemAlreadyExists = 1;
                        break;
                    }
                }
                if (itemAlreadyExists)
                {
                    cout << "Item has already been added to your cart! Continue Shopping for Other Products!" << en;
                    break;
                }

                if (qtyAvailable[subch - 1] == 0)
                {
                    cout << "Sorry. This item is out of stock. Please select another item" << en;
                    break;
                }
            selectQty1:
                int qty;
                cout << "Enter the quantity for purchase" << en;
                cin >> qty;
                if (qty > qtyAvailable[subch - 1])
                {
                    cout << qty << " Units are not in stock. Please enter value within Available quantity.\n"
                         << en;
                    goto selectQty1;
                }
                else if (qty <= 0)
                {
                    cout << "Please enter appropriate value as quantity.\n"
                         << en;
                    goto selectQty1;
                }
                else
                {
                    cart.pb({subch, qty});
                    cout << "ITEM SUCCESSFULLY ADDED! Continue Shopping!\n"
                         << en;
                    qtyAvailable[subch - 1] -= qty;
                }
            }
            else
            {
                cout << "Sorry! Invalid Item number. Please select item again\n"
                     << en;
                goto wrongElec1;
            }
        }
        break;
        case 2:
        {
        wrongElec2:
            cout << "\nITEM NO.\tITEM NAME\t\tQUANTITY AVAILABLE\tPRICE" << en;
            for (int i = 3; i < 6; i++)
            {
                cout << i - 2 << "\t\t" << productDetails[i].second.first << "\t" << qtyAvailable[i] << "\t\t\t" << itemPrices[i] << en;
            }
        repeatDetails2:
            cout << "\nDo you want to view the Item Description Too?\n Press 1 for Yes. 0 for No: ";
            int detailsNeeded;
            cin >> detailsNeeded;
            if (detailsNeeded == 1)
            {
                cout << "\nITEM NO.\tITEM NAME\t\tQUANTITY AVAILABLE\tPRICE\tDESCRIPTION" << en;
                for (int i = 3; i < 6; i++)
                {
                    cout << i - 2 << "\t\t" << productDetails[i].second.first << "\t" << qtyAvailable[i] << "\t\t\t" << itemPrices[i] << "\t" << itemDetails[i] << en;
                }
            }
            else if (detailsNeeded != 0)
            {
                cout << "Incorrect Input entered.Please Try Again!" << en;
                goto repeatDetails2;
            }
            int subch;
            cout << "Enter item which you want to add to cart" << en;
            cin >> subch;
            if (subch == 1 || subch == 2 || subch == 3)
            {
                int itemAlreadyExists = 0;
                for (auto item : cart)
                {
                    int pid = item.first;
                    if (pid == subch + 3)
                    {
                        itemAlreadyExists = 1;
                        break;
                    }
                }
                if (itemAlreadyExists)
                {
                    cout << "Item has already been added to your cart! Continue Shopping for Other Products!" << en;
                    break;
                }
                if (qtyAvailable[subch - 1 + 3] == 0)
                {
                    cout << "Sorry. This item is out of stock. Please select another item" << en;
                    break;
                }
            selectQty2:
                int qty;
                cout << "Enter the quantity for purchase" << en;
                cin >> qty;
                if (qty > qtyAvailable[subch - 1 + 3])
                {
                    cout << qty << " Units are not in stock. Please enter value within Available quantity." << en;
                    goto selectQty2;
                }
                else if (qty <= 0)
                {
                    cout << "Please enter appropriate value as quantity.\n"
                         << en;
                    goto selectQty2;
                }
                else
                {
                    cart.pb({subch + 3, qty});
                    cout << "ITEM SUCCESSFULLY ADDED! Continue Shopping!\n"
                         << en;
                    qtyAvailable[subch - 1 + 3] -= qty;
                }
            }
            else
            {
                cout << "Sorry! Invalid Item number. Please select item again\n"
                     << en;
                goto wrongElec2;
            }
            break;
        }
        case 3:
        {

        wrongElec3:
            cout << "\nItem No.\tITEM NAME\t\tQUANTITY AVAILABLE\tPRICE" << en;
            for (int i = 6; i < 9; i++)
            {
                cout << i - 5 << "\t\t" << productDetails[i].second.first
                     << "\t" << qtyAvailable[i] << "\t\t\t" << itemPrices[i] << en;
            }
        repeatDetails3:
            cout << "\nDo you want to view the Item Description Too?\n Press 1 for Yes. 0 for No: ";
            int detailsNeeded;
            cin >> detailsNeeded;
            if (detailsNeeded == 1)
            {
                cout << "\nITEM NO.\tITEM NAME\t\tQUANTITY AVAILABLE\tPRICE\tDESCRIPTION" << en;
                for (int i = 6; i < 9; i++)
                {
                    cout << i - 5 << "\t\t" << productDetails[i].second.first << "\t" << qtyAvailable[i] << "\t\t\t" << itemPrices[i] << "\t" << itemDetails[i] << en;
                }
            }
            else if (detailsNeeded != 0)
            {
                cout << "Incorrect Input entered.Please Try Again!" << en;
                goto repeatDetails3;
            }
            cout << "Enter item which you want to add to cart" << en;
            int subch;
            cin >> subch;
            if (subch == 1 || subch == 2 || subch == 3)
            {
                int itemAlreadyExists = 0;
                for (auto item : cart)
                {
                    int pid = item.first;
                    if (pid == subch + 6)
                    {
                        itemAlreadyExists = 1;
                        break;
                    }
                }
                if (itemAlreadyExists)
                {
                    cout << "Item has already been added to your cart! Continue Shopping for Other Products!" << en;
                    break;
                }
                if (qtyAvailable[subch - 1 + 6] == 0)
                {
                    cout << "Sorry. This item is out of stock. Please select another item" << en;
                    break;
                }
            selectQty3:
                int qty;
                cout << "Enter the quantity for purchase" << en;
                cin >> qty;
                if (qty > qtyAvailable[subch - 1 + 6])
                {
                    cout << qty << " Units are not in stock. Please enter value within Available quantity." << en;
                    goto selectQty3;
                }
                else if (qty <= 0)
                {
                    cout << "Please enter appropriate value as quantity.\n"
                         << en;
                    goto selectQty3;
                }
                else
                {

                    cart.pb({subch + 6, qty});
                    cout << "ITEM SUCCESSFULLY ADDED! Continue Shopping!\n"
                         << en;
                    qtyAvailable[subch - 1 + 6] -= qty;
                }
            }
            else
            {
                cout << "Sorry! Invalid Item number. Please select item again\n"
                     << en;
                goto wrongElec3;
            }
            break;
        }
        default:
        {
            error = 1;
            cout << "Sorry! Invalid Sub-Category selected. Please select desired Sub-Category again\n"
                 << en;
            break;
        }
        }

        if (error == 1)
            continue;

        for (int i = 0; i < 9; i++)
        {
            productPriceQty[i].second.second = qtyAvailable[i];
        }
        ofstream fout;
        fout.open("priceQtyDetails.txt", ios_base::out);
        for (auto v : productPriceQty)
        {
            fout << v.first << en;
            fout << v.second.first << en;
            fout << v.second.second << en;
        }
        fout.close();

        int elech;
        cout << "\nDo you want to Continue Shopping? Press 1 for Yes, 0 for No" << en;
        cin >> elech;
        return elech;
    }
}

int grocery()
{
    cout << "\nEASYBUY GROCERY:" << en;
    while (true)
    {
        int ch;
        cout << "1. Dairy Products" << en;
        cout << "2. Snacks and Beverages" << en;
        cout << "3. Body Care Products" << en;
        cout << "Enter desired sub-category: ";
        cin >> ch;
        int error = 0;
        vector<int> qtyAvailable;
        vector<float> itemPrices;
        vector<string> itemDetails;
        for (int i = 9; i < 18; i++)
        {
            qtyAvailable.pb(productPriceQty[i].second.second);
            itemPrices.pb(productPriceQty[i].second.first);
            itemDetails.pb(productDetails[i].second.second);
        }
        switch (ch)
        {
        case 1:
        {
        wrongGroc1:
            cout << "\nITEM NO.\tITEM NAME\t\tQUANTITY AVAILABLE\tPRICE" << en;
            for (int i = 0; i < 3; i++)
            {
                cout << i + 1 << "\t\t" << productDetails[i + 9].second.first
                     << "\t" << qtyAvailable[i] << "\t\t\t" << itemPrices[i] << en;
            }
        repeatDetails4:
            cout << "\nDo you want to view the Item Description Too?\n Press 1 for Yes. 0 for No: ";
            int detailsNeeded;
            cin >> detailsNeeded;
            if (detailsNeeded == 1)
            {
                cout << "\nITEM NO.\tITEM NAME\t\tQUANTITY AVAILABLE\tPRICE\tDESCRIPTION" << en;
                for (int i = 0; i < 3; i++)
                {
                    cout << i + 1 << "\t\t" << productDetails[i + 9].second.first << "\t" << qtyAvailable[i] << "\t\t\t" << itemPrices[i] << "\t" << itemDetails[i] << en;
                }
            }
            else if (detailsNeeded != 0)
            {
                cout << "Incorrect Input entered.Please Try Again!" << en;
                goto repeatDetails4;
            }
            int subch;
            cout << "Enter the desired item number for purchase" << en;
            cin >> subch;
            if (subch == 1 || subch == 2 || subch == 3)
            {
                int itemAlreadyExists = 0;
                for (auto item : cart)
                {
                    int pid = item.first;
                    if (pid == subch + 10)
                    {
                        itemAlreadyExists = 1;
                        break;
                    }
                }
                if (itemAlreadyExists)
                {
                    cout << "Item has already been added to your cart! Continue Shopping for Other Products!" << en;
                    break;
                }
                if (qtyAvailable[subch - 1] == 0)
                {
                    cout << "Sorry. This item is out of stock. Please select another item" << en;
                    break;
                }
            selectQty11:
                int qty;
                cout << "Enter the quantity for purchase" << en;
                cin >> qty;
                if (qty > qtyAvailable[subch - 1])
                {
                    cout << qty << " Units are not in stock. Please enter value within Available quantity." << en;
                    goto selectQty11;
                }
                else if (qty <= 0)
                {
                    cout << "Please enter appropriate value as quantity.\n"
                         << en;
                    goto selectQty11;
                }
                else
                {
                    cart.pb({subch + 10, qty});
                    cout << "ITEM SUCCESSFULLY ADDED! Continue Shopping!\n"
                         << en;
                    qtyAvailable[subch - 1] -= qty;
                }
            }
            else
            {
                cout << "Sorry! Invalid Item number. Please select item again" << en;
                goto wrongGroc1;
            }

            break;
        }
        case 2:
        {
        wrongGroc2:
            cout << "\nITEM NO.\tITEM NAME\t\tQUANTITY AVAILABLE\tPRICE" << en;
            for (int i = 3; i < 6; i++)
            {
                cout << i - 2 << "\t\t" << productDetails[i + 9].second.first
                     << "\t" << qtyAvailable[i] << "\t\t\t" << itemPrices[i] << en;
            }
        repeatDetails5:
            cout << "\nDo you want to view the Item Description Too?\n Press 1 for Yes. 0 for No: ";
            int detailsNeeded;
            cin >> detailsNeeded;
            if (detailsNeeded == 1)
            {
                cout << "\nITEM NO.\tITEM NAME\t\tQUANTITY AVAILABLE\tPRICE\tDESCRIPTION" << en;
                for (int i = 3; i < 6; i++)
                {
                    cout << i - 2 << "\t\t" << productDetails[i + 9].second.first << "\t" << qtyAvailable[i] << "\t\t\t" << itemPrices[i] << "\t" << itemDetails[i] << en;
                }
            }
            else if (detailsNeeded != 0)
            {
                cout << "Incorrect Input entered.Please Try Again!" << en;
                goto repeatDetails5;
            }
            int subch;
            cout << "Enter item which you want to add to cart" << en;
            cin >> subch;
            if (subch == 1 || subch == 2 || subch == 3)
            {
                int itemAlreadyExists = 0;
                for (auto item : cart)
                {
                    int pid = item.first;
                    if (pid == subch + 13)
                    {
                        itemAlreadyExists = 1;
                        break;
                    }
                }
                if (itemAlreadyExists)
                {
                    cout << "Item has already been added to your cart! Continue Shopping for Other Products!" << en;
                    break;
                }

                if (qtyAvailable[subch - 1 + 3] == 0)
                {
                    cout << "Sorry. This item is out of stock. Please select another item" << en;
                    break;
                }
            selectQty12:
                int qty;
                cout << "Enter the quantity for purchase" << en;
                cin >> qty;
                if (qty > qtyAvailable[subch - 1 + 3])
                {
                    cout << qty << " Units are not in stock. Please enter value within Available quantity." << en;
                    goto selectQty12;
                }
                else if (qty <= 0)
                {
                    cout << "Please enter appropriate value as quantity.\n"
                         << en;
                    goto selectQty12;
                }
                else
                {
                    cart.pb({subch + 13, qty});
                    cout << "ITEM SUCCESSFULLY ADDED! Continue Shopping!\n"
                         << en;
                    qtyAvailable[subch - 1 + 3] -= qty;
                }
            }
            else
            {
                cout << "Sorry! Invalid Item number. Please select item again" << en;
                goto wrongGroc2;
            }
            break;
        }
        case 3:
        {

        wrongGroc3:
            cout << "\nITEM NO.\tITEM NAME\t\tQUANTITY AVAILABLE\tPRICE" << en;
            for (int i = 6; i < 9; i++)
            {
                cout << i - 5 << "\t\t" << productDetails[i + 9].second.first
                     << "\t" << qtyAvailable[i] << "\t\t\t" << itemPrices[i] << en;
            }
        repeatDetails6:
            cout << "\nDo you want to view the Item Description Too?\n Press 1 for Yes. 0 for No: ";
            int detailsNeeded;
            cin >> detailsNeeded;
            if (detailsNeeded == 1)
            {
                cout << "\nITEM NO.\tITEM NAME\t\tQUANTITY AVAILABLE\tPRICE\tDESCRIPTION" << en;
                for (int i = 6; i < 9; i++)
                {
                    cout << i - 5 << "\t\t" << productDetails[i + 9].second.first << "\t" << qtyAvailable[i] << "\t\t\t" << itemPrices[i] << "\t" << itemDetails[i] << en;
                }
            }
            else if (detailsNeeded != 0)
            {
                cout << "Incorrect Input entered.Please Try Again!" << en;
                goto repeatDetails6;
            }
            cout << "Enter item which you want to add to cart" << en;
            int subch;
            cin >> subch;
            if (subch == 1 || subch == 2 || subch == 3)
            {
                int itemAlreadyExists = 0;
                for (auto item : cart)
                {
                    int pid = item.first;
                    if (pid == subch + 16)
                    {
                        itemAlreadyExists = 1;
                        break;
                    }
                }
                if (itemAlreadyExists)
                {
                    cout << "Item has already been added to your cart! Continue Shopping for Other Products!" << en;
                    break;
                }
                if (qtyAvailable[subch - 1 + 6] == 0)
                {
                    cout << "Sorry. This item is out of stock. Please select another item" << en;
                    break;
                }
            selectQty13:
                int qty;
                cout << "Enter the quantity for purchase" << en;
                cin >> qty;
                if (qty > qtyAvailable[subch - 1 + 6])
                {
                    cout << qty << " Units are not in stock. Please enter value within Available quantity." << en;
                    goto selectQty13;
                }
                else if (qty <= 0)
                {
                    cout << "Please enter appropriate value as quantity.\n"
                         << en;
                    goto selectQty13;
                }
                else
                {
                    cart.pb({subch + 16, qty});
                    cout << "ITEM SUCCESSFULLY ADDED! Continue Shopping!\n"
                         << en;
                    qtyAvailable[subch - 1 + 6] -= qty;
                }
            }
            else
            {
                cout << "Sorry! Invalid Item number. Please select item again" << en;
                goto wrongGroc3;
            }
            break;
        }
        default:
        {
            error = 1;
            cout << "Sorry! Invalid Sub-Category number. Please select desired Sub-Category again" << en;
            break;
        }
        }

        if (error)
            continue;

        for (int i = 9; i < 18; i++)
        {
            productPriceQty[i].second.second = qtyAvailable[i - 9];
        }
        ofstream fout;
        fout.open("priceQtyDetails.txt", ios_base::out);
        for (auto v : productPriceQty)
        {
            fout << v.first << en;
            fout << v.second.first << en;
            fout << v.second.second << en;
        }
        fout.close();

        int groc;
        cout << "\nDo you want to Continue Shopping? Press 1 for Yes, 0 for No" << en;
        cin >> groc;
        return groc;
    }
}

int stationery()
{

    cout << "EASYBUY BOOKS & STATIONERY:" << en;
    while (true)
    {
        int ch;
        cout << "1. Fiction" << en;
        cout << "2. Non-Fiction" << en;
        cout << "3. Stationery" << en;
        cout << "Enter desired sub-category: ";
        cin >> ch;
        int error = 0; // to check for invalid input
        vector<int> qtyAvailable;
        vector<float> itemPrices;
        vector<string> itemDetails;
        for (int i = 18; i < 27; i++)
        {
            qtyAvailable.pb(productPriceQty[i].second.second);
            itemPrices.pb(productPriceQty[i].second.first);
            itemDetails.pb(productDetails[i].second.second);
        }
        switch (ch)
        {
        case 1:
        {
        wrongStat1:
            cout << "\nITEM NO.\tITEM NAME\t\tQUANTITY AVAILABLE\tPRICE" << en;
            for (int i = 0; i < 3; i++)
            {
                cout << i + 1 << "\t\t" << productDetails[i + 18].second.first
                     << "\t" << qtyAvailable[i] << "\t\t\t" << itemPrices[i] << en;
            }
        repeatDetails7:
            cout << "\nDo you want to view the Item Description Too?\n Press 1 for Yes. 0 for No: ";
            int detailsNeeded;
            cin >> detailsNeeded;
            if (detailsNeeded == 1)
            {
                cout << "\nITEM NO.\tITEM NAME\t\tQUANTITY AVAILABLE\tPRICE\tDESCRIPTION" << en;
                for (int i = 0; i < 3; i++)
                {
                    cout << i + 1 << "\t\t" << productDetails[i + 18].second.first << "\t" << qtyAvailable[i] << "\t\t\t" << itemPrices[i] << "\t" << itemDetails[i] << en;
                }
            }
            else if (detailsNeeded != 0)
            {
                cout << "Incorrect Input entered.Please Try Again!" << en;
                goto repeatDetails7;
            }
            int subch;
            cout << "Enter the desired item number for purchase" << en;
            cin >> subch;
            if (subch == 1 || subch == 2 || subch == 3)
            {
                int itemAlreadyExists = 0;
                for (auto item : cart)
                {
                    int pid = item.first;
                    if (pid == subch + 20)
                    {
                        itemAlreadyExists = 1;
                        break;
                    }
                }
                if (itemAlreadyExists)
                {
                    cout << "Item has already been added to your cart! Continue Shopping for Other Products!" << en;
                    break;
                }
                if (qtyAvailable[subch - 1] == 0)
                {
                    cout << "Sorry. This item is out of stock. Please select another item" << en;
                    break;
                }
            selectQty111:
                int qty;
                cout << "Enter the quantity for purchase" << en;
                cin >> qty;
                if (qty > qtyAvailable[subch - 1])
                {
                    cout << qty << " units are not in stock. Please enter value within Available quantity." << en;
                    goto selectQty111;
                }
                else if (qty <= 0)
                {
                    cout << "Please enter appropriate value as quantity.\n"
                         << en;
                    goto selectQty111;
                }
                else
                {
                    cart.pb({subch + 20, qty});
                    cout << "ITEM SUCCESSFULLY ADDED!" << en;
                    qtyAvailable[subch - 1] -= qty;
                }
            }
            else
            {
                cout << "Sorry! Invalid Item number. Please select item again" << en;
                goto wrongStat1;
            }

            break;
        }
        case 2:
        {
        wrongStat2:
            cout << "\nITEM NO.\tITEM NAME\t\tQUANTITY AVAILABLE\tPRICE" << en;
            for (int i = 3; i < 6; i++)
            {
                cout << i - 2 << "\t\t" << productDetails[i + 18].second.first
                     << "\t" << qtyAvailable[i] << "\t\t\t" << itemPrices[i] << en;
            }
        repeatDetails8:
            cout << "\nDo you want to view the Item Description Too?\n Press 1 for Yes. 0 for No: ";
            int detailsNeeded;
            cin >> detailsNeeded;
            if (detailsNeeded == 1)
            {
                cout << "\nITEM NO.\tITEM NAME\t\tQUANTITY AVAILABLE\tPRICE\tDESCRIPTION" << en;
                for (int i = 3; i < 6; i++)
                {
                    cout << i - 2 << "\t\t" << productDetails[i + 18].second.first << "\t" << qtyAvailable[i] << "\t\t\t" << itemPrices[i] << "\t" << itemDetails[i] << en;
                }
            }
            else if (detailsNeeded != 0)
            {
                cout << "Incorrect Input entered.Please Try Again!" << en;
                goto repeatDetails8;
            }
            int subch;
            cout << "Enter item which you want to add to cart" << en;
            cin >> subch;
            if (subch == 1 || subch == 2 || subch == 3)
            {
                int itemAlreadyExists = 0;
                for (auto item : cart)
                {
                    int pid = item.first;
                    if (pid == subch + 23)
                    {
                        itemAlreadyExists = 1;
                        break;
                    }
                }
                if (itemAlreadyExists)
                {
                    cout << "Item has already been added to your cart! Continue Shopping for Other Products!" << en;
                    break;
                }
                if (qtyAvailable[subch - 1 + 3] == 0)
                {
                    cout << "Sorry. This item is out of stock. Please select another item" << en;
                    break;
                }
            selectQty222:
                int qty;
                cout << "Enter the quantity for purchase" << en;
                cin >> qty;
                if (qty > qtyAvailable[subch - 1 + 3])
                {
                    cout << qty << " units are not in stock. Please enter value within Available quantity." << en;
                    goto selectQty222;
                }
                else if (qty <= 0)
                {
                    cout << "Please enter appropriate value as quantity.\n"
                         << en;
                    goto selectQty222;
                }
                else
                {
                    cart.pb({subch + 23, qty});
                    cout << "ITEM SUCCESSFULLY ADDED!" << en;
                    qtyAvailable[subch - 1 + 3] -= qty;
                }
            }
            else
            {
                cout << "Sorry! Invalid Item number. Please select item again" << en;
                goto wrongStat2;
            }
            break;
        }
        case 3:
        {
        wrongStat3:
            cout << "\nITEM NO.\tITEM NAME\t\tQUANTITY AVAILABLE\tPRICE" << en;
            for (int i = 6; i < 9; i++)
            {
                cout << i - 5 << "\t\t" << productDetails[i + 18].second.first
                     << "\t" << qtyAvailable[i] << "\t\t\t" << itemPrices[i] << en;
            }
        repeatDetails9:
            cout << "\nDo you want to view the Item Description Too?\n Press 1 for Yes. 0 for No: ";
            int detailsNeeded;
            cin >> detailsNeeded;
            if (detailsNeeded == 1)
            {
                cout << "\nITEM NO.\tITEM NAME\t\tQUANTITY AVAILABLE\tPRICE\tDESCRIPTION" << en;
                for (int i = 6; i < 9; i++)
                {
                    cout << i - 5 << "\t\t" << productDetails[i + 18].second.first << "\t" << qtyAvailable[i] << "\t\t\t" << itemPrices[i] << "\t" << itemDetails[i] << en;
                }
            }
            else if (detailsNeeded != 0)
            {
                cout << "Incorrect Input entered.Please Try Again!" << en;
                goto repeatDetails9;
            }
            cout << "Enter item which you want to add to cart" << en;
            int subch;
            cin >> subch;
            if (subch == 1 || subch == 2 || subch == 3)
            {
                int itemAlreadyExists = 0;
                for (auto item : cart)
                {
                    int pid = item.first;
                    if (pid == subch + 26)
                    {
                        itemAlreadyExists = 1;
                        break;
                    }
                }
                if (itemAlreadyExists)
                {
                    cout << "Item has already been added to your cart! Continue Shopping for Other Products!" << en;
                    break;
                }
                if (qtyAvailable[subch - 1 + 6] == 0)
                {
                    cout << "Sorry. This item is out of stock. Please select another item" << en;
                    break;
                }
            selectQty333:
                int qty;
                cout << "Enter the quantity for purchase" << en;
                cin >> qty;
                if (qty > qtyAvailable[subch - 1 + 6])
                {
                    cout << qty << " Units are not in stock. Please enter value within Available quantity." << en;
                    goto selectQty333;
                }
                else if (qty <= 0)
                {
                    cout << "Please enter appropriate value as quantity.\n"
                         << en;
                    goto selectQty333;
                }
                else
                {
                    cart.pb({subch + 26, qty});
                    cout << "ITEM SUCCESSFULLY ADDED!" << en;
                    qtyAvailable[subch - 1 + 6] -= qty;
                }
            }
            else
            {
                cout << "Sorry! Invalid Item number. Please select item again" << en;
                goto wrongStat3;
            }
            break;
        }
        default:
        {
            error = 1;
            cout << "Sorry! Invalid Sub-Category number. Please select desired Sub-Category again" << en;
            break;
        }
        }

        if (error)
            continue;

        for (int i = 18; i < 27; i++)
        {
            productPriceQty[i].second.second = qtyAvailable[i - 18];
        }
        ofstream fout;
        fout.open("priceQtyDetails.txt", ios_base::out);
        for (auto v : productPriceQty)
        {
            fout << v.first << en;
            fout << v.second.first << en;
            fout << v.second.second << en;
        }
        fout.close();

        int stachoice;
        cout << "\nDo you want to Continue Shopping? Press 1 for Yes, 0 for No" << en;
        cin >> stachoice;
        return stachoice;
    }
}

int fashion()
{
    cout << "\nEASYBUY FASHION:" << en;
    while (true)
    {
        int ch;
        cout << "1.Mens wear" << en;
        cout << "2.Womens wear" << en;
        cout << "3.Bags and luggages" << en;
        cout << "Enter desired sub-category: ";
        cin >> ch;
        int error = 0;
        vector<int> qtyAvailable;
        vector<float> itemPrices;
        vector<string> itemDetails;
        for (int i = 27; i < 36; i++)
        {
            qtyAvailable.pb(productPriceQty[i].second.second);
            itemPrices.pb(productPriceQty[i].second.first);
            itemDetails.pb(productDetails[i].second.second);
        }
        switch (ch)
        {
        case 1:
        {
        wrongElec1f:
            cout << "\nITEM NO.\tITEM NAME\t\tQUANTITY AVAILABLE\tPRICE" << en;
            for (int i = 0; i < 3; i++)
            {
                cout << i + 1 << "\t\t" << productDetails[i + 27].second.first
                     << "\t" << qtyAvailable[i] << "\t\t\t" << itemPrices[i] << en;
            }
        repeatDetails11:
            cout << "\nDo you want to view the Item Description Too?\n Press 1 for Yes. 0 for No: ";
            int detailsNeeded;
            cin >> detailsNeeded;
            if (detailsNeeded == 1)
            {
                cout << "\nITEM NO.\tITEM NAME\t\tQUANTITY AVAILABLE\tPRICE\tDESCRIPTION" << en;
                for (int i = 0; i < 3; i++)
                {
                    cout << i + 1 << "\t\t" << productDetails[i + 27].second.first << "\t" << qtyAvailable[i] << "\t\t\t" << itemPrices[i] << "\t" << itemDetails[i] << en;
                }
            }
            else if (detailsNeeded != 0)
            {
                cout << "Incorrect Input entered.Please Try Again!" << en;
                goto repeatDetails11;
            }
            int subch;
            cout << "Enter the desired item number for purchase" << en;
            cin >> subch;
            if (subch == 1 || subch == 2 || subch == 3)
            {
                int itemAlreadyExists = 0;
                for (auto item : cart)
                {
                    int pid = item.first;
                    if (pid == subch + 30)
                    {
                        itemAlreadyExists = 1;
                        break;
                    }
                }
                if (itemAlreadyExists)
                {
                    cout << "Item has already been added to your cart! Continue Shopping for Other Products!" << en;
                    break;
                }
                if (qtyAvailable[subch - 1] == 0)
                {
                    cout << "Sorry. This item is out of stock. Please select another item" << en;
                    break;
                }
            selectQty1f:
                int qty;
                cout << "Enter the quantity for purchase" << en;
                cin >> qty;
                if (qty > qtyAvailable[subch - 1])
                {
                    cout << qty << " Units are not in stock. Please enter value within Available quantity.\n"
                         << en;
                    goto selectQty1f;
                }
                else if (qty <= 0)
                {
                    cout << "Please enter appropriate value as quantity.\n"
                         << en;
                    goto selectQty1f;
                }
                else
                {

                    cart.pb({subch + 30, qty});
                    cout << "ITEM SUCCESSFULLY ADDED! Continue Shopping!\n"
                         << en;
                    qtyAvailable[subch - 1] -= qty;
                }
            }
            else
            {
                cout << "Sorry! Invalid Item number. Please select item again\n"
                     << en;
                goto wrongElec1f;
            }
        }
        break;
        case 2:
        {
        wrongElec2f:
            cout << "\nITEM NO.\tITEM NAME\t\tQUANTITY AVAILABLE\tPRICE" << en;
            for (int i = 3; i < 6; i++)
            {
                cout << i - 2 << "\t\t" << productDetails[i + 27].second.first
                     << "\t" << qtyAvailable[i] << "\t\t\t" << itemPrices[i] << en;
            }
        repeatDetails12:
            cout << "\nDo you want to view the Item Description Too?\n Press 1 for Yes. 0 for No: ";
            int detailsNeeded;
            cin >> detailsNeeded;
            if (detailsNeeded == 1)
            {
                cout << "\nITEM NO.\tITEM NAME\t\tQUANTITY AVAILABLE\tPRICE\tDESCRIPTION" << en;
                for (int i = 3; i < 6; i++)
                {
                    cout << i - 2 << "\t\t" << productDetails[i + 27].second.first << "\t" << qtyAvailable[i] << "\t\t\t" << itemPrices[i] << "\t" << itemDetails[i] << en;
                }
            }
            else if (detailsNeeded != 0)
            {
                cout << "Incorrect Input entered.Please Try Again!" << en;
                goto repeatDetails12;
            }
            int subch;
            cout << "Enter item which you want to add to cart" << en;
            cin >> subch;
            if (subch == 1 || subch == 2 || subch == 3)
            {
                int itemAlreadyExists = 0;
                for (auto item : cart)
                {
                    int pid = item.first;
                    if (pid == subch + 33)
                    {
                        itemAlreadyExists = 1;
                        break;
                    }
                }
                if (itemAlreadyExists)
                {
                    cout << "Item has already been added to your cart! Continue Shopping for Other Products!" << en;
                    break;
                }
                if (qtyAvailable[subch - 1 + 3] == 0)
                {
                    cout << "Sorry. This item is out of stock. Please select another item" << en;
                    break;
                }
            selectQty2f:
                int qty;
                cout << "Enter the quantity for purchase" << en;
                cin >> qty;
                if (qty > qtyAvailable[subch - 1 + 3])
                {
                    cout << qty << " Units are not in stock. Please enter value within Available quantity." << en;
                    goto selectQty2f;
                }
                else if (qty <= 0)
                {
                    cout << "Please enter appropriate value as quantity.\n"
                         << en;
                    goto selectQty2f;
                }
                else
                {

                    cart.pb({subch + 33, qty});
                    cout << "ITEM SUCCESSFULLY ADDED! Continue Shopping!\n"
                         << en;
                    qtyAvailable[subch - 1 + 3] -= qty;
                }
            }
            else
            {
                cout << "Sorry! Invalid Item number. Please select item again\n"
                     << en;
                goto wrongElec2f;
            }
            break;
        }
        case 3:
        {
        wrongElec3f:
            cout << "\nITEM NO.\tITEM NAME\t\tQUANTITY AVAILABLE\tPRICE" << en;
            for (int i = 6; i < 9; i++)
            {
                cout << i - 5 << "\t\t" << productDetails[i + 27].second.first
                     << "\t" << qtyAvailable[i] << "\t\t\t" << itemPrices[i] << en;
            }
        repeatDetails13:
            cout << "\nDo you want to view the Item Description Too?\n Press 1 for Yes. 0 for No: ";
            int detailsNeeded;
            cin >> detailsNeeded;
            if (detailsNeeded == 1)
            {
                cout << "\nITEM NO.\tITEM NAME\t\tQUANTITY AVAILABLE\tPRICE\tDESCRIPTION" << en;
                for (int i = 6; i < 9; i++)
                {
                    cout << i - 5 << "\t\t" << productDetails[i + 27].second.first << "\t" << qtyAvailable[i] << "\t\t\t" << itemPrices[i] << "\t" << itemDetails[i] << en;
                }
            }
            else if (detailsNeeded != 0)
            {
                cout << "Incorrect Input entered.Please Try Again!" << en;
                goto repeatDetails13;
            }
            cout << "Enter item which you want to add to cart" << en;
            int subch;
            cin >> subch;
            if (subch == 1 || subch == 2 || subch == 3)
            {
                int itemAlreadyExists = 0;
                for (auto item : cart)
                {
                    int pid = item.first;
                    if (pid == subch + 36)
                    {
                        itemAlreadyExists = 1;
                        break;
                    }
                }
                if (itemAlreadyExists)
                {
                    cout << "Item has already been added to your cart! Continue Shopping for Other Products!" << en;
                    break;
                }
                if (qtyAvailable[subch - 1 + 6] == 0)
                {
                    cout << "Sorry. This item is out of stock. Please select another item" << en;
                    break;
                }
            selectQty3f:
                int qty;
                cout << "Enter the quantity for purchase" << en;
                cin >> qty;
                if (qty > qtyAvailable[subch - 1 + 6])
                {
                    cout << qty << " Units are not in stock. Please enter value within Available quantity." << en;
                    goto selectQty3f;
                }
                else if (qty <= 0)
                {
                    cout << "Please enter appropriate value as quantity.\n"
                         << en;
                    goto selectQty3f;
                }
                else
                {

                    cart.pb({subch + 36, qty});
                    cout << "ITEM SUCCESSFULLY ADDED! Continue Shopping!\n"
                         << en;
                    qtyAvailable[subch - 1 + 6] -= qty;
                }
            }
            else
            {
                cout << "Sorry! Invalid Item number. Please select item again\n"
                     << en;
                goto wrongElec3f;
            }
            break;
        }
        default:
        {
            error = 1;
            cout << "Sorry! Invalid Category selected. Please select desired Category again\n"
                 << en;
            break;
        }
        }

        if (error == 1)
            continue;

        for (int i = 27; i < 36; i++)
        {
            productPriceQty[i].second.second = qtyAvailable[i - 27];
        }
        ofstream fout;
        fout.open("priceQtyDetails.txt", ios_base::out);
        for (auto v : productPriceQty)
        {
            fout << v.first << en;
            fout << v.second.first << en;
            fout << v.second.second << en;
        }
        fout.close();

        int elech;
        cout << "\nDo you want to Continue Shopping? Press 1 for Yes, 0 for No" << en;
        cin >> elech;
        return elech;
    }
}

// The following function fetches the product details like product id,name and description from the file "productDetails.txt" where all these
// details are already stored
vector<pair<int, pair<string, string>>> getProductDetails()
{
    vector<pair<int, pair<string, string>>> p;
    ifstream fin;
    fin.open("productDetails.txt", ios_base::in);
    if (fin.is_open())
    {
        int id;
        string s1, s2;
        for (int i = 0; i < 36; i++)
        {
            fin >> id;
            getline(fin, s1); // to remove newline
            getline(fin, s1);
            getline(fin, s2);
            p.push_back(make_pair(id, make_pair(s1, s2)));
        }
        fin.close();
    }
    return p;
}

// The following function fetches the product details like product id,price and quantity from the file "priceQtyDetails.txt" where all these
// details are already stored
vector<pair<int, pair<float, int>>> getProductPriceQty()
{
    vector<pair<int, pair<float, int>>> p;
    ifstream fin;
    fin.open("priceQtyDetails.txt", ios_base::in);
    if (fin.is_open())
    {
        int id;
        float pr;
        int qty;
        string buffer;
        for (int i = 0; i < 36; i++)
        {
            fin >> id;
            getline(fin, buffer); // to remove newline
            fin >> pr;
            getline(fin, buffer); // to remove newline
            fin >> qty;
            getline(fin, buffer); // to remove newline

            p.push_back(make_pair(id, make_pair(pr, qty)));
        }
        fin.close();
    }
    return p;
}

int main()
{

    cout << "\tWelcome To EasyBuy - Your One Stop Destination For Online Shopping" << en << en;
    string username, pass;
    int loginSuccessful = 0;
    while (true) // loop for login/signup
    {
        int ch = welcome();
        // It stores the value returned from welcome based on login or signup as chosen by the user
        int flag = 0;
        switch (ch)
        {
        case 1:
        {
            cout << "\t\t\t    USER LOGIN" << en << en;
            cout << "\tEnter your username: ";
            cin >> username;
            cout << "\tEnter your password: ";
            cin >> pass;
            if (login(username, pass))
            {
                cout << "\n\tLogged in Successfully" << en << en;
                loginSuccessful = 1;
            }
            else
            {
                cout << "\n\tLogin failed" << en << en;
                flag = 1;
            }
            break;
        }
        case 2:
        {

            signUp();
            cout << "\n\tRegistered Successfully! Login to Start Shopping!\n"
                 << en;
            flag = 1;
            break;
        }
        case 3:
        {
            // int ch1 = dashboard();
            break;
        }
        default:
        {
            cout << "\n\tInvalid Input. Please Try Again!\n"
                 << en;
            // The user has chosen a value apart from signup or login
            flag = 1;
        }
        }
        if (flag)
            continue;
        else
            break;
        // If the user has pressed an invalid number then it goes back to start
    }

    productDetails = getProductDetails();
    productPriceQty = getProductPriceQty();

    if (loginSuccessful || !loginSuccessful)
    {
    repeatDashboard:
        int ch = dashboard(); // dashboard function displays the category of items available
        switch (ch)
        {
        case 1:
        {
            int continueShopping = electronics();
            if (continueShopping)
                goto repeatDashboard;
        }
        break;
        case 2:
        {
            int continueShopping = grocery();
            if (continueShopping)
                goto repeatDashboard;
        }
        break;
        case 3:
        {
            int continueShopping = fashion();
            if (continueShopping)
                goto repeatDashboard;
        }
        break;
        case 4:
        {
            int continueShopping = stationery();
            if (continueShopping)
                goto repeatDashboard;
        }
        break;
        default:
        {
            cout << "\nInvalid Category Selected. Make your Selection again" << en << en;
            goto repeatDashboard;
            break;
        }
        }
    showCart:
        cout << "\n\t\t\t\tMy Cart" << en << en;
        cout << "Sl.No\tProduct Name\t\t\tPrice\t\tQuantity Selected" << en << en;
        int i = 1;
        for (auto item : cart)
        {
            int pid = item.first;
            int qty = item.second;
            if (pid <= 10)
                cout << i << "\t" << productDetails[pid - 1].second.first << "\t\t" << productPriceQty[pid - 1].second.first << "\t\t" << qty << en << en;
            else if (pid <= 20)
                cout << i << "\t" << productDetails[pid - 2].second.first << "\t\t" << productPriceQty[pid - 2].second.first << "\t\t" << qty << en << en;
            else if (pid <= 30)
                cout << i << "\t" << productDetails[pid - 3].second.first << "\t\t" << productPriceQty[pid - 3].second.first << "\t\t" << qty << en << en;
            else if (pid <= 40)
                cout << i << "\t" << productDetails[pid - 4].second.first << "\t\t" << productPriceQty[pid - 4].second.first << "\t\t" << qty << en << en;
            i++;
        }
    repeatChoices:
        cout << en << "1.Add Items to Cart" << en;
        cout << "2.Remove Items from Cart" << en;
        cout << "3.Place Order" << en;
        cout << "Enter your choice: ";
        int cartch;
        cin >> cartch;
        switch (cartch)
        {
        case 1:
            goto repeatDashboard;
            break;
        case 2:
        {
            cout << "Enter the number of items you want to remove from the cart" << en;
            int n;
            cin >> n;
            cout << "Enter the Sl no's of the items you want to remove(Incorrect Item No's will be automatically ignored)" << en;
            vector<int> itemNos(n);
            for (int i = 0; i < n; i++)
            {
                cin >> itemNos[i];
                itemNos[i] = cart[itemNos[i] - 1].first;
            }
            vector<pair<int, int>> removedItems;
            for (int itemNo : itemNos)
            {
                if (itemNo == cart.front().first)
                {
                    removedItems.pb({cart[0].first, cart[0].second});
                    cart.pop_front();
                }
                else if (itemNo == cart.back().first)
                {
                    removedItems.pb({cart[cart.sz - 1].first, cart[cart.sz - 1].second});
                    cart.pop_back();
                }
                else
                {

                    for (deque<pair<int, int>>::iterator it = cart.begin(); it != cart.end(); it++)
                    {
                        if (it->first == itemNo)
                        {
                            removedItems.pb({it->first, it->second});
                            cart.erase(it);
                            break;
                        }
                    }
                }
            }
            // updating the quantities in the productPriceQty vector
            for (auto item : removedItems)
            {
                int pid = item.first;
                int qty = item.second;
                if (pid <= 10)
                {
                    productPriceQty[pid - 1].second.second += qty;
                }
                else if (pid <= 20)
                {
                    productPriceQty[pid - 2].second.second += qty;
                }
                else if (pid <= 30)
                {
                    productPriceQty[pid - 3].second.second += qty;
                }
                else if (pid <= 40)
                {
                    productPriceQty[pid - 4].second.second += qty;
                }
            }

            // updating the priceQtyDetails.txt file
            ofstream fout;
            fout.open("priceQtyDetails.txt", ios_base::out);
            for (auto v : productPriceQty)
            {
                fout << v.first << en;
                fout << v.second.first << en;
                fout << v.second.second << en;
            }
            fout.close();

            cout << "\nItems removed successfully!" << en;
            if (cart.sz == 0)
            {
                cout << "\nYour Cart is Empty! Shop for Products to Checkout!" << en << en;
                goto repeatDashboard;
            }
            goto showCart;
        }
        break;
        case 3:
        {
            cout << "Your Order Has been Placed!" << en << en;
            cout << "\t\t\tOrder Details" << en << en;
            cout << "Sl.No\tProduct Name\t\t\tPrice\t\tQuantity Selected" << en << en;
            int i = 1;
            double orderTotal = 0.0;
            for (auto item : cart)
            {

                int pid = item.first;
                int qty = item.second;
                if (pid <= 10)
                {
                    cout << i << "\t" << productDetails[pid - 1].second.first << "\t\t" << productPriceQty[pid - 1].second.first << "\t\t" << qty << en << en;
                    orderTotal += (double)productPriceQty[pid - 1].second.first * qty;
                }
                else if (pid <= 20)
                {
                    cout << i << "\t" << productDetails[pid - 2].second.first << "\t\t" << productPriceQty[pid - 2].second.first << "\t\t" << qty << en << en;
                    orderTotal += (double)productPriceQty[pid - 2].second.first * qty;
                }
                else if (pid <= 30)
                {
                    cout << i << "\t" << productDetails[pid - 3].second.first << "\t\t" << productPriceQty[pid - 3].second.first << "\t\t" << qty << en << en;
                    orderTotal += (double)productPriceQty[pid - 3].second.first * qty;
                }
                else if (pid <= 40)
                {
                    cout << i << "\t" << productDetails[pid - 4].second.first << "\t\t" << productPriceQty[pid - 4].second.first << "\t\t" << qty << en << en;
                    orderTotal += (double)productPriceQty[pid - 4].second.first * qty;
                }
                i++;
            }
            int discPercent = 0;
            if (orderTotal >= 1000000)
            {
                discPercent = 10;
            }
            else if (orderTotal >= 10000)
            {
                discPercent = 4;
            }
            else if (orderTotal >= 1000)
            {
                discPercent = 2;
            }
            double discount = orderTotal * (double)(discPercent) / 100.0;
            double finalTotal = (double)orderTotal - discount;
            cout << "Order Total: " << orderTotal << en;
            cout << "Discount( " << discPercent << "% ): " << discount << en;
            cout << "\nGRAND TOTAL: " << finalTotal << en;
            cout << en << "Your Order will be Delivered within 7 business days. You can pay by Cash/Card at the time of delivery!" << en;
            cout << "Thank You for Shopping!" << en;

        repeatLogout:
            cout << en << "Press 1 to Place Another Order. Press 2 to Close Application" << en;
            int finalch;
            cin >> finalch;
            if (finalch == 1)
            {
                cart.clear();
                goto repeatDashboard;
            }
            else if (finalch == 2)
            {
                cout << "Logging Out.." << en;
                return 0;
            }
            else
            {
                cout << "Incorrect Input. Please Try Again" << en;
                goto repeatLogout;
            }
        }
        break;
        default:
        {
            cout << "Incorrect choice entered. Please try again" << en;
            goto repeatChoices;
        }
        }
    }
    return 0;
}
