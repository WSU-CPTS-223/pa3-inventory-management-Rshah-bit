#include "inventorylist.hpp"
#include <sstream>

InventoryT inv;

void printHelp()
{
    cout << "Supported list of commands: " << endl;
    cout << " 1. find <inventoryid> - Finds if the inventory exists. If exists, prints details. If not, prints 'Inventory not found'." << endl;
    cout << " 2. listInventory <category_string> - Lists just the id and name of all inventory belonging to the specified category. If the category doesn't exists, prints 'Invalid Category'.\n"
         << endl;
    cout << " Use :quit to quit the REPL" << endl;
}

bool validCommand(string line)
{
    return (line == ":help") ||
           (line.rfind("find", 0) == 0) ||
           (line.rfind("listInventory") == 0);
}

void evalCommand(string line)
{
    if (line == ":help") {
        printHelp();
        return;
    }

    // if line starts with find
    if (line.rfind("find", 0) == 0) {
        istringstream iss(line);
        string cmd, inventoryid;
        iss >> cmd;
        if (!(iss >> inventoryid)) {
            cout << "Usage: find <inventoryid>" << endl;
        } else {
            inv.find(inventoryid);
        }
        return;
    }

    // if line starts with listInventory
    if (line.rfind("listInventory", 0) == 0) {
        string category = "";
        if (line.size() > strlen("listInventory")) {
            category = line.substr(strlen("listInventory"));
        }
        size_t p = category.find_first_not_of(' ');
        if (p != string::npos) category = category.substr(p);
        else category.clear();

        if (category.empty()) {
            cout << "Usage: listInventory <category_string>" << endl;
        } else {
            inv.listInventory(category);
        }
        return;
    }
}

void bootStrap()
{
    cout << "\n Welcome to Amazon Inventory Query System" << endl;
    cout << " enter :quit to exit. or :help to list supported commands." << endl;
    cout << "\n> ";
    // TODO: Do all your bootstrap operations here

    ifstream ifile("marketdata.csv");
    if (!ifile.is_open()) {
        cerr << "Failed to open marketdata.csv\n";
    }
    inv.initList(ifile);

}

int main(int argc, char const *argv[])
{   

    string line;
    bootStrap();
    while (getline(cin, line) && line != ":quit")
    {
        if (validCommand(line))
        {
            evalCommand(line);
        }
        else
        {
            cout << "Command not supported. Enter :help for list of supported commands" << endl;
        }
        cout << "> ";
    }
    return 0;
}
