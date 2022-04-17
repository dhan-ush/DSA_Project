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

vector<pair<int, int>> cart;

void signUp()
{
    string username, pass;
    ofstream fout;
    fout.open("userdetails.txt", ios_base::app);
    if (fout.is_open())
    {
        cout << "Enter username" << en;
        cin >> username;
        cout << "Enter password" << en;
        cin >> pass;
        fout << username << "\n"
             << pass << "\n";
        fout.close();
    }
}

int login(string username, string pass)
{
    vector<pair<string, string>> mp;
    ifstream fin;
    fin.open("userdetails.txt", ios_base::in);
    int i = 0;
    if (fin.is_open())
    {
        string s1, s2;
        while (getline(fin, s1) && getline(fin, s2))
        {
            mp.push_back(make_pair(s1, s2));
        }
        fin.close();
    }
    int flag = 0, pos;
    for (auto v : mp)
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

int welcome()
{
    cout << "Press 1 to Login" << en;
    cout << "Press 2 to Sign Up" << en;
    int ch;
    cin >> ch;
    return ch;
}

int dashboard()
{
    int ch;
    cout << "CATEGORIES AVAILABLE:" << en;
    cout << "1. Electronics" << en;
    cout << "2. Grocery" << en;
    cout << "3. Fashion" << en;
    cout << "4. Stationery" << en;
    cout << "Hurry! Limited Time Offer! " << en;
    cout << "Enter the desired category of item" << en;
    cin >> ch;
    return ch;
}

int grocery()
{
    cout << "EASYBUY GROCERY:" << en;
    while (true)
    {
        int ch;
        cout << "1. Dairy Products" << en;
        cout << "2. Snacks and Beverages" << en;
        cout << "3. Body Care Products" << en;
        cout << "Enter item which you want to add to cart" << en;
        cin >> ch;
        int error = 0;
        vector<int> qtyAvailable;
        ifstream fin;
        fin.open("grocery.txt", ios_base::in);
        int i = 0;
        if (fin.is_open())
        {
            int x;
            while (fin >> x)
            {
                qtyAvailable.pb(x);
            }
            fin.close();
        }
        switch (ch)
        {
        case 1:
        {
        wrongGroc1:
            cout << "ITEM NAME\t\tQUANTITY AVAILABLE:" << en;
            cout << "1. Cottage Cheese"
                 << " " << qtyAvailable[0] << en;
            cout << "2. Milk"
                 << " " << qtyAvailable[1] << en;
            cout << "3. BUtter"
                 << " " << qtyAvailable[2] << en;
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
                    cout << qty << " Units are not in stock. Please enter value within Available quantity." << en;
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
                cout << "Sorry! Invalid Item number. Please select item again" << en;
                goto wrongGroc1;
            }

            break;
        }
        case 2:
        {
        wrongGroc2:
            cout << "ITEM NAME\t\tQUANTITY AVAILABLE:" << en;
            cout << "1. Chips"
                 << " " << qtyAvailable[3] << en;
            cout << "2. Soft-drinks"
                 << " " << qtyAvailable[4] << en;
            cout << "3. Chocolates"
                 << " " << qtyAvailable[5] << en;
            int subch;
            cout << "Enter item which you want to add to cart";
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
                else
                {
                    cart.pb({subch, qty});
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
            cout << "ITEM NAME\t\tQUANTITY AVAILABLE:" << en;
            cout << "1. Body Lotions"
                 << " " << qtyAvailable[6] << en << en;
            cout << "2. Body Oil"
                 << " " << qtyAvailable[7] << en << en;
            cout << "3. Body Powder"
                 << " " << qtyAvailable[8] << en << en;
            cout << "Enter item which you want to add to cart" << en;
            int subch;
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
                else
                {
                    cart.pb({subch, qty});
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

        ofstream fout;
        fout.open("grocery.txt", ios_base::out);
        for (auto v : qtyAvailable)
            fout << v << en;
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
        cout << "Enter item which you want to add to cart" << en;
        cin >> ch;
        int error = 0; // to check for invalid input
        vector<int> qtyAvailable;
        ifstream fin;
        fin.open("books.txt", ios_base::in);
        int i = 0;
        if (fin.is_open())
        {
            int x;
            while (fin >> x)
            {
                qtyAvailable.pb(x);
            }
            fin.close();
        }
        switch (ch)
        {
        case 1:
        {
        wrongStat1:
            cout << "ITEM NAME\t\tQUANTITY AVAILABLE:" << en;
            cout << "1. The Blue Umbrella - By Ruskin Bond"
                 << "\t" << qtyAvailable[0] << en;
            cout << "2. One  Indian Girl - By Chetan Bhagat"
                 << "\t" << qtyAvailable[1] << en;
            cout << "3. Death on the Nile - By Christie Agatha"
                 << "\t" << qtyAvailable[2] << en;
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
            cout << "ITEM NAME\t\tQUANTITY AVAILABLE:" << en;
            cout << "1. Ignited minds- By A.P.J. Abdul Kalam"
                 << "\t" << qtyAvailable[3] << en;
            cout << "2. Three Thousand Stitches - By Sudha Murthy"
                 << "\t" << qtyAvailable[4] << en;
            cout << "3. The Diary Of A Young Girl - By Anne Frank"
                 << "\t" << qtyAvailable[5] << en;
            int subch;
            cout << "Enter item which you want to add to cart";
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
            cout << "ITEM NAME\t\tQUANTITY AVAILABLE:" << en;
            cout << "1. "
                 << "\t" << qtyAvailable[6] << en << en;
            cout << "2. "
                 << "\t" << qtyAvailable[7] << en << en;
            cout << "3. "
                 << "\t" << qtyAvailable[8] << en << en;
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

        ofstream fout;
        fout.open("electronics.txt", ios_base::out);
        for (auto v : qtyAvailable)
            fout << v << en;
        fout.close();

        int stachoice;
        cout << "\nDo you want to Continue Shopping? Press 1 for Yes, 0 for No" << en;
        cin >> stachoice;
        return stachoice;
    }
}

int electronics()
{

    cout << "EASYBUY ELECTRONICS:" << en;
    while (true)
    {
        int ch;
        cout << "1. Mobiles" << en;
        cout << "2. Laptops" << en;
        cout << "3. Accesories" << en;
        cout << "Enter item which you want to add to cart" << en;
        cin >> ch;
        int error = 0;
        vector<int> qtyAvailable;
        ifstream fin;
        fin.open("electronics.txt", ios_base::in);
        int i = 0;
        if (fin.is_open())
        {
            int x;
            while (fin >> x)
            {
                qtyAvailable.pb(x);
            }
            fin.close();
        }
        switch (ch)
        {
        case 1:
        {
        wrongElec1:
            cout << "ITEM NAME\t\t\tQUANTITY AVAILABLE:" << en;
            cout << "1. Samsung Galaxy Note 11"
                 << "\t" << qtyAvailable[0] << en;
            cout << "2. Apple iPhone 13 Pro"
                 << "\t\t" << qtyAvailable[1] << en;
            cout << "3. Google Pixel 4a "
                 << "\t\t" << qtyAvailable[2] << en;
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
            cout << "ITEM NAME\t\tQUANTITY AVAILABLE:" << en;
            cout << "1. Hp"
                 << " " << qtyAvailable[3] << en;
            cout << "2. Asus"
                 << " " << qtyAvailable[4] << en;
            cout << "3. Lenovo"
                 << " " << qtyAvailable[5] << en;
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
            cout << "ITEM NAME\t\tQUANTITY AVAILABLE:" << en;
            cout << "1. Laptop Charger"
                 << " " << qtyAvailable[6] << en << en;
            cout << "2. Mobile Charger"
                 << " " << qtyAvailable[7] << en << en;
            cout << "3. Headphone"
                 << " " << qtyAvailable[8] << en << en;
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

        ofstream fout;
        fout.open("electronics.txt", ios_base::out);
        for (auto v : qtyAvailable)
            fout << v << en;
        fout.close();

        int elech;
        cout << "\nDo you want to Continue Shopping? Press 1 for Yes, 0 for No" << en;
        cin >> elech;
        return elech;
    }
}

int fashion()
{
    cout << "EASYBUY FASHION:" << en;
    while (true)
    {
        int ch;
        cout << "1.Mens wear" << en;
        cout << "2.Womens wear" << en;
        cout << "3.Bags and luggages" << en;
        cout << "Enter item which you want to add to cart" << en;
        cin >> ch;
        int error = 0;
        vector<int> qtyAvailable;
        ifstream fin;
        fin.open("fashion.txt", ios_base::in);
        int i = 0;
        if (fin.is_open())
        {
            int x;
            while (fin >> x)
            {
                qtyAvailable.pb(x);
            }
            fin.close();
        }
        switch (ch)
        {
        case 1:
        {
        wrongElec1f:
            cout << "ITEM NAME\t\t\tQUANTITY AVAILABLE:" << en;
            cout << "1. T shirt"
                 << "\t" << qtyAvailable[0] << en;
            cout << "2. Jeans"
                 << "\t\t" << qtyAvailable[1] << en;
            cout << "3. Shorts "
                 << "\t\t" << qtyAvailable[2] << en;
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
            cout << "ITEM NAME\t\tQUANTITY AVAILABLE:" << en;
            cout << "1.Sarees"
                 << " " << qtyAvailable[3] << en;
            cout << "2.Dress Material"
                 << " " << qtyAvailable[4] << en;
            cout << "3.Salvars"
                 << " " << qtyAvailable[5] << en;
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
            cout << "ITEM NAME\t\tQUANTITY AVAILABLE:" << en;
            cout << "1.Briefcases"
                 << " " << qtyAvailable[6] << en << en;
            cout << "2.Waistbags"
                 << " " << qtyAvailable[7] << en << en;
            cout << "3.Travel bags"
                 << " " << qtyAvailable[8] << en << en;
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

        ofstream fout;
        fout.open("fashion.txt", ios_base::out);
        for (auto v : qtyAvailable)
            fout << v << en;
        fout.close();

        int elech;
        cout << "\nDo you want to Continue Shopping? Press 1 for Yes, 0 for No" << en;
        cin >> elech;
        return elech;
    }
}

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
            cout << id << en << s1 << en << s2 << en;
            p.push_back(make_pair(id, make_pair(s1, s2)));
        }
        fin.close();
    }
    return p;
}
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
            cout << id << en << pr << en << qty << en;
            p.push_back(make_pair(id, make_pair(pr, qty)));
        }
        fin.close();
    }
    return p;
}

int main()
{
    cout << "Welcome To EasyBuy - Your One Stop Destination " << en;
    string username, pass;
    int loginSuccessful = 0;
    while (true) // loop for login/signup
    {
        int ch = welcome();
        int flag = 0;
        switch (ch)
        {
        case 1:
        {
            cout << "Enter username" << en;
            cin >> username;
            cout << "Enter password" << en;
            cin >> pass;
            if (login(username, pass))
            {
                cout << "Logged in Successfully" << en;
                loginSuccessful = 1;
            }
            else
            {
                cout << "Login failed" << en;
                flag = 1;
            }
            break;
        }
        case 2:
        {

            signUp();
            cout << "Registered Successfully" << en;
            flag = 1;
            break;
        }
        default:
        {
            cout << "\nInvalid Input\n"
                 << en;
            flag = 1;
        }
        }
        if (flag)
            continue;
        else
            break;
    }

    vector<pair<int, pair<string, string>>> productDetails = getProductDetails();
    vector<pair<int, pair<float, int>>> productPriceQty = getProductPriceQty();

    if (loginSuccessful)
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
        cout << "\n\t\t\t\tMy Cart"<<en<<en;
        cout<<"Sl.No\tProduct Name\t\t\tPrice\t\tQuantity Selected"<<en<<en;
        int i=1;
        for(auto item:cart)
        {
            int pid=item.first;
            if(i<=10)
            cout<<i<<"\t"<<productDetails[pid-1].second.first<<"\t\t"<<productPriceQty[pid-1].second.first<<"\t\t"<<productPriceQty[pid-1].second.second<<en<<en;
            else if(i<=20)
            cout<<i<<"\t"<<productDetails[pid-2].second.first<<"\t\t"<<productPriceQty[pid-2].second.first<<"\t\t"<<productPriceQty[pid-2].second.second<<en<<en;
            else if(i<=30)
            cout<<i<<"\t"<<productDetails[pid-3].second.first<<"\t\t"<<productPriceQty[pid-3].second.first<<"\t\t"<<productPriceQty[pid-3].second.second<<en<<en;
            else if(i<=40)
            cout<<i<<"\t"<<productDetails[pid-4].second.first<<"\t\t"<<productPriceQty[pid-4].second.first<<"\t\t"<<productPriceQty[pid-4].second.second<<en<<en;
            i++;
        }

    }
}
