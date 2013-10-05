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
    error_code_3,
    error_code_4
};

struct Rules {
    int LHS;
    vector<int> RHS;
};

vector<string> nonTerminals;                        //vector to hold a list of non-terminal tokens
vector<string> terminals;                           //vector to hold a list of terminal tokens
vector<string> reference;                           //vector to hold a list of rules
vector<int> nT;                                     //vector for error check 1
vector<int> t;                                      //vector for error check 4
vector<string> errorCodeVector;                     //vector to hold the error codes
vector<Rules> vecOfRules;                           //vector of rules

vector< vector<int> > ultimateFirstSet;

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
        if(isdigit(tmp.data()[0])) {            //checks to make sure the first character in the token is not a digit
            throw error_code_0;
        }
    }
}

void checkErrorCodeOne() {
    for(int i=0; i < nT.size(); i++) {
        if(nT.at(i) == 0) {
            int index = findTokenInVector(errorCodeVector, "ERROR CODE 1");
            if(index == -1) {
                errorCodeVector.push_back("ERROR CODE 1");
            }
        }
    }
}

void checkErrorCodeTwo(string tmp) {
    int index = findTokenInVector(nonTerminals, tmp);
    int index2 = findTokenInVector(terminals, tmp);
    if(index == -1 && index2 == -1) {
        int index = findTokenInVector(errorCodeVector, "ERROR CODE 2");
        if(index == -1) {
            errorCodeVector.push_back("ERROR CODE 2");
        }
    }
}

void checkErrorCodeThree(string tmp) {
    int index = findTokenInVector(terminals, tmp);
    if(index != -1) {
        int index = findTokenInVector(errorCodeVector, "ERROR CODE 3");
        if(index == -1) {
            errorCodeVector.push_back("ERROR CODE 3");
        }
    }
}

void checkErrorCodeFour() {
    for(int i=0; i < t.size(); i++) {
        if(t.at(i) == 0) {
            int index = findTokenInVector(errorCodeVector, "ERROR CODE 4");
            if(index == -1) {
                errorCodeVector.push_back("ERROR CODE 4");
            }
        }
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
}

void readGrammar() {
    
    string tmp;
    cin >> tmp;                             //read the first token in section 3 the rules
    
    while(tmp.compare("##") != 0) {         //exit the loop when a "##" is found in the file
        Rules rule;                         //create a new rule
        
        //****start of LHS****//
        checkErrorCodeZero(tmp);            //checking for syntax errors
        
        int index = findTokenInVector(nonTerminals, tmp);       /*because this token is on the LHS, check to make sure its
                                                                  a non-terminal. It will find the token in the non-terminal
                                                                  vector and return the index*/
        if(index != -1) {                   //if the token is found then the value is changed to 1 signifying that its been found
            nT.at(index) = 1;
        }
        
        checkErrorCodeTwo(tmp);             /*checking to make sure the token is listed in section 1 or 2,
                                            if no error then we assume that the token is either in 
                                            section 1 or 2 or both as a T or NT*/
        checkErrorCodeThree(tmp);           //checking to make sure its a NT on the LHS
        
        index = findTokenInVector(reference, tmp);              //once it passes error 0, 2, 3 then add it to the rule
        rule.LHS = index;
        //****end of LHS****//
        
        cin >> tmp;                         //read the next token
        
        if(tmp.compare("->") == 0) {        //the next token needs to be an "->" to be a valid file
            cin >> tmp;                     //read the next token
            
            //****start of RHS****//
            if(tmp.compare("##") == 0) {    //if the next token after "->" is "##" then error code 0
                throw error_code_0;
            }
            else if(tmp.compare("#") == 0) {                        //if the next token after "->" is "#" then its epsilon
                int index = findTokenInVector(reference, tmp);
                rule.RHS.push_back(index);                          //find the index, add it to the rule, then add the rule to a vector of rules
                vecOfRules.push_back(rule);
            }
            else {                                                  //this is for the case of normal tokens
                while(tmp.compare("#") != 0) {                      //loop as long as "#" is not found, this makes it so it breaks up the rules
                    int index = findTokenInVector(terminals, tmp);  //similar with error 1 and that its checking the terminal vector
                        
                    if(index != -1) {                               //if the token is found then mark the vector 1 at that index
                        t.at(index) = 1;
                    }
                    checkErrorCodeZero(tmp);        
                    checkErrorCodeTwo(tmp); 
                    index = findTokenInVector(reference, tmp);      //if error check passes then add the index to the rule
                    rule.RHS.push_back(index);
                    cin >> tmp;                                     //read the next token
                }
                vecOfRules.push_back(rule);                         //add the rule to the vector of rules
            }
        }
        else {
            throw error_code_0;                                     //error code 0 if the second token is not a "->"
        }
        cin >> tmp;                                                 //read the next token
        if(tmp.compare("##") == 0) {                                /*if the token is "##" then check for error code 1 and 4,
                                                                      because at this point its at the end of the file and you
                                                                      know you've read in all the inputs. Since the t and nT 
                                                                      vectors were being marked as tokens were being read in,
                                                                      these vectors will all have a true value in them (meaning
                                                                      all the terminals and non-terminals were accounted for) or
                                                                      if it has at least one false value then error codes will be 
                                                                      thrown in their respective functions*/
            checkErrorCodeOne();
            checkErrorCodeFour();
        }
        // for(int i=0; i < rule.RHS.size(); i++) {
        //     cout << "RHS: " << rule.RHS.at(i) << "\n";
        // }
    }
}
    
vector<int> unionSet(vector<int> v1, vector<int> v2) { 
    vector<int> v3(v1.size(), 0);
    for(int i=0; i < v1.size(); i++) {
        if(v1.at(i) == 1 || v2.at(i) == 1) {
            v3.at(i) = 1;
        }
    }
    return v3;
}    
    
void calculateFirstSet() {
    vector<int> firstSet(reference.size(), 0);          //the default vector that has the same size as the reference vector with 
                                                        //initial values of 0, meaning they are all false
    
    for(int i=0; i < reference.size(); i++) {           //loop to add the default vector to the big vector essentially making it a 2d vector
        vector<int> defaultFirst(firstSet);
        ultimateFirstSet.push_back(defaultFirst);
        
        if(i == 0 || (i > 1 && i < terminals.size() + 2)) {         //add 1(true) to all the terminals because FIRST(terminal) = {terminal}
            ultimateFirstSet.at(i).at(i) = 1;
        }
    }
   
    bool change = true;                                 //a flag to keep track of whether or not the vectors are changing
    while(change) {
        change = false;
        
        //for all rules
        for(int i=0; i < vecOfRules.size(); i++) {                                      //loop through all of the rules
            //loop through the RHS, add FIRST(A1) - e to FIRST(A)
            
            int j = 0;
            for(j; j < vecOfRules.at(i).RHS.size(); j++) {
                vector<int> v1 = ultimateFirstSet.at(vecOfRules.at(i).LHS);
                vector<int> v2 = ultimateFirstSet.at(vecOfRules.at(i).RHS.at(j));
                
                vector<int> copyVec(v1);                                                //copy of the FIRST(LHS) so I can compare later for change
                
                ultimateFirstSet.at(vecOfRules.at(i).LHS) = unionSet(v1, v2);
                
                // for(int n=0; n < copyVec.size(); n++) {
                //     cout << copyVec.at(n) << " ";
                // }
                // for(int m=0; m < ultimateFirstSet.size(); m++) {
                //     cout << ultimateFirstSet.at(vecOfRules.at(i).LHS).at(m);
                // }
                
                if(copyVec != ultimateFirstSet.at(vecOfRules.at(i).LHS)) {
                    change = true;
                } 
                
                if(ultimateFirstSet.at(vecOfRules.at(i).RHS.at(j)).at(0) != 1) {        //if = 1 then there is epsilon, therefore continue
                                                                                        //add FIRST(An) - e to FIRST(A) 
                    break;
                }
                
                // for(int i=0; i < v1.size(); i++) {
                //     cout << v1.at(i) << " ";
                // }
                // cout << "\n";
                // for(int i=0; i < v2.size(); i++) {
                //     cout << v2.at(i) << " ";
                // }
                // break;
            }//end of inner for loop
            
            if(j == vecOfRules.at(i).RHS.size() - 1) {                              //if j is the last index on RHS then that means its done 
                                                                                    //the unionSets for each token on the RHS
                if(ultimateFirstSet.at(vecOfRules.at(i).RHS.at(j)).at(0) == 1) {    //if epsilon exits in the last FIRST(RHS) then its assumed
                                                                                    //that epsilon belonged in all FIRST(RHS) therefore add 
                                                                                    //epsilon to FIRST(LHS)
                    ultimateFirstSet.at(vecOfRules.at(i).LHS).at(0) = 1;
                }
            }
        }//end of outer for loop
    }
    
    //print matrix
    for(int i = 0; i < reference.size(); i++ ) {
        for(int j = 0; j < reference.size(); j++ ) {
            cout << ultimateFirstSet.at(i).at(j) << " ";
        }
        cout << endl;
    }
}

void printFirstSet() {
    for(int i=terminals.size() +2; i < reference.size(); i++) {
        bool flag = false;
        
        cout << "FIRST(" << reference.at(i) << ") = {";
        for(int j=0; j < ultimateFirstSet.size(); j++) {
            
            if(ultimateFirstSet.at(i).at(j) == 1) {
                if(!flag) {
                    flag = true;
                     
                }
                else {
                    cout << ",";
                }
                cout << " " << reference.at(j);
            }
        }
        cout << " }" << "\n";
    }
}

int main() {
    try {
        readNonTerminals();             //read the first line in the file
        readTerminals();                //read the second line in the file
        createReferenceVector();        //reference vector used to reference tokens to see if they exits within section 1 and section 2
        
        for(int i=0; i < nonTerminals.size(); i++) {
            nT.push_back(0);    
        }
        for(int i=0; i < terminals.size(); i++) {
            t.push_back(0);
        }
        
        readGrammar();                  //read in the grammar and perform all error checking
        
        if(errorCodeVector.empty()) {
            calculateFirstSet();
        printFirstSet();
        // calculateFollowSet();
        // printFollowSet();
        }
    } catch(errorCodes error) {
        switch (error) {
            case error_code_0: {
                cout << "ERROR CODE 0" << endl;
                exit(0);
                break;
            }
            default:
                cout << "It should never get to the default case" << endl;
                break;
        }
    }
    std::sort(errorCodeVector.begin(), errorCodeVector.end());
    
    for (int n=0; n<errorCodeVector.size(); ++n) {
        cout << errorCodeVector.at(n) << "\n";
    }
    
    
    
    
    
    // cout << rule1.LHS << endl;
    // for(unsigned n=0; n<rule1.RHS.size(); ++n) {
    //     cout << rule1.RHS.at(n) << " ";
    // }
    // for (unsigned n=0; n<terminals.size(); ++n) {
    //     cout << terminals.at(n) << " ";
    // }
    return 0;
}