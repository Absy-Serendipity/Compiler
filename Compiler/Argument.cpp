#include "Argument.h"

Node* Argument::GetExpression() const
{
    return mExpression;
}
Node* Argument::GetNextArgument() const
{
    return mMoreArgument;
}