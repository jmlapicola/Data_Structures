#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <string>
#include <vector>
#include <stack>

using namespace std;

//Possible exceptions are enumerated
const int ILLEGAL_OPERATOR = 0;
const int MISSING_OPERAND = 1;
const int MISSING_OPERATOR = 2;
const int UNBALANCED = 3;

//Expression class
class Expression:
{
private:
	//String containing the expression
	string expString;

	//Returns true if the input string is an int
	bool isInt(string str)
	{
		try
		{
			int n = stoi(str);
			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	//Checks if open and close parentheses match
	bool matchParen(string openParen, string closeParen)
	{
		return (openParen == "{" && closeParen == "}" ||
			openParen == "[" && closeParen == "]" ||
			openParen == "(" && closeParen == ")");
	}

	//Returns an integer based on type of operator/operand
	int itemType(string item)
	{
		if (item == "(" || item == "{" || item == "[") return 0;	//Open paren
		else if (item == "+" || item == "-") return 1;	//Priority 1 operators
		else if (item == "*" || item == "/" || item == "%") return 2;	//Priority 2 operators
		else if (item == ")" || item == "}" || item == "]") return 3;	//Close paren
		else if (isInt(item)) return 4;	//Integers (operands)
		else throw ILLEGAL_OPERATOR;	//Exceptions
	}

	//Returns a single character representing the operator/operand
	char operation(string item)
	{
		if (isInt(item)) return 'n';
		else return item[0];
	}

	//Reverses an expression (reversing the direction of parentheses
	void reverse(string& exString)
	{
		stringstream ss(exString);
		exString = "";
		string nextItem;
		while (ss >> nextItem)
		{
			if (nextItem == "(") exString = ") " + exString;
			else if (nextItem == ")") exString = "( " + exString;
			else if (nextItem == "{") exString = "} " + exString;
			else if (nextItem == "}") exString = "{ " + exString;
			else if (nextItem == "[") exString = "] " + exString;
			else if (nextItem == "]") exString = "[ " + exString;
			else exString = nextItem + " " + exString;
		}
	}

public:
	/** Constructor (default Destructor)*/
	Expression(string s) : expString(s) {};

	/** Return the integer value of the infix expression */
	virtual int value(void);

	/** Return the infix items from the expression
	Throw an error if the expression
	1) is not balanced.
	2) the number of operators IS NOT one less than the number of operands.
	3) there are adjacent operators. */
	virtual string infix(void);

	/** Return a postfix representation of the infix expression */
	virtual string postfix(void);

	/** (BONUS) Return a prefix representation of the infix expression */
	virtual string prefix(void);

	/** Return the infix vector'd expression items */
	virtual string toString() const
	{
		return expString;
	}

};
#endif	// EXPRESSION