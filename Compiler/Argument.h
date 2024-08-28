#pragma once
#include "Node.h"

class Argument : public Node
{
public:
    Argument(eSymbolName symbol, Node* exprssion, Node* moreArgument) : Node(symbol), mExpression(exprssion), mMoreArgument(moreArgument) {}
    Node* GetExpression() const;
    Node* GetNextArgument() const;

private:
    Node* mExpression;
    Node* mMoreArgument;
};

