#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

enum errorCodes {
    error_code_0 = 0,
    error_code_1,
    error_code_2,
    error_code_3
};

void readNonTerminals(string tmp) {
    vector<string> nonTerminals;
    while(tmp.compare("#") != 0) {
        for(int i = 0; i < tmp.length(); i++) {
            if (ispunct(tmp.data()[i])) {
                throw error_code_0;
            }
            if(isdigit(tmp.data()[0])) {
                throw error_code_0;
            }
        }
        nonTerminals.push_back(tmp);
        cin >> tmp;
    }
}

void readTerminals(string tmp) {
    vector<string> terminals;
    while(tmp.compare("#") != 0) {
        for(int i = 0; i < tmp.length(); i++) {
            if (ispunct(tmp.data()[i])) {
                throw error_code_0;
            }
            if(isdigit(tmp.data()[0])) {
                throw error_code_0;
            }
        }
        terminals.push_back(tmp);
        cin >> tmp;
    }
}

int main() {
    string tmp;
    
    cin >> tmp;
    
    try {
        readNonTerminals(tmp);
        cin >> tmp;
        readTerminals(tmp);
                
        
    } catch(errorCodes error) {
        switch (error) {
            case error_code_0:
                cout << "ERROR CODE 0" << endl;
                break;
            case error_code_1:
                cout << "ERROR CODE 1" << endl;
                break;
            case error_code_2:
                cout << "ERROR CODE 2" << endl;
                break;
            case error_code_3:
                cout << "ERROR CODE 3" << endl;
                break;
            default:
                cout << "It should never come to the default case" << endl;
                break;
        }
    }
    
    // for (unsigned n=0; n<nonTerminals.size(); ++n) {
    //     cout << nonTerminals.at( n ) << " ";
    // }
    return 0;
}