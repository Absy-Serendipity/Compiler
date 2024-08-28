#include "IfStatement.h"

void IfStatement::Print(const int indentCount) const
{
    for (int i = 0; i < indentCount; i++) {
        std::cout << INDENT;
    }
    std::cout << STRING_SYMOL_NAMES.at(GetName());
    std::cout << std::endl;
    mCondition->Print(indentCount + 1);
    mBlock->Print(indentCount + 1);
    mElseStatement->Print(indentCount + 1);
}

eDataType IfStatement::CheckWellFormedness(ScopedSymbolTable* localSymbolTable) const
{
    mCondition->CheckWellFormedness(localSymbolTable);

    ScopedSymbolTable* ifBlockSymbolTable = new ScopedSymbolTable(localSymbolTable);
    mBlock->CheckWellFormedness(ifBlockSymbolTable);


    ScopedSymbolTable* elseBlockSymbolTable = new ScopedSymbolTable(localSymbolTable);
    mElseStatement->CheckWellFormedness(elseBlockSymbolTable);

    return eDataType::Void;
}