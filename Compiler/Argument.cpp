#include "Argument.h"

Argument::Argument(const eSymbolName symbol, Node* exprssion, Node* moreArgument)
    : Node(symbol)
    , mExpression(exprssion)
    , mMoreArgument(moreArgument) 
{}

Node* Argument::GetExpression() const
{
    return mExpression;
}
Node* Argument::GetNextArgument() const
{
    return mMoreArgument;
}