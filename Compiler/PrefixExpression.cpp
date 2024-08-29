#include "PrefixExpression.h"

PrefixExpression::PrefixExpression(const std::string& op, const std::string& identifier) 
    : Node(eSymbolName::UnaryOp, identifier)
    , mSign(OPERATORS.at(op)) 
{}

void PrefixExpression::Print(const int indentCount) const
{
    for (int i = 0; i < indentCount; i++) 
    {
        std::cout << INDENT;
    }

    std::cout << "PREFIX EXPRESSION: " << STRING_OPERATORS.at(mSign) << GetValue() << std::endl;
}


eDataType PrefixExpression::CheckWellFormedness(ScopedSymbolTable* localSymbolTable) const
{
    return localSymbolTable->GetDataType(GetValue());
}