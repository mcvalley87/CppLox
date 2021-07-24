// CppLox.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Visitor.h"
#include "Expr.h"
#include "Interpreter.h"
#include "Parser.h"

using namespace Lox::Interpreter;
int main(int argc, char** argv)
{
    /*AstPrinter ast;
    
    std::unique_ptr<Expr> expression = std::make_unique<BinaryExpr>(
        std::make_unique<UnaryExpr>(
            Token(TokenType::MINUS,"-",nullptr,1),
            std::make_unique<LiteralExpr>(
                std::make_unique<LoxDouble>(LoxDouble(123)))),
        Token(TokenType::STAR,"*",nullptr,1),
        std::make_unique<GroupingExpr>(
            std::make_unique<LiteralExpr>(
                std::make_unique<LoxDouble>(LoxDouble(45.67)))));

    std::cout << boost::any_cast<std::string>(ast.print(*expression)) << std::endl;*/
    
    Interpreter interpreter = Interpreter();
    if (argc > 2) {
        std::cout << "Usage: Lox [script]";
        return 64;
    }
    else if (argc == 2) {
        interpreter.runFile(argv[1]);
    }
    else {
        std::cout << "Good Luck, Have Fun\n";
        interpreter.runPrompt();
    }
    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
