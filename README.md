Stack Calculator

 Using the C++ programming language (and the GNU g++ compiler), you are to build a stack based (RPN - Reverse Polish Notation) calculator for rational numbers, called Simple Stack Calculator (ssc). Although C++ allows your code to be distributed among multiple files, please put all of your code into a single file (ssc.cc) to make it easier to download and compile. 

Rational numbers could be numerators only (i.e., integers) as well as having a denominator. New numbers are placed on the stack by typing a single value one per line (with no trailing blanks or other characters). The calculator should support the 4 functions of addition (+), subtraction (-), multiplication (*), and division (/). Each of the 4 operations consumes the two top entries on the stack and pushes the result onto the stack (in place of the two consumed arguments). 

Here's the complete list of operations that ssc supports:
Operation	Description
p	Prints the current top entry on the stack (but leaves it on the stack).
P	Pops the stack.
f	Prints the entire stack starting with the top entry (useful for debugging).
c	Pops all items off the stack (i.e., clears the stack).
d	Duplicates the top entry on the stack.
r	Reverses the top two entries on the stack.
+	Replaces the top 2 entries with their sum.
-	The top entry is subtracted from the next item down and the top two stack entries replaced with the result.
*	Replaces the top 2 entries with their product.
/	The top entry is divided into the next item down and the top two stack entries replaced with the result.

Because accuracy is important, ssc keeps its values and results as RationalNumbers, which you should declare as a class, keeping the implementation private and supporting the arithmetic operations by overloading the corresponding int operations. Likewise, printing and input of RationalNumber should overload "<<" and ">>" respectively. Furthermore, the results of numeric operations should be reduced to lowest terms (but NOT as a mixed number). Thus a result like "33/9" should be reduced to "11/3", but NOT "3 and 2/3". 

Your solution should also define a Stack class as a template. It should be able to hold exactly 32 stack entries, and must hide its implementation. 

Beta_20150613: Upload of files as submitted for grading.  