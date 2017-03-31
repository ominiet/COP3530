#include <stdio.h>
#include <math.h>
#include <cmath>
#include <iostream>
#include <cctype>
#include <string>
#include <stack>
#include <unordered_map>

#define PI 3.14159
#define E 2.718

int getPrec(char a){//rules for precedence
	if (a == '^') return 3;
	if (a == '*' || a == '/') return 2;
	if (a == '+' || a == '-') return 1;
	else return 0;
}
int goesFirst(char x, char stacktop){//checks to see if x goes before stacktop
	if (getPrec(x) > getPrec(stacktop)) return 1;//true if next to be pushed goes before the one on top of the stack
	if (getPrec(x) == 3 && getPrec(stacktop) == 3) return 1;// if they are both exponents x has precedence bc its rtl asoc
	return 0;
}
int isNumber(char ch){ 	//helps skip over numbers that are converted 
	switch (ch){
		case '1': return 1;
		case '2': return 1;
		case '3': return 1;
		case '4': return 1;
		case '5': return 1;
		case '6': return 1;
		case '7': return 1;
		case '8': return 1;
		case '9': return 1;
		case '0': return 1;
		case '.': return 1;
	}
	return 0;
}
int isOp(char ch){	//supported operations
	switch (ch){
		case '^': return 1;
		case '*': return 1;
		case '/': return 1;
		case '+': return 1;
		case '-': return 1;
		case '(': return 1;
		case ')': return 1;
	}
	return 0;
}
int isWhite(char ch){// helps to ignore whitespace
	switch (ch){
		case ' ': 
		return 1;
		case '\t':
		return 1;
		case '\n': return 1;
		case '\v': return 1;
		case '\f': return 1;
		case '\r': return 1;
	}
	return 0;
}
double doOp(std::stack<double> *numbs, std::stack<char> *ops){//pops two from numbs stack and applies most recent operation
	double sol = 0;//to hold the answer
	double a,b;
	b = numbs->top();//the most recently pushed double (right number)
	numbs->pop();
	a = numbs ->top();//second most recent double (left number)
	numbs->pop();

	switch (ops->top()){
		case '+': sol = a+b;
		break;
		case '-': sol = a-b;
		break;
		case '/': if(b == 0) {//checks for case of divide by zero and pushes NAN to top of stack if needed
			std::cout << "Division-By-Zero\n";
			sol = NAN;
		}
		else sol = a/b;
		break;
		case '*': sol = a*b;
		break;
		case '^': sol = pow(a,b);
		break;
	}
	ops->pop();
	numbs->push(sol);//push this back onto the stack (essentially replacing the a op b with sol)
	return sol;
}
double calculate(std::string input, std::unordered_map<std::string,double>  * varspoint){
	double value = NAN;
	std::unordered_map<std::string,double> vars;
	int x = 0;
	bool grabbing = false;
	std::string alpha = "";
	double a,b;

	std::stack<double> *numbs = new std::stack<double>;
	std::stack<char> *ops = new std::stack<char>;
	//TOKENIZE NUMBERS
	while (input.size()){//runs until input size is 0
		if (!isNumber(input.at(x))) {//stops loop that eliminates number chars at the end of the number
			grabbing = false;
		}
		if (isNumber(input.at(x))){
			if (!grabbing){ 		//goes out of bouds if last char isNumber
				double value = atof(input.c_str());//converts the string into a double (autostops at end of num)
				numbs->push(value);//place value on top of stack ALWAYS (rules change for ops)
				grabbing = true;
			}
		} 
		//TOKENIZE OPERATION SYMBOLS
		else if (isOp(input.at(x))){
			if (input.at(x) == '('){//always push these into the stack
				ops->push(input.at(x));
			}
			else if(input.at(x) == ')'){//do operations from right to left (should be in correct order within parenthesis)
				while(ops->top() != '(' && !ops->empty()){
					doOp(numbs,ops);
					if (isnan(numbs->top())) return NAN;//returns NAN (to supress output) if Divde-by-zero happens
				}
				ops->pop(); 	//should eliminate left parenthesis	
			}

			else { 		//should be if it is any of the math multipliers
				while(!ops->empty() && !goesFirst(input.at(x),ops->top())){	//if top of stack goes first or is the same, do ops until
					doOp(numbs,ops);										//x goes first then push to stack
					if (isnan(numbs->top())) return NAN;
				}
				ops->push(input.at(x));
			}	
		}
		//TOKENIZE STRINGS (WILL NOT SUPPORT NAMES WITH SPACES)
		else if(isalpha(input.at(x))){
			int y = 0;
			while (y < input.size() && isalpha(input.at(y))){//finds the size of the substring containing consecutive letters
				alpha += input.at(y);
				y++;
			}
			if (alpha == "Pi") numbs->push(PI);//Pushes constants
			else if (alpha == "e") numbs->push(E);

			else if (alpha=="sin"){ 
				std::string solve = "";
				int evenPar = 1;
				int z = 4;
				
				while(evenPar != 0){//waits until an even set of parentheses is found 
					if (input.at(z) == '(' ){ 	//starts iterating after first ( 
						evenPar ++;//left adds to total, right subtracts
					}
					else if (input.at(z) == ')') evenPar --;
					z++;
				}
				int solveLen = z-3;	//the size of the expression needed to calculate before performing trig
				numbs->push(sin(calculate(input.substr(3,solveLen),varspoint)));//caluculates whats within parenthesis for sin
				input = input.substr(solveLen,input.size()-solveLen);			//cuts the length of the expression off of the string
			}																	//(the size of sin will be cut off later)

			else if (alpha == "cos"){	//same exact concept as above
				std::string solve = "";
				int evenPar = 1;
				int z = 4;

				while(evenPar != 0){//waits until an even set of parentheses is found 
					if (input.at(z) == '('){ 	//starts iterating after first ( 
						evenPar ++;//left adds to total, right subtracts
					}
					else if (input.at(z) == ')') evenPar --;
					z++;
				}
				int solveLen = z-3;	//helps to see what is going on in next two lines
				numbs->push(cos(calculate(input.substr(3,solveLen),varspoint)));	//calculates whats within parenthesis
				input = input.substr(solveLen,input.size()-solveLen);				//cuts off size of exp 
			}																		//cos gets cut later
			else if (alpha == "log"){
				std::string solve = "";
				int evenPar = 1;	
				int z = 4;
				
				while(evenPar != 0){//waits until an even set of parentheses is found 
					if (input.at(z) == '('){ 	//starts iterating after first ( 
						evenPar ++;//left adds to total, right subtracts
					}
					else if (input.at(z) == ')') evenPar --;
					z++;
				}
				int solveLen = z-3;//helps see below
				numbs->push(log(calculate(input.substr(3,solveLen),varspoint)));//calc parenthesis
				input = input.substr(solveLen,input.size()-solveLen);			//cut of size of par but not log (later)
				
			}
			else {
				std::unordered_map<std::string,double>::const_iterator got = varspoint->find (alpha);
				//iterator above for hash map
 	 			if ( got == varspoint->end() ){
    			std::cout << "Undeclared-Variable\n";
    			return NAN;//returns NAN if not found yet
    			}
  				else {
    			numbs->push(got->second);//places it on top of numbs stack if it is in the Map
    			}
			}
			input = input.substr(y-1,input.size()-y+1);

			alpha = "";	//resets alpha bc was too lazy to make it in the scope of this 'else if'
						//this was way more typing but now it's out of principle
		}
		input = input.substr(1,input.size()-1);//removes 1 char from string until the string dies
		
	}

	while (!ops->empty()){	//completes leftover operations. (should be in ascending order of precedence)
		doOp(numbs, ops);
		if (isnan(numbs->top())) return NAN;//returns NAN to help supress output
	}
	if(!numbs->empty()) value = numbs->top();//if numbs is empty then the final Value must be NAN

	return value;//final return value
}

int main(){
	std::string input = "";	//place to hold your input
	std::unordered_map<std::string,double>  vars;//hash-map for all variables
	std::unordered_map<std::string,double>  * varspoint = &vars;//creating the pointer to pass by reference to the calculate function
	double sol = NAN;											//pretty sure that has less copying to do at each function call
	
	while (!(input == "quit")){	//runs until you type quit
		std::getline(std::cin, input);//gets whole line includeing all whitespaces entered
		
		if (input.substr(0,4) == "let "){//if the statement is an assignment
			int x = 4;
			std::string aKey = "";
			while (isalpha(input.at(x))){//gets name of variable
				aKey += input.at(x);
				x++;
			}
			vars[aKey] = calculate(input.substr(x+2,input.size()-(x+2)),varspoint);//sets Key/value pair for the map
		}
		else if(!(input == "quit")){	//if it isn't an assignment and you havent typed quit calculate the solution
			sol = calculate(input,varspoint);
			if (!(std::isnan(sol))){//if the output is NAN dont print anything (there was an error)
				std::cout << sol << "\n";//if it isn't print out your solution
			}	
		}
	}
	return 0;
}
