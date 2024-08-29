#pragma once
#include "Node.h"

class Code final: public Node
{
public:
    Code();
    ~Code() override = default;

    void Print(const int) const override;
    eDataType CheckWellFormedness(ScopedSymbolTable*) const override;
    void Destroy() override;

    void AddDeclaration(Node*);
    void AddDeclarations(const std::vector<Node*>&);
    const std::vector<Node*>& GetDeclarations() const;



private:
    std::vector<Node*> mFunctionDeclarations;
};