#include "PrefixExpression.h"

void PrefixExpression::Print(const int indentCount) const
{
    for (int i = 0; i < indentCount; i++) {
        std::cout << INDENT;
    }

    std::cout << "PREFIX EXPRESSION: " << STRING_OPERATORS.at(mSign) << GetValue() << std::endl;
}
eDataType PrefixExpression::CheckWellFormedness(ScopedSymbolTable* localSymbolTable) const
{
    return localSymbolTable->GetDataType(GetValue());
}