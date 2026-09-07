#include <iostream>
#include <string>
#include <iomanip> //actually not sure but i'm done with this day and it worked with this here. so imma leave it be
#include <sstream> //for hex stuff
#include <openssl/evp.h> //openssl dependency (this took me wayyy too long to figure out. the code was easy once i got this done. it's also more complicated as i'm using the latest version which isn't from 2015 :') )
using namespace std;


string stringToMD5(const string& s)
{
    EVP_MD_CTX* ctx = EVP_MD_CTX_new(); //creates a context to process the md5 hash
    //result buffer/store
    unsigned char result[EVP_MAX_MD_SIZE];
    unsigned int resultLen = 0;

    EVP_DigestInit_ex(ctx, EVP_md5(), nullptr); //initialises the context
    EVP_DigestUpdate(ctx, s.c_str(), s.size()); //input the string (c_str is a pointer the to bytes)
    EVP_DigestFinal_ex(ctx, result, &resultLen); //finishes the md5 calculation and stores the output

    EVP_MD_CTX_free(ctx); //releases the memory the context used

    ostringstream hexValue;
    for (int i = 0; i < resultLen; i++)
    {
        hexValue << hex << setw(2) << setfill('0') << (int)result[i]; //converts md5 into hex
    }

    return hexValue.str();
}

int main()
{
    //input
    string input;
    cout << "Enter the key: ";
    cin >> input;

    //other vars
    int number = 1;
    string combined;
    string hexValue = "";
    
    while (hexValue.substr(0,6) != "000000") //start with 5 zeroes, move to 6 (6 took me SO LONG cause the number was 9,962,624!!)
    {
        combined = input + to_string(number); //cobines the input with the current number
        hexValue = stringToMD5(combined); //runs the above function
        cout << hexValue << endl; //debugging (also shows it is working)
        number++; //increment number
        cout << combined << endl; //likewise as above
    }

    //print my results
    cout << "Result: " << hexValue << endl;
    cout << "Number used: " << number-1 << endl; //(-1 cause it adds another to the number at the end of the while loop)
}