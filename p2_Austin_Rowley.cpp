#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

enum errorCodes {
    error_code_0 = 0,
    error_code_1,
    error_code_2,
    error_code_3
};

struct Rules {
    int LHS;
    vector<int> RHS;
};

vector<string> nonTerminals;                        //vector to hold a list of non-terminal tokens
vector<string> terminals;                           //vector to hold a list of terminal tokens
vector<string> reference;                           //vector to hold a list of rules
vector<bool> nT;
vector<bool> t;
//vector< vector<int> > reference;

//Rules rule1;

int findTokenInVector(vector<string> tmpVec, string tmp) {
    int index = -1;
    for(int i=0; i < tmpVec.size(); i++) {
        if(tmp.compare(tmpVec.at(i)) == 0) {
            index = i;
        }
    }
    return index;
}

void checkErrorCodeZero(string tmp) {
    for(int i = 0; i < tmp.length(); i++) {     
        if(ispunct(tmp.data()[i])) {            //checks to make sure there are no punctuation in the token
            throw error_code_0;
        }
        if(isdigit(tmp.data()[0])) {            //chekcs to make sure the first character in the token is not a digit
            throw error_code_0;
        }
    }
}

void checkErrorCodeTwo(string tmp) {
    int index = findTokenInVector(nonTerminals, tmp);
    int index2 = findTokenInVector(terminals, tmp);
    if(index == -1 && index2 == -1) {
        throw error_code_2;
    }
    else {
        
    }
}

void checkErrorCodeThree(string tmp) {
    int index = findTokenInVector(terminals, tmp);
    if(index != -1) {
        throw error_code_3;
    }
}

void readNonTerminals() {
    string tmp;
    cin >> tmp;
    while(tmp.compare("#") != 0) {                  //loop throught until it finds a '#'
        checkErrorCodeZero(tmp);
        nonTerminals.push_back(tmp);                //add the token to the vector non-terminal
        cin >> tmp;                                 //read in the next token
    }
}

void readTerminals() {
    string tmp;
    cin >> tmp;
    while(tmp.compare("#") != 0) {                  //loop throught until it finds a '#'
        checkErrorCodeZero(tmp);
        terminals.push_back(tmp);                   //add the token to the vector terminal
        cin >> tmp;                                 //read in the next token
    }
}

void createReferenceVector() {
    reference.push_back("#");
    reference.push_back("$");
    
    for(int i=0; i < terminals.size(); i++) {
        reference.push_back(terminals.at(i));
    }
    for(int i=0; i < nonTerminals.size(); i++) {
        reference.push_back(nonTerminals.at(i));
    }
    // for (int i = 0; i < 10; i++) {
    //     vector<string> row; // Create an empty row
    //     for (int j = 0; j < 20; j++) {
    //         row.push_back(i * j); // Add an element (column) to the row
    //     }
    //     vec.push_back(row); // Add the row to the main vector
    // }
}

void readGrammar() {
    string tmp;
    cin >> tmp;
    
    checkErrorCodeZero(tmp);            //checking syntax
    checkErrorCodeTwo(tmp);             //checking to make sure the token is listed in section 1 or 2, if no error then we assume that the token is either in section 1 or 2 or both as a T or NT
    checkErrorCodeThree(tmp);           //checking to make sure its a NT on the LHS
    
    
    
    
    
    // iterator intIterator;
    // std::vector<int>::iterator intIterator;
    
    // while(tmp.compare("##") != 0) {
    //     for(int i = 0; i < tmp.length(); i++) {
    //         if(ispunct(tmp.data()[i])) {            //checks to make sure there are no punctuation in the token
    //             throw error_code_0;
    //         }
    //         if(isdigit(tmp.data()[0])) {            //chekcs to make sure the first character in the token is not a digit
    //             throw error_code_0;
    //         }
    //     }
        
    //     intIterator = find(rules.begin(), rules.end(), tmp);
    //     rule1.LHS = intIterator;
        
    //     cin >> tmp;
    //     if(tmp.compare("->") == 0) {
    //         cin >> tmp;
            
    //         if(tmp.compare("#") == 0 || tmp.compare("##") == 0) {
    //             intIterator = find(rules.begin(), rules.end(), tmp);
    //             rule1.RHS.push_back(intIterator);
    //         }
    //         else {
    //             while(tmp.compare("#") != 0 && tmp.compare("##") != 0) {
    //                 for(int i = 0; i < tmp.length(); i++) {
    //                     if(ispunct(tmp.data()[i])) {            //checks to make sure there are no punctuation in the token
    //                         throw error_code_0;
    //                     }
    //                     if(isdigit(tmp.data()[0])) {            //chekcs to make sure the first character in the token is not a digit
    //                         throw error_code_0;
    //                      }
    //                 }
                    
    //                 intIterator = find(rules.begin(), rules.end(), tmp);
    //                 rule1.RHS.push_back(intIterator);
    //                 cin >> tmp;
    //             }
    //         }
    //     }
    //     else {
    //         for(int i = 0; i < tmp.length(); i++) {
    //             if(ispunct(tmp.data()[i])) {            //checks to make sure there are no punctuation in the token
    //                 throw error_code_0;
    //             }
    //             if(isdigit(tmp.data()[0])) {            //chekcs to make sure the first character in the token is not a digit
    //                 throw error_code_0;
    //             }
    //         }
    //     }
    // }
}
    

int main() {
    // string tmp;     //hold the temporary token from file
    // cin >> tmp;     //read in the first token
    
    try {
        readNonTerminals();             //read the first line in the file
        readTerminals();                //read the second line in the file
        createReferenceVector();        //reference vector used to reference tokens to see if they exits within section 1 and section 2
        
        for(int i=0; i < nonTerminals.size(); i++) {
            nT.push_back(false);    
        }
        for(int i=0; i < terminals.size(); i++) {
            t.push_back(false);
        }
        
        readGrammar();
        
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
    
    // for (unsigned n=0; n<rules.size(); ++n) {
    //     cout << rules.at(n) << " ";
    // }
    
    // cout << rule1.LHS << endl;
    // for(unsigned n=0; n<rule1.RHS.size(); ++n) {
    //     cout << rule1.RHS.at(n) << " ";
    // }
    // for (unsigned n=0; n<terminals.size(); ++n) {
    //     cout << terminals.at(n) << " ";
    // }
    return 0;
}