// CppLox.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Visitor.h"

using namespace Lox::Interpreter;
int main()
{
    //AstPrinter ast;
    
    std::unique_ptr<Expr> expression = std::make_unique<BinaryExpr>(
        std::make_unique<UnaryExpr>(
            Token(TokenType::MINUS,"-",nullptr,1),
            std::make_unique<LiteralExpr>(
                std::make_unique<LoxDouble>(LoxDouble(123)))),
        Token(TokenType::STAR,"*",nullptr,1),
        std::make_unique<GroupingExpr>(
            std::make_unique<LiteralExpr>(
                std::make_unique<LoxDouble>(LoxDouble(45.67)))));
    
    //ast.print(*expression);
    //std::cout << le->getLiteral()->toString()<< std::endl;
    //std::unique_ptr<Expr> ge = std::make_unique<GroupingExpr>(le);
    /*std::unique_ptr<Expr> expression = new BinaryExpr(
        new UnaryExpr(
            Token(TokenType::MINUS, "-", nullptr, 1),
            new LiteralExpr(123)),
        Token(TokenType::STAR, "*", nullptr, 1),
        new GroupingExpr(
            new LiteralExpr(45.67)));*/
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
