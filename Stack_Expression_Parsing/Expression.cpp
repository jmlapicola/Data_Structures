#include <string>
#include <vector>
#include <stack>
#include <sstream>

#include "ExpressionManagerInterface.h"
#include "Expression.h"

using namespace std;

//Value implementation
int Expression::value(void)
{
	//evaluates value using the postfix
	stringstream ss(postfix());
	stack<int> operands;	//stack of integer operands
	//Iterates through postfix elements
	string nextItem;
	while (ss >> nextItem)
	{
		if (operation(nextItem) == 'n')
		{
			operands.push(stoi(nextItem));
		}
		else
		{
			if (operands.size() < 2) throw MISSING_OPERAND;
			//Removes left and right operands
			int right = operands.top();
			operands.pop();
			int left = operands.top();
			operands.pop();
			//Pushes the result of the operation
			switch (operation(nextItem))
			{
			case '+':
				operands.push(left + right);
				break;
			case '-':
				operands.push(left - right);
				break;
			case '/':
				operands.push(left / right);
				break;
			case '*':
				operands.push(left * right);
				break;
			case '%':
				operands.push(left % right);
				break;
			}
		}
	}
	//Checks that only one operand remains and then returns it
	if (operands.size() > 1) throw MISSING_OPERATOR;
	return operands.top();
}

//Infix implementation
string Expression::infix(void)
{
	//Checking that parentheses are balanced
	stringstream ss(expString);
	string nextItem;
	stack<string> parens;
	while (ss >> nextItem)
	{
		if (itemType(nextItem) == 0)
		{
			parens.push(nextItem);
		}
		else if (itemType(nextItem) == 3)
		{
			if (parens.size() == 0 || !matchParen(parens.top(), nextItem))
			{
				throw UNBALANCED;
			}
			else
			{
				parens.pop();
			}
		}
	}
	if (parens.size() != 0) throw UNBALANCED;
	
	//Checking for no missing operand/operator
	ss = stringstream(expString);
	bool followsInt = false;
	bool followsOperator = true; //Initialized as true since no expression may begin with an operator
	while (ss >> nextItem)
	{
		switch (itemType(nextItem)) //Throws error if not a legal operator/operand
		{
		case 1:	// Operator cases
		case 2:		
			if (followsOperator) throw MISSING_OPERAND;
			followsOperator = true;
			followsInt = false;
			break;
		case 4:	// Operand
			if (followsInt) throw MISSING_OPERATOR;
			followsInt = true;
			followsOperator = false;
			break;
		//Cases 0 and 3 (parentheses) are ignored
		}
	}
	if (followsOperator) throw MISSING_OPERAND; //Ends with an incomplete operation

	return expString;
}

//Postfix implementatino
string Expression::postfix(void)
{
	//Variable declaration
	stringstream postfixString;	//Output stream
	stack<string> operators;	//Stack of operators
	stringstream ss(expString);	//Input stream
	//Iterates through each operator and operand in expString
	string nextItem;
	while (ss >> nextItem)
	{
		switch (itemType(nextItem))
		{
		case 0: // Open paren
			operators.push(nextItem);
			break;
		case 1: // Priority level 1 operators (+,-)
		case 2: // Priority level 2 operators (*,/,%)
			//Output all operators that are of EQUAL OR HIGHER priority
			while (operators.size() != 0 && itemType(operators.top()) >= itemType(nextItem)) 
			{
				postfixString << operators.top() << " ";
				operators.pop();
			}
			operators.push(nextItem);
			break;
		case 3: // Close paren
			while (operators.size() > 1 && itemType(operators.top()) > 0)
			{
				postfixString << operators.top() << " ";
				operators.pop();
			}
			if (matchParen(operators.top(), nextItem)) operators.pop();
			else throw UNBALANCED;
			break;
		case 4: // Integer operand
			postfixString << nextItem << " ";
		}
	}
	//Appends remaining operators
	while (operators.size() != 0)
	{
		postfixString << operators.top() << " ";
		operators.pop();
	}
	//Returns output string
	return postfixString.str();
}

//Prefix implementation very similar to postfix
string Expression::prefix(void)
{
	//Variables
	stringstream prefixString;	//Output stream
	stack<string> operators;	//Stack of operators
	//Reversing expString
	string reversed = expString;
	reverse(reversed);
	stringstream ss(reversed);	//New input stream
	//Iterates through each operator and operand in reversed expString
	string nextItem;
	while (ss >> nextItem)
	{
		switch (itemType(nextItem))
		{
		case 0: // Open paren
			operators.push(nextItem);
			break;
		case 1: // Priority level 1 operators (+,-)
		case 2: // Priority level 2 operators (*,/,%)
			//Output all operators that are of STRICTLY HIGHER priority
			while (operators.size() != 0 && itemType(operators.top()) > itemType(nextItem))
			{
				prefixString << operators.top() << " ";
				operators.pop();
			}
			operators.push(nextItem);
			break;
		case 3: // Close paren
			while (operators.size() > 1 && itemType(operators.top()) > 0)
			{
				prefixString << operators.top() << " ";
				operators.pop();
			}
			if (matchParen(operators.top(), nextItem)) operators.pop();
			else throw UNBALANCED;
			break;
		case 4: // Integer operand
			prefixString << nextItem << " ";
		}
	}
	//Appends remaining operators
	while (operators.size() != 0)
	{
		prefixString << operators.top() << " ";
		operators.pop();
	}
	//Returns reversed output string
	string prefixFinal = prefixString.str();
	reverse(prefixFinal);
	return prefixFinal;
}