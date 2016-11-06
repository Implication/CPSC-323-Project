/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Trajon Felton
 *
 * Created on November 5, 2016, 3:38 PM
 */

#include <cstdlib>
#include <iostream>
#include <stack>
#include <queue>

using namespace std;

//Functions
void read(stack<char>& st, queue<char>& input, string table[17][11], char
   key[11]);
void p(stack<char>& st, queue<char>& input, string table[17][11], char
    key[11]); //Push function

int main(int argc, char** argv) {
    //
    char con;
    //Rules
    string rule1 = "E->E+T";
    string rule2 = "E->E-T";
    string rule3 = "E->T";
    string rule4 = "T->T*F";
    string rule5 = "T->T/F";
    string rule6 = "T->F";
    string rule7 = "F->(E)";
    string rule8 = "F->i";
    
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
    stack<char> st;
    
    //Stores the key characters of each column
    char key[11] = {'|','+', '-', '*', '/', '(', ')', '$', 'E', 'T', 'F' };
    int row; //Stores the row to look at in the table
    
    string table[17][11] = {
    //       <------Terminals------>     <-Non-Terminals->
    //      | | | +| - | * | / | ( | ) | $ | E | T | F |
    /*0*/    {"S5", " ", " ", " ", " ", "S4", " ", " ", "1" "2", "3" },
    /*1*/    {" ", "S6", "S7", " ", " ", " ", " ", "acc", " " " ", " " }, 
    /*2*/    {" ", "R3", "R3", "S8", "S9", " ", "R3", "R3", "R3" " ", " " },
    /*3*/    {" ", "R6", "R6", "R6", "R6", " ", "R6", "R6", " " " ", " " },
    /*4*/    {"S5", " ", " ", " ", " ", "S4", " ", " ", "10" "2", "3" },
    /*5*/    {" ", "R8", "R8", "R6", "R6", " ", "R8", "R8", " " " ", " " },
    /*6*/    {"S5", " ", " ", " ", " ", "S4", " ", " ", " " "11", "3" },
    /*7*/    {"S5", " ", " ", " ", " ", "S4", " ", " ", " " "12", "3" },
    /*8*/    {"S5", " ", " ", " ", " ", "S4", " ", " ", " " " ", "13" },
    /*9*/    {"S5", " ", " ", " ", " ", "S4", " ", " ", "1" "2", "14" },
    /*10*/    {" ", "S6", "S7", " ", " ", " ", "S15", " ", " " " ", " " },
    /*11*/    {" ", "R1", "R1", "S8", "S9", " ", "R1", "R1", " " " ", " " },
    /*12*/    {" ", "R2", "R2", "S8", "S9", " ", " R1", "R1", " " " ", " " },
    /*13*/    {" ", "R4", "R4", "R4", "R4", " ", " ", " ", "1" "2", "3" },
    /*14*/    {" ", "R5", "R5", "R5", "R5", " ", "R5", "R5", " " " ", " " },
     /*15*/   {" ", "R7", "R7", "R7", "R7", " ", "R7", "R7", " " " ", " " },
    };
    do{
        cout << "Please enter the input string: ";
        string i;
        cin >> i;
        for(int z = 0; z < i.length(); z++){
            input.push(i[z]);
        }
        st.push('0');
        cout << "Push: 0" << "\t" << "input: " << i << endl;
        cout << "Pop: 0" << endl;
        read(st,input,table,key);
        
        cout << "Continue?(y/n)";
        cin >> con;
    }while(con == 'y' || con == 'Y');
    
    return 0;
}

void read(stack<char>& st, queue<char>& input, string table[17][11], char key[11]){
    char terminal = ' ' //This is for the push function if used.
    char token;
    token = input.front();
    input.pop();
    int row, col;
    string value;
    cout << "read: " << token << endl;
    cout << "[" << st.top() << " , " << token << "] = ";
    for(int i = 0; i < 11; i++){
        if(token == key[i]){
            col = i;
            break;
        }
    }
    
    row = (int)st.top();
    value = table[0][col];
    cout << value << endl;
    if(value == "acc"){
      cout <<  "Language was accepted" << endl;
    }
    else if(value == " "){
       cout <<  "Language was not accepted" << endl;
    }
    else{
        //Here is where you would push
    }
    
}

//TODO: Push function needs to be implemented
//I realized while doing this pop is not needed
//I suggest to whoever does it, to make push recursive
//Until it reads either a blank or accept
//I suggest to make it recursive to have a character variable
//Called terminal that reads in the terminal of the rules
//And becomes "empty" after use.
//When empty use the recursive push, otherwise push the values into
//read

