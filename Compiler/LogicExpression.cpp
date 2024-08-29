#include "LogicExpression.h"

void LogicExpression::Print(const int indentCount) const
{
    for (int i = 0; i < indentCount; i++) 
    {
        std::cout << INDENT;
    }
    std::cout << STRING_SYMOL_NAMES.at(GetName());
    std::cout << ", LOGIC OPERATOR: " << STRING_OPERATORS.at(mSign) << std::endl;

    mCondition->Print(indentCount + 1);
}

eDataType LogicExpression::CheckWellFormedness(ScopedSymbolTable* localSymbolTable) const
{
    return mCondition->CheckWellFormedness(localSymbolTable);
}

void LogicExpression::Destroy()
{
	mCondition->Destroy();
    delete this;
}
