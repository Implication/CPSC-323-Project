/*
 * Trajon Felton
 * Vincent Campbell
 * Rosin Chau
 * Ray Almedia
 * CPSC 323 Project 3 Part 1 
 * September 15, 2016
 * Purpose: Given a file, this will fix the format in order for it to be read
 * properly by the compiler
 */



//Libraries
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;

//Functions
void program(queue<string> data);

int main(int argc, char** argv) {
    ifstream read; //This reads in the file inputted in by the user
    queue<string> data; //This queue collects the data of the file inputted in
    //by the user
    string x; //This simply collects the string to push into the data queue
    //Here we open the file inputted in by the user 
    //*Note* Value for now is fixed.
    read.open("C:\\Users\\TraFe\\OneDrive\\Documents\\NetBeansProjects"
    "\\CPSC 323 Project 3 Part 1\\data.txt");
    /*Statement is to simply check if the file is opened, otherwise print an 
     error that it didnt open*/
    if(read.is_open()){
        cout << "Opening data.txt file" << endl;
        //This is to simply collect the data into the file
        while(getline(read,x)){
            data.push(x);
            data.push("\n");
        }
       //Input the data into our program function
        program(data);
    }
    else {
        cout << "Error reading the file" << endl;
    }
    //Close the file to prevent corrupt data.
    cout << "Closing data.txt file" << endl;
    read.close();
    return 0;
}


/*Program function:
 This essentially takes an unformmated queue of data
 from a file and revises it into a formatted output
 to read in to a compiler
 
 *NOTE* *This may need to be checked in future programs
 * Of Outputs not used for the sample run.*
 */
void program(queue<string> data){
    int size = data.size(); //Collects a fixed size of the data queue
    string* d = new string[size]; //This is to simply put the queue of data
    //Into a 2d array of strings
    for(int x = 0; x < size; x++){
        d[x] = data.front();
        data.pop();
    }
    queue<char> revise; //This is essentially the fixed queue of the data
    //inputted in by the user
    /*Nested for loop, simply to loop through each line
     and check every character*/
    for(int x = 0; x < size; x++){
        for(int y = 0; y < d[x].size(); y++){
            //This checks if the line is a comment
            if(d[x][y] == '/'){
                break; //If it is a comment, we break out of the inner for loop
                //To skip the commented line
            }
            else{
                //Otherwise, we need to check if the character is a new line
                //If it is we dont enter it into our revised string
                if(d[x][y] != '\n'){
                //This checks if the character is a white space
                if(d[x][y] == ' '){
                    //If there are other white spaces after
                    //This will skip those white spaces until we hit a character
                    while(d[x][y] == ' '){
                        y++;
                    }
                    //This checks to see if the space is beginning on a newline
                    //In the revised queue. If it is a newline, we do nothing
                    //But push the character
                    if(revise.back() != '\n'){
                        //Otherwise we need to check the inputted character
                   switch(d[x][y]){
                       //For , if their is already a space after the comma,
                       //We don't push a whitespace after the string
                       //Otherwise this will by default push the comma into
                       //the revised string with or without a whitespace after
                       //if needed
                       case ',':
                           revise.push(d[x][y]);
                           if(d[x][y + 1] != ' '){
                               revise.push(' ');
                           }
                           break;
                       /*For operators, there needs to a space before and after
                        so this will check to see if they are needed in the front
                        and the back*/
                        case '=':
                        case '+':
                        case '-':
                        case '/':
                        case '%':   
                            if(revise.back() != ' ');
                            revise.push('  ');
                            revise.push(d[x][y]);
                         //   cout << d[x][y+1] << endl;
                            if(d[x][y+1] != ' ')
                                revise.push('  ');
                            break;
                       /*In the case of a ;, these are essentially how we know
                        to enter a new line, so we input a new whitespace, the 
                        ; character, and push a newline character as well*/
                       case ';':
                           revise.push(' ');
                           revise.push(d[x][y]);
                           revise.push('\n');
                           break;
                       /*Otherwise by default we just push a white space
                        followed by the charcter*/
                       default:
                           revise.push(' ');
                           revise.push(d[x][y]);
                           break;
                   }
                }
                    /*Otherwise if it is a newline, we need to check
                     To make sure it does not enter a /, otherwise we just
                     push whatever the character is*/
                  else{
                        if(d[x][y] != '/')
                       revise.push(d[x][y]);
                   }
                }
                /*Otherwise the character is not a white space, so we need
                 other conditions*/
                else{
                    switch(d[x][y]){
                        /*As explained before, this is essentially how we know
                         to enter a newline, so we push a whitespace followed by
                         the semicolon character, followed by a newline*/
                        case ';':
                            revise.push(' ');
                            revise.push(d[x][y]);
                            revise.push('\n');
                            break;
                        /*In the case of tabs, if we encounter a tab, we simply
                         skip all inputs of more tabs. Then we check to see
                         the input after the tab. If it is a whitespace,
                         we skip that input as well then push a whitespace
                         in replacement of the tab character*/
                        case '\t':
                            while(d[x][y] == '\t'){
                                y++;
                            }
                            if(revise.back() != '\n')
                            revise.push(' ');
                            if(d[x][y] == ' '){
                                while(d[x][y] == ' '){
                                    y++;
                                }
                            }
                            revise.push(d[x][y]);
                            break;
                        /*Operators explained in the first switch case*/
                        case '=':
                        case '+':
                        case '-':
                        case '/':
                        case '%':   
                            if(revise.back() != ' ');
                            revise.push(' ');
                            revise.push(d[x][y]);
                         //   cout << d[x][y+1] << endl;
                            if(d[x][y+1] != ' ')
                                revise.push('.');
                            break;
                            //Otherwise by default we just push the new character
                            // and break out the siwtch statement
                        default:
                       revise.push(d[x][y]); 
                       break;
                    }
                    
                }
        }
        }
    }
    

   
    }
    ofstream fix; //This is the fixed output file
    //Open the file of the fixed data
    fix.open("newdata.txt");
    int b = revise.size(); //Set a fixed size to enter into our for loop
    //To prevent data loss
    
    //If statement is to simply check if the file was opened
    if(fix.is_open()){
        cout << "Opening newdata.txt file" << endl;
        //After fixing the format, we simply just output it into our file
    for(int x = 0; x < b; x++){
        fix << revise.front();
        revise.pop();
    }
    }
    else{
        cout << "Error reading newdata.txt file";
    }
    cout << "Closing newData.txt file" << endl;
    fix.close();
}
        