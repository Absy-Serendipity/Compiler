#pragma once
#include "Node.h"
#include "Code.h"
#include "FDeclaration.h"
#include "VDeclaration.h"
#include "Assign.h"
#include "BinaryExpression.h"
#include "SignOperation.h"
#include "Block.h"
#include "WhileStatement.h"
#include "IfStatement.h"
#include "PrefixExpression.h"
#include "PostfixExpression.h"
#include "FunctionCall.h"
#include "Argument.h"
#include "Condition.h"
#include "LogicExpression.h"
#include "EmptyNode.h"

#include <functional>
#include <stack>

class NodeFactory
{
public:
    static Node* CreateNode(eSymbolName, const std::vector<eSymbolName>&, std::stack<Node*>&);

private:
    static Node* createCode(eSymbolName, const std::vector<eSymbolName>&, std::stack<Node*>&);
    static Node* createFDecl(eSymbolName, const std::vector<eSymbolName>&, std::stack<Node*>&);
    static Node* createParameter(eSymbolName, const std::vector<eSymbolName>&, std::stack<Node*>&);
    static Node* createMoreParameter(eSymbolName, const std::vector<eSymbolName>&, std::stack<Node*>&);
    static Node* createVDecl(eSymbolName, const std::vector<eSymbolName>&, std::stack<Node*>&);
    static Node* createAssign(eSymbolName, const std::vector<eSymbolName>&, std::stack<Node*>&);
    static Node* createExpr(eSymbolName, const std::vector<eSymbolName>&, std::stack<Node*>&);
    static Node* createTerm(eSymbolName, const std::vector<eSymbolName>&, std::stack<Node*>&);
    static Node* createFact(eSymbolName, const std::vector<eSymbolName>&, std::stack<Node*>&);
    static Node* createBlock(eSymbolName, const std::vector<eSymbolName>&, std::stack<Node*>&);
    static Node* createStmt(eSymbolName, const std::vector<eSymbolName>&, std::stack<Node*>&);
    static Node* createPrefixStmt(eSymbolName, const std::vector<eSymbolName>&, std::stack<Node*>&);
    static Node* createPostfixStmt(eSymbolName, const std::vector<eSymbolName>&, std::stack<Node*>&);
    static Node* createFuncCall(eSymbolName, const std::vector<eSymbolName>&, std::stack<Node*>&);
    static Node* createArgument(eSymbolName, const std::vector<eSymbolName>&, std::stack<Node*>&);
    static Node* createMoreArgument(eSymbolName, const std::vector<eSymbolName>&, std::stack<Node*>&);
    static Node* createCond(eSymbolName, const std::vector<eSymbolName>&, std::stack<Node*>&);
    static Node* createCondExpr(eSymbolName, const std::vector<eSymbolName>&, std::stack<Node*>&);
    static Node* createLogicExpr(eSymbolName, const std::vector<eSymbolName>&, std::stack<Node*>&);
    static Node* createElse(eSymbolName, const std::vector<eSymbolName>&, std::stack<Node*>&);
    static Node* createReturn(eSymbolName, const std::vector<eSymbolName>&, std::stack<Node*>&);

private:
    using SemanticAction = std::function<Node* (eSymbolName, const std::vector<eSymbolName>&, std::stack<Node*>&)>;
    static const std::unordered_map<eSymbolName, SemanticAction> sSemanticActions;
};


