# CppLox
A C++ implementation of the  Robert Nystrom's Crafting Interpreters' Lox language, with some modifications

This is an attempt to implement the Lox programming language in C++.

Status:

* 7/22/2021 -- have scanner working, have AST creation for expressions -- can walk an AST for printing expressions back onto screen
    * URGENT TO-DO
        * need to at least get expression evaluation complete.
        
* 7/25/2021 -- Got arithmetical evaluations to work. Need to resolve issue with reading of string concatenation
    * ISSUE RESOLVED 7/27/2021 -- string issue was silly mistake involve std::cin instead of std::getline.

* 7/27/2021 -- Have statement and expression visitors working and program will calculate the value of expressions and one can print
    * URGENT TO-DO
        * Need to fix error where failure to have a semi-colon to terminate the statement ends up not returning the interpreter back to the prompt and instead the program hangs.
