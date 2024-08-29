#pragma once
#include "Node.h"
#include "Parameter.h"
#include "VDeclaration.h"

class FDeclaration final: public Node
{
public:
    FDeclaration(const std::string&, const std::string&, Node*, Node*, Node*);
    ~FDeclaration() override = default;

    void Print(const int) const override;
    eDataType CheckWellFormedness(ScopedSymbolTable*) const override;
	void Destroy() override;
    
private:
    eDataType mReturnType;
    std::vector<Node*> mParameters;
    Node* mBlock;
    Node* mReturnStatement;
};