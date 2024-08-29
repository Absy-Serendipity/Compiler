#pragma once
#include "Node.h"

class VDeclaration final: public Node
{
public:
    VDeclaration(const std::string&, const std::string&, const std::optional<Node*>&);
    VDeclaration(const eDataType, const std::string&, const std::optional<Node*>&);
    ~VDeclaration() = default;

    void Print(const int) const override;
    eDataType CheckWellFormedness(ScopedSymbolTable*) const override;
	void Destroy() override;

private:
    eDataType mType;
    std::optional<Node*> mAssignStatement;
};