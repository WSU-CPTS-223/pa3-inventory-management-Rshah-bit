#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

struct inventorylist
{ 
    string UniqId;
    string ProductName;
    string BrandName;
    string Asin;
    string Category;
    string UpcEanCode;
    string ListPrice;
    string SellingPrice;
    string Quantity;
    string ModelNumber;
    string AboutProduct;
    string ProductSpecification;
    string TechnicalDetails;
    string ShippingWeight;
    string ProductDimensions;
    string Image;
    string Variants;
    string Sku;
    string ProductUrl;
    string Stock;
    string ProductDetails;
    string Dimensions;
    string Color;
    string Ingredients;
    string Directions;
    string Seller;
    string SizeQuantityVariant;
    string ProductDescription;
};

static inline bool readCSVRecord(ifstream &file, string &outRecord)
{
    outRecord.clear();
    string line; 
    if (!getline(file, line)) return false;
    outRecord = line; 
    auto quoteCount =count(outRecord.begin(), outRecord.end(), '"');
    while ((quoteCount % 2) == 1) {
        string next; 
        if (!getline(file, next)) break;
        outRecord +='\n';
        outRecord += next;
        quoteCount += count(next.begin(), next.end(), '"');
    }
    return true;
}

static inline vector<string> parseCSVLine(const string &line)
{
    vector<string> fields;
    string field;  
    bool inQuotes = false;
    for (size_t i =  0; i < line.size(); ++i) {
        char c = line[i];
        if (inQuotes){
            if (c == '"')
             {
                if (i + 1 < line.size() && line[i + 1] == '"') {
                    field.push_back('"');
                    ++i; 
                } else {
                    inQuotes = false;
                }
            } else {
                 field.push_back(c);
            }
        } else {
            if (c == '"') {
                inQuotes = true;
            } else if (c == ',') {
                fields.push_back(field);
                field.clear();
            } else {
                field.push_back(c);
            }
        }
    }
    fields.push_back(field);
    return fields;
}

template<typename Key = int,
         typename MapT = unordered_map<Key, inventorylist>>
class Inventory {
public:
    using key_type = Key;
    using map_type = MapT;
    using record_type = inventorylist;

     map_type initList(ifstream &file)
    {
        map_type thelist;
        string record;
        if (!readCSVRecord(file, record)) return thelist;

        size_t idx = 0;
        while (readCSVRecord(file, record)) {
            if (record.empty()) continue;
            vector<string> fields = parseCSVLine(record);
            Key key = static_cast<Key>(idx++);
            ListInsert(thelist, key, fields);
        }
        this->thelist = thelist;
        return thelist;
    }

    void ListInsert(map_type &list, const key_type &key, const vector<string> &fields)
    {
        if (fields.size() > 0) list[key].UniqId = fields[0];
        if (fields.size() > 1) list[key].ProductName = fields[1];
        if (fields.size() > 2) list[key].BrandName = fields[2];
        if (fields.size() > 3) list[key].Asin = fields[3];
        if (fields.size() > 4) list[key].Category = fields[4];
        if (fields.size() > 5) list[key].UpcEanCode = fields[5];
        if (fields.size() > 6) list[key].ListPrice = fields[6];
        if (fields.size() > 7) list[key].SellingPrice = fields[7];
        if (fields.size() > 8) list[key].Quantity = fields[8];
        if (fields.size() > 9) list[key].ModelNumber = fields[9];
        if (fields.size() > 10) list[key].AboutProduct = fields[10];
        if (fields.size() > 11) list[key].ProductSpecification = fields[11];
        if (fields.size() > 12) list[key].TechnicalDetails = fields[12];
        if (fields.size() > 13) list[key].ShippingWeight = fields[13];
        if (fields.size() > 14) list[key].ProductDimensions = fields[14];
        if (fields.size() > 15) list[key].Image = fields[15];
        if (fields.size() > 16) list[key].Variants = fields[16];
        if (fields.size() > 17) list[key].Sku = fields[17];
        if (fields.size() > 18) list[key].ProductUrl = fields[18];
        if (fields.size() > 19) list[key].Stock = fields[19];
        if (fields.size() > 20) list[key].ProductDetails = fields[20];
        if (fields.size() > 21) list[key].Dimensions = fields[21];
        if (fields.size() > 22) list[key].Color = fields[22];
        if (fields.size() > 23) list[key].Ingredients = fields[23];
        if (fields.size() > 24) list[key].Directions = fields[24];
        if (fields.size() > 25) list[key].Seller = fields[25];
        if (fields.size() > 26) list[key].SizeQuantityVariant = fields[26];
        if (fields.size() > 27) list[key].ProductDescription = fields[27];
    }

    void find(const string &inventoryid)
    {
        for (auto &kv : thelist) {
            const inventorylist &rec = kv.second;
            if (rec.UniqId == inventoryid) {
                cout << "Item: " << inventoryid << " exists!" << endl << endl;
                cout << "Name: " << rec.ProductName << endl << "Details: " << rec.ProductDetails << endl << "About: " << rec.AboutProduct << endl;
                return;
            }
        }
        cout << "Could not find product with id: " << inventoryid << endl;
    }

    void listInventory(const string &category)
    {

    }

private:
    inventorylist cvlist;
    map_type thelist;
};
using InventoryT = Inventory<>;