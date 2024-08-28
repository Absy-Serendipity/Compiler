#pragma once
#include "Node.h"

class Parameter : public Node
{
public:
    Parameter(eSymbolName symbol, const std::string& type, const std::string& identifier, Node* moreParameter) :
        Node(symbol, identifier), mMoreParameter(moreParameter), mType(DATA_TYPES.at(type)) {}

    eDataType GetType() const;
    Node* GetNextParameter() const;

private:
    eDataType mType;
    Node* mMoreParameter;
};