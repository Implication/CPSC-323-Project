/*
 Trajon Felton
 * Vincent Campbell
 * 
 * Ray Almedia
 * CPSC 323 Project 1 
 * September 1, 2016
 * Purpose: Reads in a postfix mathematical expression and computers based on 
 * user input
 */


//Libraries
#include <cstdlib>
#include <iostream>
#include <string>
#include <stack>
#include <queue>
using namespace std;

//Function
bool isOperator(char input);
bool isDigit(char input);
int operation(int num1, int num2, char op);
string converter(string input, char letter, int value);

//Program starts here
int main(int argc, char** argv) {
    //Variable declaration
    string input; //User input of a postfix expression
    stack<int> n; //Used to hold all integers and pop numbers for operations
    char letter; //After user input, this stores the letter to be used in the 
    //converter function of a letter to a number character
    char condition; // Condition to check if the user wants to do more postfix 
    //expressions
    bool math; //Used to determine whether we do math or not
    char op; // Stores the operator being enacted on 2 operands
    do{
    //Here we need to enter a postfix expression in order to do our operations
    cout << "Enter a postfix expression with a $ at the end: ";
    cin >> input;
    int x = 0;
    int result;
    /*While loop needed in order to convert our
     string letters into character digits*/
    while(input[x] != '$'){
        char value;
        /*Condition, if the character is not a digit or an operation
         it is a letter, therefore we need to obtain the letter
         and get the value input by the user. Finally we convert all
         letters into the number inputted in by the user*/
        if(!isOperator(input[x])){
            if(!isDigit(input[x])){
                letter = input[x];
                cout << "Enter the value of " << input[x] << " ";
                cin >> value;
                 input = converter(input,letter,value);
                }   
        }
        x++;
    }
    //Need to reset our x value counter to use it again in this while loop
    x = 0; 
    /*While loop used to basically perform operations*/
    while(input[x] != '$'){  
        //Used to determine if we need to do an operation or not
        math = isOperator(input[x]); 
        /*IF-else conditon: if math is true, then we perform an operation  
         otherwise we make the character digit an integer and push it into our 
         * stack*/
        if(math == true){
            int n1 = n.top(); n.pop();
            int n2 = n.top(); n.pop();
            result = operation(n1,n2,input[x]);
            n.push(result);
        }
        else{
            int z = input[x] - 48;
            n.push(z);
        }
        x++;
    }
    
    //Show the results
    cout << "\tThe final value is " << n.top() << endl; 
    n.pop(); //Pop the final value to prevent memory leaks
    cout << "Continue(y/n)? : ";
    cin >> condition;
    }while(condition == 'y' || condition == 'Y');
    return 0;
}
 
/*isOperator function: Checks if a character is
 an operator or not. If it is, returns true, otherwise
 it returns false*/
bool isOperator(char input){
    string operators = "+-*/%";
    bool isOp = false;
    for(int i = 0; i < operators.size(); i++){
        if(input == operators[i]){
            isOp = true; break;
        }
    }
    return isOp;
}

/*isDigit function: Checks to see if the character is a digit or not
 if it is returns true, otherwise it returns false*/
bool isDigit(char input){
    if(input >= '0' && input <= '9'){
        return true;
    }
    else
        return false;
}

/*Converter function: Purpose is to convert all letters in a postfix
 expression into numbers given the letter inputted in by the user
 and the value the user wishes to use. Returns the newly inputted
 string into main*/
string converter(string input, char letter, int value){
    for(int i = 0; i < input.size(); i++){
        if(input[i] == letter)
            input[i] = value;
    }
    return input;
}

/*Operation function: Simply performs operation
 based on the operand given on the 2 numbers
 in the stack. Returns the result back into main*/
int operation(int num1, int num2, char op){
    int result;
    switch(op){
        case '+':
            result = num2 + num1;
            break;
        case '-':
            result = num2 - num1;
            break;
        case '*':
            result = num2 * num1;
            break;
        case '/':
            result = num2 / num1;
            break; 
        case '%':
            result = num2 % num1;
            break;
        default:
            cout << "There is no operation present" << endl;
            result = 0;
           
    }
    return result;
}