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

vector<string> nonTerminals;                        //vector to hold a list of non-terminal tokens
vector<string> terminals;                           //vector to hold a list of terminal tokens
vector<string> rules;                               //vector to hold a list of rules

void readNonTerminals(string tmp) {
    while(tmp.compare("#") != 0) {                  //loop throught until it finds a '#'
        for(int i = 0; i < tmp.length(); i++) {     
            if(ispunct(tmp.data()[i])) {            //checks to make sure there are no punctuation in the token
                throw error_code_0;
            }
            if(isdigit(tmp.data()[0])) {            //chekcs to make sure the first character in the token is not a digit
                throw error_code_0;
            }
        }
        nonTerminals.push_back(tmp);                //add the token to the vector non-terminal
        cin >> tmp;                                 //read in the next token
    }
}

void readTerminals(string tmp) {
    while(tmp.compare("#") != 0) {                  //loop throught until it finds a '#'
        for(int i = 0; i < tmp.length(); i++) {
            if(ispunct(tmp.data()[i])) {            //checks to make sure there are no punctuation in the token
                throw error_code_0;
            }
            if(isdigit(tmp.data()[0])) {            //chekcs to make sure the first character in the token is not a digit
                throw error_code_0;
            }
        }
        terminals.push_back(tmp);                   //add the token to the vector terminal
        cin >> tmp;                                 //read in the next token
    }
}

void readRules(string tmp) {
    rules.push_back("#");
    rules.push_back("$");
    
    for(int i=0; i < terminals.size(); i++) {
        rules.push_back(terminals.at(i));
    }
    for(int i=0; i < nonTerminals.size(); i++) {
        rules.push_back(nonTerminals.at(i));
    }
    
    
    
    
    // while(tmp.compare("##") != 0) {
    //     if(tmp.compare("->") != 0) {
    //         rules.push_back(tmp);
            
    //         for(int i = 0; i < rules.size(); i++) {
    //             if(ispunct(rules.at(i))) {            //checks to make sure there are no punctuation in the token
    //                 throw error_code_0;
    //             }   
    //             if(isdigit(rules.at(0))) {            //chekcs to make sure the first character in the token is not a digit
    //                 throw error_code_0;
    //             }
    //         }
    //     }
    // }
        
}

int main() {
    string tmp;     //hold the temporary token from file
    cin >> tmp;     //read in the first token
    
    try {
        readNonTerminals(tmp);      //read the first line in the file
        cin >> tmp;                 //read in the next token
        readTerminals(tmp);         //read the second line in the file
        cin >> tmp;
        readRules(tmp);
        
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
    
    for (unsigned n=0; n<rules.size(); ++n) {
        cout << rules.at(n) << " ";
    }
    // for (unsigned n=0; n<terminals.size(); ++n) {
    //     cout << terminals.at(n) << " ";
    // }
    return 0;
}