#pragma once
#include "Node.h"

class Parameter final: public Node
{
public:
    Parameter(const eSymbolName, const std::string&, const std::string&, Node*);
	~Parameter() override = default;

    eDataType GetType() const;
    Node* GetNextParameter() const;
    
private:
    eDataType mType;
    Node* mMoreParameter;
};