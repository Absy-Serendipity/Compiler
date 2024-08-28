#include "WhileStatement.h"


void WhileStatement::Print(const int indentCount) const
{
    for (int i = 0; i < indentCount; i++) {
        std::cout << INDENT;
    }
    std::cout << STRING_SYMOL_NAMES.at(GetName());
    std::cout << std::endl;
    mConditionStatement->Print(indentCount + 1);
    mBlock->Print(indentCount + 1);
}

eDataType WhileStatement::CheckWellFormedness(ScopedSymbolTable* localSymbolTable) const
{
    if (mConditionStatement->CheckWellFormedness(localSymbolTable) != eDataType::Bool) {
        throw std::runtime_error("While condition must be boolean");
    }

    ScopedSymbolTable* localBlockSymbolTable = new ScopedSymbolTable(localSymbolTable);
    mBlock->CheckWellFormedness(localBlockSymbolTable);

    return eDataType::Void;
}