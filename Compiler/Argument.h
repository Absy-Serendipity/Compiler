#pragma once
#include "Node.h"

class Argument final : public Node
{
public:
    Argument(const eSymbolName, Node*, Node*);
    ~Argument() override = default;

    Node* GetExpression() const;
    Node* GetNextArgument() const;

private:
    Node* mExpression;
    Node* mMoreArgument;
};

