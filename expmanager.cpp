#include "expmanager.hpp"
#include <stack>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <optional>

// takes an open `enclosing glyph` and returns the corresponding closed glyph
std::map<char, char> open_to_closed = {
    { '(', ')' },
    { '[', ']' },
    { '{', '}' }
};

// takes a closed `enclosing glyph` and returns the corresponding open glyph
std::map<char, char> closed_to_open = {
    { ')', '(' },
    { ']', '[' },
    { '}', '{' }
};

// takes an operator and returns the precedence of that operator
std::map<char,int> precedence_map = {
    { '*', 2 },
    { '/', 2 },
    { '+', 1 },
    { '-', 1 }
};

/**
 * removes double spaces from a string
 *
 * @param str the string which should be trimmed
 */
void trim_double_spaces (std::string& str) {
    int pos = str.find("  ");

    // while there are instances of "  " in the string
    while(pos != std::string::npos) {
	// erase one of the spaces in the double space
	str.erase(pos, 1);
	pos = str.find("  ");
    }
}

/**
 * verify parenthesis placement in string
 *
 * iterate through the string searching for pairs of parenthesis, brackets, or
 * braces. ensure that each open parenthesis has a matching closed parenthesis
 * that appears in the correct location. if there is an error in the placement
 * of parenthesis, print an error to the screen and return false.
 *
 * @param str the string which should be validated
 *
 * @return bool true if the string is valid, false otherwise
 */
bool balanced_parens(std::string str) {
    // a stack containing only the parenthesis in the string
    std::stack<char> paren_stack;
    std::string::iterator it;

    // loop through the string
    for(it = str.begin(); it != str.end(); it++) {
	// if an open parenthesis is found
	if (*it == '(' || *it == '[' || *it == '{') {
	    paren_stack.push(*it);
	}
	// if a closed parenthesis is found
	if (*it == ')' || *it == ']' || *it == '}') {
	    // if the parenthesis on the front of the parenstack matches
	    if (*it == open_to_closed[paren_stack.top()]) {
		paren_stack.pop();
	    } else {
		std::cout << "ERROR: mismatched brackets at " << *it << std::endl;
		return false;
	    }
	}
    }

    if(paren_stack.empty()) {
	return true;
    } else {
	std::cout << "ERROR: unclosed bracket\n";
	return false;
    }
}

/**
 * process operators on the operator stack and postfix string
 *
 * when the stack is empty, or the operator is an open `enclosing glyph`, push
 * the operator to the stack.
 *
 * if the precedence of the operator is greater than the precedence of the
 * operator at the top of the stack, push the operator to the stack.
 *
 * if the precedence of the operator is less than or equal to the precedence of
 * the operator at the top of the stack, continuously pop operators off the
 * stack until the top of the stack has a lower precedence to the operator.
 *
 * @param op_stack the stack where operators will be stored and pulled from
 * @param op the operator that should be processed
 * @param postfix_string the modifiable postfix version of the user's string
 */
void process_op (std::stack<char>& op_stack, char op, std::string& postfix_string) {
    if (op_stack.empty()
	|| op == '('
	|| op == '['
	|| op == '{')
    {
	op_stack.push(op);
    } else if (precedence_map[op_stack.top()] < precedence_map[op]) {
	op_stack.push(op);
    } else if (precedence_map[op_stack.top()] >= precedence_map[op]) {
	postfix_string += op_stack.top();
	op_stack.pop();
	process_op(op_stack, op, postfix_string);
    }
}

/**
 * convert string from infix to postfix
 *
 * given str, ensure that the parenthesis are in valid positions. if they are,
 * iterate through the string and put any non-operators into the returned
 * postfix string, and process any operators encountered during the iteration.
 * handle parenthesis and other enclosing glyphs as they should be handled in
 * infix notation. return a version of the postfix string that has been
 * stripped of excess white spaces
 *
 * @param string the string containing an infix expression
 *
 * @return optional<string> either nothing, or a string in postfix form
 */
std::optional<std::string> infix_to_postfix(std::string str) {
    // ensure str has valid parenthesis placement
    if (!balanced_parens(str)) {
	return std::nullopt;
    }

    std::stack<char> op_stack;
    std::string::iterator it;
    std::string postfix_string = "";

    for(it = str.begin(); it != str.end(); it++) {
	// handle closed parenthesis
        if (*it == ')' || *it == ']' || *it == '}') {
	    // loop until matching open parenthesis is found
	    while (!op_stack.empty()
		   && op_stack.top() != closed_to_open[*it]
		   && precedence_map[*it] <= precedence_map[op_stack.top()])
	    {
		postfix_string += ' ';
		postfix_string += op_stack.top();
		op_stack.pop();
	    }
	    // pop the open parenthesis from the stack
	    op_stack.pop();
	} else if (*it == '*'
		   || *it == '/'
		   || *it == '+'
		   || *it == '-'
		   || *it == '('
		   || *it == '['
		   || *it == '{')
	{ // handle operators/parenthesis
	    process_op(op_stack, *it, postfix_string);
	} else { // all other elements are operands. add them to the string
	    postfix_string += *it;
	}
    }

    // place remaining items from the stack onto the string
    while (!op_stack.empty()) {
	postfix_string += ' ';
	postfix_string += op_stack.top();
	op_stack.pop();
    }

    // remove excess spaces from the string
    trim_double_spaces(postfix_string);
    return postfix_string;
}
