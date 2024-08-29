#include "Condition.h"

Condition::Condition(Node* conditionExpression, Node* logicExpression) 
    : Node(eSymbolName::COND) 
    , mConditionExpression(conditionExpression)
    , mLogicExpression(logicExpression)
{}


void Condition::Print(const int indentCount) const
{
    for (int i = 0; i < indentCount; i++) 
    {
        std::cout << INDENT;
    }
    std::cout << STRING_SYMOL_NAMES.at(GetName());
    std::cout << std::endl;
    mConditionExpression->Print(indentCount + 1);
    mLogicExpression->Print(indentCount + 1);
}


eDataType Condition::CheckWellFormedness(ScopedSymbolTable* localSymbolTable) const
{
    if (mConditionExpression->CheckWellFormedness(localSymbolTable) == eDataType::Bool) 
    {
        if (mLogicExpression->CheckWellFormedness(localSymbolTable) == eDataType::Bool || mLogicExpression->Empty()) 
        {
            return eDataType::Bool;
        }
    }

    throw std::runtime_error("Condition must be boolean");
}

void Condition::Destroy()
{
	mConditionExpression->Destroy();
	mLogicExpression->Destroy();
    delete this;
}