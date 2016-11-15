
/* 
 * File:   main.cpp
 * Author: Trajon Felton
 * Vincent Campbell
 * Rosin Chau
 * Due November 10, 2016
 * Ray Almedia
 *
 * Created on November 5, 2016, 3:38 PM
 * Purpose: Reads and determines if an input is accepted in the grammar
 */

#include <cstdlib>
#include <iostream>
#include <stack>
#include <queue>
#include <sstream>

using namespace std;

//Functions
void read(stack<string>& st, queue<char>& input, string table[17][11], string
   key[11],string rule[8], bool& ntd, string& prev);
void p(stack<string>& st, queue<char>& input, string table[17][11], string
    key[11],string value, int row, int col, string nt, string rule[8]
    ,bool& ntd,string& prev);
void pS1(stack<string>& st, queue<char>& input, string table[17][11], string
    key[11],string value, int row, int col, string nt, string rule[8]
    , bool& ntd,string& prev);
void pR(stack<string>& st, queue<char>& input, string table[17][11], string
    key[11],string value, int row, int col, string nt, string rule[8]
    ,bool& ntd,string& prev);//Push function

void displayStack(stack<string> st);

int main(int argc, char** argv) {
    //
    bool ntd = false;
    string prev;
    char con;
    //Rules
    string rule[8] = { "E->E+T","E->E-T","E->T","T->T*F","T->T/F", "T->F",
    "F->(E)" ,"F->i" };
    
    //Firsts
    string first_e = "(i";
    string first_t = "(i";
    string first_f = "(i";
    
    //Follows
    string follow_e = "-)$";
    string follow_t = "-*/)$";
    string follow_f = "-*/)$";
    
    //Input String
    queue<char> input;
    
    //Stack
    stack<string> st;
    
    //Stores the key characters of each column
    string key[11] = {"|","+", "-", "*", "/", "(", ")", "$", "E", "T", "F" };
    int row; //Stores the row to look at in the table
    
    string table[17][11] = {
    //       <------Terminals------>     <-Non-Terminals->
    //      | | | +| - | * | / | ( | ) | $ | E | T | F |
    /*0*/    {"S5", " ", " ", " ", " ", "S4", " ", " ", "1", "2", "3" },
    /*1*/    {" ", "S6", "S7", " ", " ", " ", " ", "acc", " ", " ", " " }, 
    /*2*/    {" ", "R3", "R3", "S8", "S9", " ", "R3", "R3", "R3", " ", " " },
    /*3*/    {" ", "R6", "R6", "R6", "R6", " ", "R6", "R6", " ", " ", " " },
    /*4*/    {"S5", " ", " ", " ", " ", "S4", " ", " ", "10", "2", "3" },
    /*5*/    {" ", "R8", "R8", "R6", "R6", " ", "R8", "R8", " ", " ", " " },
    /*6*/    {"S5", " ", " ", " ", " ", "S4", " ", " ", " ", "11", "3" },
    /*7*/    {"S5", " ", " ", " ", " ", "S4", " ", " ", " ", "12", "3" },
    /*8*/    {"S5", " ", " ", " ", " ", "S4", " ", " ", " ", " ", "13" },
    /*9*/    {"S5", " ", " ", " ", " ", "S4", " ", " ", "1", "2", "14" },
    /*10*/    {" ", "S6", "S7", " ", " ", " ", "S15", " ", " ", " ", " " },
    /*11*/    {" ", "R1", "R1", "S8", "S9", " ", "R1", "R1", " ", " ", " " },
    /*12*/    {" ", "R2", "R2", "S8", "S9", " ", " R1", "R1", " ", " ", " " },
    /*13*/    {" ", "R4", "R4", "R4", "R4", " ", " ", " ", "1", "2", "3" },
    /*14*/    {" ", "R5", "R5", "R5", "R5", " ", "R5", "R5", " ", " ", " " },
     /*15*/   {" ", "R7", "R7", "R7", "R7", " ", "R7", "R7", " ", " ", " " },
    };
    do{
        cout << "Please enter the input string: ";
        string i;
        cin >> i;
        for(int z = 0; z < i.length(); z++){
            input.push(i[z]);
        }
        st.push("0");
        cout << "Push: 0" << "\t" << "input: " << i << endl;
        read(st,input,table,key,rule,ntd,prev);
        
        cout << "Continue?(y/n)";
        cin >> con;
    }while(con == 'y' || con == 'Y');
    
    return 0;
}

void read(stack<string>& st, queue<char>& input, string table[17][11], string key[11], string rule[8], bool& ntd, string& prev){
    // is pushed onto the stack, needed for push
    string nt = " "; //This is for the push function if used.
    stringstream ss;
    string token;
    ss << input.front();
    ss >> token;
    cout << "Pop: " << st.top() << endl;
    if(ntd){
        token = prev;
    }
    if(!ntd){
        prev = token;
        input.pop();
    }
    int row, col;
    string value;
    if(!ntd){
    cout << "read: " << token << endl;
    }
    cout << "[" << st.top() << " , " << token << "] = ";
    for(int i = 0; i < 11; i++){
        if(token == key[i]){
            col = i;
            break;
        }
    }
    
    row = atoi(st.top().c_str());
    value = table[row][col];
    cout << value << endl;
    ntd = false;
    if(value == "acc"){
      cout <<  "Language was accepted" << endl;
    }
    else if(value == " "){
       cout <<  "Language was not accepted" << endl;
    }
    else{
       p(st, input, table, key, value, row, col, nt, rule, ntd, prev);
    }
    
}

void p(stack<string>& st, queue<char>& input, string table[17][11], string
    key[11],string value, int row, int col,string nt,string rule[8], bool& ntd
, string& prev){
    if(value.at(0) != 'R')
        pS1(st, input, table, key, value, row, col, nt, rule, ntd,prev);
     else
        pR(st, input, table, key, value, row, col, nt, rule, ntd,prev);
    }

void pS1(stack<string>& st, queue<char>& input, string table[17][11], string
    key[11],string value, int row, int col, string nt, string rule[8], bool& ntd
,string& prev){
      cout << "push: " << st.top() << " " << key[col] << " "; 
      if(value[0] == 'S'){
      cout << value[1] << endl;
      }
      else{
          cout << value[0] << endl;
      }
        st.push(key[col]);
        stringstream ss;
        if(value[0] == 'S'){
             string x = value.substr(1,value.length() - 1);
             ss << x;
        }
        else{
            ss << value;
        }
        string temp;
        ss >> temp;
        st.push(temp);
        displayStack(st);
        read(st,input,table,key,rule,ntd,prev);
}
void pR(stack<string>& st, queue<char>& input, string table[17][11], string
    key[11],string value, int row, int col, string nt, string rule[8], bool& ntd
,string& prev){
         cout << "push: " << st.top() << endl;
            //display stack
            cout << "#" << value.at(1) << ": ";
            int num = value[1] - '0';
            string line = rule[num - 1];
            cout << line;
            nt = line[0];
            string rhs = line.substr(3,line.length() - 3);
            cout << "Pop: 2 * |" << rhs << "| = " << rhs.length() * 2 
                    << " items" << endl;
            for(int i = 1; i <= 2*rhs.length(); i++){
                st.pop();
            }
            //display the stack
        cout << "Pop: " <<  st.top() << endl;
        displayStack(st);
        stringstream ss;
        ss << line[0];
        ss >> nt;
        cout << "[" << st.top() << " , " << nt << "] = ";
        for(int i = 0; i < 11; i++){
        if(nt == key[i]){
            col = i;
            break;
        }
    }
    
    row = atoi(st.top().c_str());
    value = table[row][col];
    cout << value << endl;
    ntd = true;
    if(value == "acc"){
      cout <<  "Language was accepted" << endl;
    }
    else if(value == " "){
       cout <<  "Language was not accepted" << endl;
    }
    else{
        p(st,input,table,key,value,row,col,nt,rule,ntd,prev);
    }
}

void displayStack(stack<string> st){
    cout << "Stack : ";
    string c;
    while(!st.empty()){ 
        c = st.top() + " " + c;
        st.pop();
    }
    cout << c;
    cout << endl;
}

