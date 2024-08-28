#pragma once
#include "SyntaxAnalyzer.h"
#include <iostream>
#include <fstream>
#include <sstream>

int main()
{
    std::ifstream file("sample.c");
    
    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }


    std::stringstream buffer;
    buffer << file.rdbuf();

    file.close();

    std::string contents = buffer.str();
    std::cout << contents << std::endl;

    LexicalAnalyzer lexicalAnalyzer(contents);
    SyntaxAnalyzer syntaxAnalyzer;
    
    Node* syntaxTree = syntaxAnalyzer.Analyze(lexicalAnalyzer);
    

    syntaxTree->Print(0);

    syntaxTree->CheckWellFormedness(nullptr);

	SymbolTable& symbolTable = SymbolTable::GetInstance();
	symbolTable.Print();
   
    return 0;
}