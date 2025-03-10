/*
 * Name: Reeves Farrell
 * Date Submitted: Due: 2/6/23
 * Lab Section: 005
 * Assignment Name: Lab 2: Infix to Postfix Conversion
 */

#include <iostream>
#include <string>
#include <stack>

using namespace std;

//Converts an infix arithmetic expression into postfix
//The function takes 3 parameters
//First parameter: array of strings for infix expression
//    each string is either an integer number or operator symbol
//Second parameter: number of strings in infix expression
//Third parameter: array of strings for postfix expression
//    generated by function, same format as first parameter
//    assumes that postfix is at least the size of postfix
//Return value: int, number of strings in postfix expression
//    Returns 0 if an error is encountered when converting expression
//    An error occurs with a mismatched parenthesis, e.g. ( ( ) or ( ) ) etc.
//Operator symbols:
// ( : left parenthesis, all operations between this and ")" take place first
// ) : right parenthesis, all op.s back to previous "(" take place first
// * : multiplication, higher precedence - takes place before "+" and "-"
// / : division, higher precedence - takes place before "+" and "-"
// % : remainder, higher precedence - takes place before "+" and "-"
// + : addition, lower precedence - takes place after "*" , "/" , "%"
// - : subtraction, lower precedence - takes place after "*" , "/" , "%"
//The function is not specified to work with any other operator symbols
//Any string in infix may be assumed to be an integer operand if none
// of the above symbols
int infixToPostfix(string infix[], int length, string postfix[])
{

    // Order of operations flags
    int np = 0; 
    int op = 0;

    // Creates a stack for numbers
    stack<string> numStack;

    // Creates a operator stack
    stack<string> opStack;

    for (int i = 0; i < length; i++) {

        string x = infix[i];

        // Checks if it is a number
        if (x != "+" && x != "-" && x != "*" && x != "/" && x != "%" && x != "(" && x != ")") {

            numStack.push(infix[i]);
        }
        else if (x == "+" || x == "-" || x == "*" || x == "/" || x == "%") {

            // Adds to the top if empty
            if (opStack.empty()) {

                opStack.push(infix[i]);
            }
            else {
                
                // Creates comparison variables
                if (x == "%" || x == "/" || x == "*") {

                    np = 3;
                }
                else if (x == "+" || x == "-") {

                    np = 2;
                }
                else {

                    np = 1;
                }

                if (opStack.top() == "%" || opStack.top() == "/" || opStack.top() == "*") {

                    op = 3;
                }
                else if (opStack.top() == "+" || opStack.top() == "-") {

                    op = 2;
                }
                else {

                    op = 1;
                }

                // Pushs top of the opStack to the numStack if precedence is met
                while (opStack.size() != 0 && opStack.top() != "(" && (np < op)) {
                
                    // Copies top of opStack to numStack
                    numStack.push(opStack.top());

                    // Pops opStack
                    opStack.pop();
                }

                // Checks for equal precedence
                if (np == op) {

                    // Copies top of opStack to numStack
                    numStack.push(opStack.top());

                    // Pops opStack
                    opStack.pop();
                }

                opStack.push(infix[i]);
            }       
        }
        else if (x == "(") {
            
            opStack.push(infix[i]);
        }
        else if (x == ")") {

            while (opStack.top() != "(") {
                
                // Copies top of opStack to numStack
                numStack.push(opStack.top());

                // Pops opStack
                opStack.pop();

                // Returns error if no left para
                if (opStack.empty()) {

                    return 0;
                }
            }

            opStack.pop();
        }
    }

    while (!opStack.empty()) {

        // Copies top of opStack to numStack
        numStack.push(opStack.top());

        // Pops opStack
        opStack.pop();
    }

    // Int to loop for the stack
    int stackSize = numStack.size() - 1;
    int flag = 0;

    while (!numStack.empty()) {

        // Checks for open para
        // If so, return 0
        if (numStack.top() == "(") {

            return 0;
        }

        postfix[stackSize] = numStack.top();

        stackSize = stackSize - 1;
        flag = flag + 1;

        numStack.pop();
    }   

    return flag;
}

//Main function to test infixToPostfix()
//Should convert 2 + 3 * 4 + ( 5 - 6 + 7 ) * 8
//            to 2 3 4 * + 5 6 - 7 + 8 * +
int main()
{
    string infixExp[] = {"2", "+", "3", "*", "4", "+", "(",
                         "5", "-", "6", "+", "7", ")", "*",
                         "8"};
    string postfixExp[15];
    int postfixLength;

    cout << "Infix expression: ";
    for (int i=0; i<15; i++)
    {
        cout << infixExp[i] << " ";
    }
    cout << endl;
    cout << "Length: 15" << endl << endl;

    postfixLength = infixToPostfix(infixExp, 15, postfixExp);
    
    cout << "Postfix expression: ";
    for (int i=0; i<postfixLength; i++)
    {
        cout << postfixExp[i] << " ";
    }
    cout << endl;
    cout << "Length: " << postfixLength << endl;
    
    return 0;
}