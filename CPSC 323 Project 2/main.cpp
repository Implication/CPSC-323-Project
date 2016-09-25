/*
 Trajon Felton
 * Vincent Campbell
 * 
 * Ray Almedia
 * CPSC 323 Project 2 
 * September 8, 2016
 * Purpose: Reads in a postfix mathematical expression and computers based on 
 * user input
 */


//Libraries
#include <cstdlib>
#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <sstream>
using namespace std;

/*Struct Token
 Used to identify a word and its associated value,
 Serving as a key and value type input*/
struct Tokens {
    vector<string> words;
    vector<string> value;
} id;

//Functions
bool isOperator(char input);
bool isDigit(char input);
void expression(string&, string&, bool&);
int operation(int num1, int num2, char op);

//Program starts here

int main(int argc, char** argv) {
    //Variable declaration
    string a; // Holds the value of the number
    string input; //User input of a postfix expression
    stack<int> n; //Used to hold all integers and pop numbers for operations
    char condition; // Condition to check if the user wants to do more postfix 
    //expressions
    bool math; //Used to determine whether we do math or not
    char op; // Stores the operator being enacted on 2 operands
    string token; //Used to store each token expression given by the user
    string exp; //Used to store the expression of values given by the 
    //user
    
    do {
        bool isValid = true;
        //Here we need to enter a postfix expression in order to do our 
        //operations
        cout << "Enter a postfix expression with a $ at the end: ";
        getline(cin, input);
        int x = 0;
        int result;
        /*While loop needed in order to convert our
         string letters into character digits*/
        expression(input, exp, isValid);
        //Need to reset our x value counter to use it again  in this while loop
        x = 0;
        exp += '$';
        /*While loop used to basically perform operations*/
        //If used to make sure this is only performed if the expression
        //Entered had valid input
        if (isValid) {
            while (exp[x] != '$') {
                //Used to determine if we need to do an operation or not
                math = isOperator(exp[x]);
                /*IF-else conditon: if math is true, then we perform an 
                 * operation  otherwise we make the character digit an integer 
                 * and push it into our  stack*/
                if (math == true) {
                    int n1 = n.top();
                    n.pop();
                    int n2 = n.top();
                    n.pop();
                    result = operation(n1, n2, exp[x]);
                    n.push(result);
                } else {
                    //For this project, we have spaces, so we need to allow our
                    //string to gather all the character digits of the token
                    //Seperated by spaces
                    if (!isspace(exp[x])) {
                        a += exp[x];
                    } else {
                        // This checks to make sure a is not an empty string
                        if (!a.empty()) {
                            //Conversion operator using string stream library
                            int z;
                            stringstream convert(a); //Using to convert strings 
                            //into integers
                            convert >> z;
                            //Push the newly found integer into our n stack
                            n.push(z);
                            //Empty the string
                            a.clear();
                        }
                    }
                }
                x++;
            }

            //Show the results
            if (!n.empty()) {
                cout << "\tThe final value is " << n.top() << endl;
                while (!n.empty()) {
                    n.pop(); //Pop the final value to prevent memory leaks
                }
            }
        }
          cout << "Continue(y/n)? : ";
            cin >> condition;
            //Need to clear the input buffer for getline
            cin.ignore(); cin.clear();
            //Word bank and values need to be cleared
            id.words.clear(); id.value.clear();
            //Expression also must be emptied and cleared
            exp.clear();
    } while (condition == 'y' || condition == 'Y');
    return 0;
}

/*Expression Function
 This functions main use is for expressions that contain white
 spacing in between each token. Using other functions, this will 
 read in the input given by the user and create an expression
 that will be used to perform the postfix operations.
 This also checks if the input entered in by the user, if 
 a user enters a token expression that is not allowed
 this will stop the program and prompt the user to re enter the expression*/
void expression(string& input, string& exp, bool& in) {
    string token;
    int x = 0;
    while (input[x] != '$') {
        string value;
        if (!isspace(input[x])) {
            token += input[x];
        }
        /*Condition, if the character is not a digit or an operation
         it is a letter, therefore we need to obtain the letter
         and get the value input by the user. Finally we convert all
         letters into the number inputted in by the user*/
        if (input[x] == ' ') {
            //  letter = input[x];
            if (!isDigit(token[0]) && !isOperator(token[0])) {
                bool repeat = false; // Used to check if the word is not 
                //a repeat
                /*For-Loop
                 This checks if any repeated words have been entered 
                 * into the expresssion, if it is a repeat,
                 * then we simply need to enter its associated value
                 * into our expression */
                for (int i = 0; i < id.words.size(); i++) {
                    if (token == id.words[i]) {
                        repeat = true;
                        exp += id.value[i];
                        break;
                    }
                }
                //This makes sure that the user does not enter a new value
                //of a repeated word in the string
                if (!repeat) {
                    //We prompt our user to enter in the value of our token
                    cout << "Enter the value of " << token << " ";
                    cin >> value;
                    cin.ignore(); //This is to clear the buffer of the newline
                    //Character for getline in the beginning
                    
                    //Our new word was entered, so now we need to push the 
                    //New word and value into our vectors in our id struct.
                    id.words.push_back(token);
                    id.value.push_back(value);
                    exp += value + " ";
                }

            }
            else {
                bool num = true; //Used to check if an identifier or number is 
                //correctly used, 
                bool opsize = true; //Used to see if correct input was entered 
                //for operators
                //Basically if the user enters a alphanumeric identifier, 
                //we prompt them that they Entered bad input 
                //in and end the program.
                if (isDigit(token[0])) {
                    for (int z = 0; z < token.size(); z++) {
                        if (!isDigit(token[z])) {
                            num = false;
                            break;
                        }
                    }
                }
                //This checks to make sure any operators are only operator
                //Expressions with no other letter or digits.
                if (isOperator(token[0])) {
                    if (token.size() > 1)
                        opsize = false;
                }
                //This condition prints out to the use they entered bad input
                if (!num || !opsize) {
                    cout << "\nWrong input: " << token << " was entered into "
                            "the expression." << endl;
                    cout << "Letters must only have letters, numbers must only "
                            "have numbers, and operators must only contain the "
                            "operator. " << endl;
                    cout << "Re-run the program and try again\n" << endl;
                    in = false;
                    break;
                } else {
                    exp += token + " ";
                }
            }
            //We need to clear our string in order to read in the next token
            token.clear();
        }
        // }
        x++;


    }
}

/*isOperator function: Checks if a character is
 an operator or not. If it is, returns true, otherwise
 it returns false*/
bool isOperator(char input) {
    string operators = "+-*/%";
    bool isOp = false;
    for (int i = 0; i < operators.size(); i++) {
        if (input == operators[i]) {
            isOp = true;
            break;
        }
    }
    return isOp;
}

/*isDigit function: Checks to see if the character is a digit or not
 if it is returns true, otherwise it returns false*/
bool isDigit(char input) {
    if (input >= '0' && input <= '9') {
        return true;
    } else
        return false;
}

/*Operation function: Simply performs operation
 based on the operand given on the 2 numbers
 in the stack. Returns the result back into main*/
int operation(int num1, int num2, char op) {
    int result;
    switch (op) {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            result = num1 / num2;
            break;
        case '%':
            result = num1 % num2;
            break;
        default:
            cout << "There is no operation present" << endl;
            result = 0;

    }
    return result;
}
