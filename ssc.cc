/*
Crystal Pendergrass    
CPSC 5135 Programming Languages  
Build a stack based (RPN - Reverse Polish Notation) calculator for rational 
numbers 
*/

#include <iostream>
#include <cctype>
#include <cmath> 

using namespace std; 

// Exception classes 
class UndefinedRational{
	private:
		string errorMessage;
	public:
		UndefinedRational(){
		errorMessage = "Denominator of input is 0";
	}

	string what(){ 
		return errorMessage; 
	}
};

class DivisionByZero{
	private:
		string errorMessage;	
	public:
		DivisionByZero(){
		errorMessage = "Attempt by ssc to divide a number by 0";
	}
	
	string what(){ 
		return errorMessage; 
	}
};

class StackOverflow{
	private:
		string errorMessage;	
	public:
	StackOverflow(){
		errorMessage = "Attempt to push more items onto full stack";
	}

	string what(){ 
		return errorMessage; 
	}
};

class StackUnderflow{
	private:
		string errorMessage;	
	public:
	StackUnderflow(){
		errorMessage = "Attempt to use item(s) from an empty stack";
	}
	
	string what(){ 
		return errorMessage; 
	}
};

class RationalNumber{
   friend RationalNumber operator+(const RationalNumber&, 
   	const RationalNumber&);	
	friend RationalNumber operator-(const RationalNumber&, 
		const RationalNumber&);
	friend RationalNumber operator*(const RationalNumber&, 
		const RationalNumber&);
	friend RationalNumber operator/(const RationalNumber&, 
		const RationalNumber&);
	friend ostream& operator<<(ostream&, const RationalNumber&);

   	private:
		int numerator;
		int denominator;

	public:
		// Empty constructor to make the errors go away
		RationalNumber(){}

		// Constructor that actually matters
		RationalNumber(int n, int d){
			//Correct sign error denominator should never be negative
			if(d < 0){
				numerator = -n;
				denominator = -d;
			}
			else if(d > 0){
				numerator = n;
				denominator = d;
			}
			else
				throw UndefinedRational();
		}

		// Constructor for whole number
		RationalNumber(int n){
				numerator = n;
				denominator = 1;
		}		
		
		//Copy constructor
		RationalNumber(const RationalNumber& rn){
			numerator = rn.numerator;
			denominator = rn.denominator;
		}

		// Assignment
		RationalNumber& operator=(const RationalNumber& rn){
			numerator = rn.numerator;
			denominator = rn.denominator;

			return *this;
		}
};	

// Find the greatest common divisor for two integers
int gcd(int x, int y){
	// must be positive integers
	int a = abs(x);
	int b = abs(y);

	if(a == 0) 
		return b;
	else if(b == 0) 
		return a;
	else if(a > b) 
		return gcd(b, a % b);
	else 
		return gcd(a, b % a);
}

// Addition (result in lowest terms)             
RationalNumber operator+(const RationalNumber& leftRN, 
	const RationalNumber& rightRN){
	int newNumerator = (leftRN.numerator * rightRN.denominator) 
		+ (rightRN.numerator * leftRN.denominator);
	int newDenominator = leftRN.denominator * rightRN.denominator;
	int greatest = gcd(newNumerator, newDenominator);

	newNumerator = newNumerator / greatest;
	newDenominator = newDenominator / greatest;

	RationalNumber rn(newNumerator,newDenominator);

	return rn;
}

// 	Subtraction (result in lowest terms)
RationalNumber operator-(const RationalNumber& leftRN, 
	const RationalNumber& rightRN){
	int newNumerator = (leftRN.numerator * rightRN.denominator) 
		- (rightRN.numerator * leftRN.denominator);
	int newDenominator = leftRN.denominator * rightRN.denominator;
	int greatest = gcd(newNumerator, newDenominator);

	newNumerator = newNumerator / greatest;
	newDenominator = newDenominator / greatest;

	RationalNumber rn(newNumerator,newDenominator);

	return rn;
}

// Multiplication (result in lowest terms)
RationalNumber operator*(const RationalNumber& leftRN, 
	const RationalNumber& rightRN){
	int newNumerator = leftRN.numerator * rightRN.numerator;
	int newDenominator = leftRN.denominator * rightRN.denominator;
	int greatest = gcd(newNumerator, newDenominator);

	newNumerator = newNumerator / greatest;
	newDenominator = newDenominator / greatest;

	RationalNumber rn(newNumerator,newDenominator);

	return rn;
}

// Division (result in lowest terms)
RationalNumber operator/(const RationalNumber& leftRN, 
	const RationalNumber& rightRN){
	int newNumerator = leftRN.numerator * rightRN.denominator;
	int newDenominator = leftRN.denominator * rightRN.numerator;
	
	if(newDenominator == 0)
		throw DivisionByZero();
	else{	
		int greatest = gcd(newNumerator, newDenominator);

		newNumerator = newNumerator / greatest;
		newDenominator = newDenominator / greatest;
		
		RationalNumber rn(newNumerator,newDenominator);
		return rn;
	}	
}

// Output
ostream& operator<<(ostream& output, const RationalNumber& rn){
	if (rn.denominator == 1)
		output << rn.numerator;
	else 
		output << rn.numerator << "/" << rn.denominator;
	
	return output;
}

// Input
istream& operator>>(istream& input, RationalNumber& rn){
	char c;
	int n, d;

	input >> n;

	// if number is followed by whitespace then it is an integer
	// http://www.cplusplus.com/reference/cctype/isspace/?kw=isspace
	if(isspace( input.peek() ))
		d = 1;
		//RationalNumber r(n);
	
	else{
		input >> c;
		input >> d;
		//RationalNumber r(n, d);
	}
	// input >> n >> c >> d;
	RationalNumber r(n, d);
	rn = r;
	return input;
}

// define a Stack class as a template. It should be able to hold exactly 32
// stack entries, and must hide its implementation
template <typename T>
class Stack {
	// Prints entire stack (one entry per line) starting with the top
	// most entry.
	friend ostream& operator<<(ostream& print, const Stack<T>& s){
		if(!s.empty()){
		for (int i = s.stackTop; i > -1; i--)
			print << s.stackArray[i] << "\n";

		return print;
	}
}

	private:
		static const int CAPACITY = 32; 
		T stackArray[CAPACITY];
		int stackTop; 

	public:
		Stack();
		void pop();
		void push(const T);
		T top();

		// True iff the stack is empty. 
		bool empty() const{
			return (stackTop == -1);
		}

		// True iff the stack is full.
		bool full() const{
			return (stackTop == CAPACITY - 1);
		}
};

// Stack constructor
template < typename T >
Stack<T>::Stack(){
	stackTop = -1;
} 

// Removes the top entry from the stack.
template < typename T >
void Stack<T>::pop(){
	if (empty())
		throw StackUnderflow();
	else
		stackTop--;
}

// Pushes a new entry onto the stack.
template < typename T >
void Stack<T>::push(const T t){
	if (full())
		throw StackOverflow();
	else {
		++stackTop;
		stackArray[stackTop] = t;
	}
}

// Returns the current top of the stack.
template < typename T >
T Stack<T>::top(){
	if (empty())
		throw StackUnderflow();
	else
		return stackArray[stackTop];
}

int main(){
	Stack<RationalNumber> s;
	char c, ch; 
	RationalNumber leftOperand, rightOperand, result; 
	bool calculating = true;

	try{
		while (calculating){
		// Skipping all whitespace characters until a non-whitespace character 
		// is found	
		// http://www.cplusplus.com/reference/istream/ws/	
		c = (cin >> ws).peek(); 
		// if at end of file exit
		if (cin.eof()){
			calculating = false;
			return 0;
		}
			switch (c){
				// Prints the current top entry on the stack (but leaves it
				// on the stack).
				case 'p':
					cin >> ch;
					try {
						cout << s.top() << "\n";
					}
					catch(StackUnderflow &stackUnderflow){
					// Indicate problem to user (stack remains unchanged).
					cout << "Exception occurred: " << stackUnderflow.what() 
						<< "\n";
					}					
					break;
				// Pops the stack.	
				case 'P':
					cin >> ch;
					try {
						s.pop();
					}
					catch(StackUnderflow &stackUnderflow){
					// Indicate problem to user (stack remains unchanged).
					cout << "Exception occurred: " << stackUnderflow.what() 
						<< "\n";
					}					
					break;
				// Prints the entire stack starting with the top entry 
				//	(useful for debugging).	
				case 'f':
					cin >> ch;
					cout << s;
					break;
				// Pops all items off the stack (i.e., clears the stack).	
				case 'c': 
					cin >> ch;
					while (!s.empty())
						s.pop();
					break;
				// Duplicates the top entry on the stack.					
				case 'd':
					cin >> ch;
					try {
						// RationalNumber rn(s.top());
						// s.push(rn);
						s.push(s.top());
					}
					catch(StackOverflow &stackOverflow){
						// Indicate problem to user (stack remains unchanged).
						cout << "Exception occurred: " << stackOverflow.what() 
							<< "\n";
					}						
					break;	
				// Reverses the top two entries on the stack.					
				case 'r':
					cin >> ch;
					try{
						leftOperand = s.top();
						s.pop();
						rightOperand = s.top();
						s.pop();
						s.push(leftOperand);
						s.push(rightOperand);
					}
					catch(StackUnderflow &stackUnderflow){
					// Indicate problem to user (stack remains unchanged).
					cout << "Exception occurred: " << stackUnderflow.what() 
						<< "\n";
					}					
					break;
				// Replaces the top 2 entries with their sum.	
				case '+':
					cin >> ch;
					try {
						leftOperand = s.top();
						s.pop();
						rightOperand = s.top();
						s.pop();

						result = leftOperand + rightOperand;
						s.push(result);
					}
					catch(StackUnderflow &stackUnderflow){
					// Indicate problem to user (stack remains unchanged).
					cout << "Exception occurred: " << stackUnderflow.what() 
						<< "\n";
					}					
					break;
				// The top entry is subtracted from the next item down and
				// the top two stack entries replaced with the result.	
				case '-':
					cin >> ch;
					try {
						leftOperand = s.top();
						s.pop();
						rightOperand = s.top();
						s.pop();

						result = rightOperand - leftOperand;
						s.push(result);
					}
					catch(StackUnderflow &stackUnderflow){
					// Indicate problem to user (stack remains unchanged).
					cout << "Exception occurred: " << stackUnderflow.what() 
						<< "\n";
					}					
					break;
				// Replaces the top 2 entries with their product.	
				case '*':
					cin >> ch;
					try {
						leftOperand = s.top();
						s.pop();
						rightOperand = s.top();
						s.pop();

						result = leftOperand * rightOperand;
						s.push(result);
					}
					catch(StackUnderflow &stackUnderflow){
					// Indicate problem to user (stack remains unchanged).
					cout << "Exception occurred: " << stackUnderflow.what() 
						<< "\n";
					}
					break;
				// 	The top entry is divided into the next item down and the
				//  top two stack entries replaced with the result.
				case '/':
					cin >> ch;
					try {
						leftOperand = s.top();
						s.pop();
						rightOperand = s.top();
						s.pop();
					
						try{
							result = rightOperand / leftOperand;
							s.push(result);
						}
						catch(DivisionByZero &divisionByZero){
							// Restore the stack to its state prior to the 
							// computation. Report problem to user.
							cout << "Exception occurred: " << divisionByZero.what()
								<< "\n";
							s.push(rightOperand);
							s.push(leftOperand);
						}
					}
					catch(StackUnderflow &stackUnderflow){
					// Indicate problem to user (stack remains unchanged).
					cout << "Exception occurred: " << stackUnderflow.what() 
						<< "\n";
					}	
					break;
				default:
					try{
						// Check if character is decimal digit
						// http://www.cplusplus.com/reference/cctype/isdigit/
						// ?kw=isdigit
						if (isdigit(c)){
							cin >> leftOperand;
							s.push(leftOperand);
						}
						else {
						cin >> ch;
						calculating = false;
						}
					}
					catch(StackOverflow &stackOverflow){
						// Indicate problem to user (stack remains unchanged).
						cout << "Exception occurred: " << stackOverflow.what() 
							<< "\n";
					}
			} 	
			}
		}
		catch(UndefinedRational &undefinedRational){
			// Indicate error to user and don't push value to the stack.
			// "Clear" input for next user entry.
			cout << "Exception occurred: " << undefinedRational.what() << "\n";
		}		

	return 0;
}
