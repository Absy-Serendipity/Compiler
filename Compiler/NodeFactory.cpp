#include "NodeFactory.h"

Node* NodeFactory::CreateNode(eSymbolName lhs, const std::vector<eSymbolName>& rhs, std::stack<Node*>& leftSubstring)
{
	if (rhs.empty()) {
		return new EmptyNode(lhs);
	}
	return sSemanticActions.at(lhs)(lhs, rhs, leftSubstring);
}

Node* NodeFactory::createCode(eSymbolName lhs, const std::vector<eSymbolName>& rhs, std::stack<Node*>& leftSubstring)
{
	Code* code = new Code;
	
	for (int i = 0; i < rhs.size(); i++) {
		Node* child = leftSubstring.top(); leftSubstring.pop();
		if (child->Empty()) {
			delete child;
		}
		else if (child->GetName() == eSymbolName::FDECL) {
			code->AddDeclaration(child);
		}
		else if (child->GetName() == eSymbolName::CODE) {
			code->AddDeclarations(static_cast<Code*>(child)->GetDeclarations());
			delete child;
		}
	}
	return code;
}


Node* NodeFactory::createFDecl(eSymbolName lhs, const std::vector<eSymbolName>& rhs, std::stack<Node*>& leftSubstring)
{
	delete leftSubstring.top(); leftSubstring.pop(); // rbrace
	Node* returnExpression = leftSubstring.top(); leftSubstring.pop();
	Node* block = leftSubstring.top(); leftSubstring.pop();
	delete leftSubstring.top(); leftSubstring.pop(); // lbrace
	delete leftSubstring.top(); leftSubstring.pop(); // rparen
	Node* parameter = leftSubstring.top(); leftSubstring.pop();
	delete leftSubstring.top(); leftSubstring.pop(); // lparen
	Node* identifier = leftSubstring.top(); leftSubstring.pop();
	Node* returnType = leftSubstring.top(); leftSubstring.pop();
	FDeclaration* functionDeclaration = new FDeclaration(returnType->GetValue(), identifier->GetValue(), parameter, block, returnExpression);

	delete returnType;
	delete identifier;
	return functionDeclaration;
}

Node* NodeFactory::createParameter(eSymbolName lhs, const std::vector<eSymbolName>& rhs, std::stack<Node*>& leftSubstring)
{
	Node* nextParameter = leftSubstring.top(); leftSubstring.pop();
	Node* identifier = leftSubstring.top(); leftSubstring.pop();
	Node* type = leftSubstring.top(); leftSubstring.pop();

	Parameter* parameter = new Parameter(lhs, type->GetValue(), identifier->GetValue(), nextParameter);
	delete type;
	delete identifier;

	return parameter;
}

Node* NodeFactory::createMoreParameter(eSymbolName lhs, const std::vector<eSymbolName>& rhs, std::stack<Node*>& leftSubstring)
{
	Node* moreParemeter = leftSubstring.top(); leftSubstring.pop();
	Node* identifier = leftSubstring.top(); leftSubstring.pop();
	Node* type = leftSubstring.top(); leftSubstring.pop();
	delete leftSubstring.top(); leftSubstring.pop(); // comma

	Parameter* parameter = new Parameter(lhs, type->GetValue(), identifier->GetValue(), moreParemeter);
	delete type;
	delete identifier;

	return parameter;
}

Node* NodeFactory::createVDecl(eSymbolName lhs, const std::vector<eSymbolName>& rhs, std::stack<Node*>& leftSubstring)
{
	delete leftSubstring.top(); leftSubstring.pop(); // semi
	Node* secondNode = leftSubstring.top(); leftSubstring.pop(); // Identifier or ASSIGN
	Node* type = leftSubstring.top(); leftSubstring.pop();

	Node* vDecl = nullptr;
	if (secondNode->GetName() == eSymbolName::Identifier) {
		Node* identifier = secondNode;
		vDecl = new VDeclaration(type->GetValue(), identifier->GetValue(), std::nullopt);
	}
	if (secondNode->GetName() == eSymbolName::ASSIGN) {
		Assign* assignStatement = static_cast<Assign*>(secondNode);
		vDecl = new VDeclaration(type->GetValue(), assignStatement->GetValue(), assignStatement->GetExpression());
	}

	delete secondNode;
	delete type;

	return vDecl;
}

Node* NodeFactory::createAssign(eSymbolName lhs, const std::vector<eSymbolName>& rhs, std::stack<Node*>& leftSubstring)
{
	Node* expression = leftSubstring.top(); leftSubstring.pop();
	delete leftSubstring.top(); leftSubstring.pop(); // assign
	Node* identifier = leftSubstring.top(); leftSubstring.pop();

	Node* assignmentStatement = new Assign(identifier->GetValue(), expression);
	delete identifier;
	return assignmentStatement;
}

Node* NodeFactory::createExpr(eSymbolName lhs, const std::vector<eSymbolName>& rhs, std::stack<Node*>& leftSubstring)
{
	if (rhs.size() == 1) {
		Node* successor = leftSubstring.top(); leftSubstring.pop();
		return successor;
	}

	if (rhs.size() == 3) {
		Node* rightOperand = leftSubstring.top(); leftSubstring.pop();
		Node* op = leftSubstring.top(); leftSubstring.pop();
		Node* leftOperand = leftSubstring.top(); leftSubstring.pop();

		BinaryExpression* binaryExpression = new BinaryExpression(lhs, leftOperand, op->GetValue(), rightOperand);	
		delete op;
		return binaryExpression;
	}

	return nullptr;
}

Node* NodeFactory::createTerm(eSymbolName lhs, const std::vector<eSymbolName>& rhs, std::stack<Node*>& leftSubstring)
{
	if (rhs.size() == 1) {
		Node* successor = leftSubstring.top(); leftSubstring.pop();
		return successor;
	}

	if (rhs.size() == 3) {
		Node* rightOperand = leftSubstring.top(); leftSubstring.pop();
		Node* op = leftSubstring.top(); leftSubstring.pop();
		Node* leftOperand = leftSubstring.top(); leftSubstring.pop();

		BinaryExpression* binaryExpression = new BinaryExpression(lhs, leftOperand, op->GetValue(), rightOperand);
		delete op;

		return binaryExpression;
	}

	throw std::runtime_error("Invalid term");
}


Node* NodeFactory::createFact(eSymbolName lhs, const std::vector<eSymbolName>& rhs, std::stack<Node*>& leftSubstring)
{
	// Variable or const value
	if (rhs.size() == 1) {
		Node* successor = leftSubstring.top(); leftSubstring.pop();
		return successor;
	}

	// Single operation
	if (rhs.size() == 2) {
		Node* operand = leftSubstring.top(); leftSubstring.pop();
		Node* op = leftSubstring.top(); leftSubstring.pop();
		SignOperation* signOperation = new SignOperation(op->GetValue(), operand);
		delete op;
		return signOperation;
	}

	// Parenthesesed expression
	if (rhs.size() == 3) {
		delete leftSubstring.top(); leftSubstring.pop(); // rparen
		Node* successor = leftSubstring.top(); leftSubstring.pop();
		delete leftSubstring.top(); leftSubstring.pop(); // lparen
		return successor;
	}

	return nullptr;
}
Node* NodeFactory::createBlock(eSymbolName lhs, const std::vector<eSymbolName>& rhs, std::stack<Node*>& leftSubstring)
{
	Block* block = new Block;

	for (int i = 0; i < rhs.size(); i++) {
		Node* child = leftSubstring.top(); leftSubstring.pop();
		if (child->Empty()) {
			delete child;
		}
		else if (child->GetName() == eSymbolName::BLOCK) {
			block->AddStatements(static_cast<Block*>(child)->GetStatements());
			delete child;
		}
		else{
			block->AddStatement(child);
		}
	}

	return block;

}

Node* NodeFactory::createStmt(eSymbolName lhs, const std::vector<eSymbolName>& rhs, std::stack<Node*>& leftSubstring)
{
	// Variable Declaration
	if (rhs.size() == 1) {
		Node* successor = leftSubstring.top(); leftSubstring.pop();
		return successor;
	}

	// Assign statement
	if (rhs.size() == 2) {
		delete leftSubstring.top(); leftSubstring.pop(); // semi
		Node* successor = leftSubstring.top(); leftSubstring.pop();
		return successor;
	}

	// while statemnt
	if (rhs.size() == 7) {
		delete leftSubstring.top(); leftSubstring.pop(); // rbrace
		Node* block = leftSubstring.top(); leftSubstring.pop();
		delete leftSubstring.top(); leftSubstring.pop(); // lbrace
		delete leftSubstring.top(); leftSubstring.pop(); // rparen
		Node* condition = leftSubstring.top(); leftSubstring.pop();
		delete leftSubstring.top(); leftSubstring.pop(); // lparen
		delete leftSubstring.top(); leftSubstring.pop(); // while
		return new WhileStatement(condition, block);
	}

	// if statemnt
	if (rhs.size() == 8) {
		Node* elseBlock = leftSubstring.top(); leftSubstring.pop();
		delete leftSubstring.top(); leftSubstring.pop(); // rbrace
		Node* block = leftSubstring.top(); leftSubstring.pop();
		delete leftSubstring.top(); leftSubstring.pop(); // lbrace
		delete leftSubstring.top(); leftSubstring.pop(); // rparen
		Node* condition = leftSubstring.top(); leftSubstring.pop();
		delete leftSubstring.top(); leftSubstring.pop(); // lparen
		delete leftSubstring.top(); leftSubstring.pop(); // while
		return new IfStatement(condition, block, elseBlock);
	}
	return nullptr;
}

Node* NodeFactory::createPrefixStmt(eSymbolName lhs, const std::vector<eSymbolName>& rhs, std::stack<Node*>& leftSubstring)
{
	Node* identifier = leftSubstring.top(); leftSubstring.pop();
	Node* op = leftSubstring.top(); leftSubstring.pop();
	PrefixExpression* prefixExpression = new PrefixExpression(op->GetValue(), identifier->GetValue());

	delete op;
	delete identifier;

	return prefixExpression;
}

Node* NodeFactory::createPostfixStmt(eSymbolName lhs, const std::vector<eSymbolName>& rhs, std::stack<Node*>& leftSubstring)
{
	Node* op = leftSubstring.top(); leftSubstring.pop();
	Node* identifier = leftSubstring.top(); leftSubstring.pop();
	PostfixExpression* postfixExpression = new PostfixExpression(op->GetValue(), identifier->GetValue());

	delete op;
	delete identifier;

	return postfixExpression;
}
Node* NodeFactory::createFuncCall(eSymbolName lhs, const std::vector<eSymbolName>& rhs, std::stack<Node*>& leftSubstring)
{
	delete leftSubstring.top(); leftSubstring.pop(); // rparen
	Node* argument = leftSubstring.top(); leftSubstring.pop();
	delete leftSubstring.top(); leftSubstring.pop(); // lparen
	Node* identifier = leftSubstring.top(); leftSubstring.pop();
	FunctionCall* functionCall = new FunctionCall(identifier->GetValue(), argument);
	delete identifier;
	return functionCall;
}


Node* NodeFactory::createArgument(eSymbolName lhs, const std::vector<eSymbolName>& rhs, std::stack<Node*>& leftSubstring)
{
	Node* moreArgument = leftSubstring.top(); leftSubstring.pop();
	Node* expression = leftSubstring.top(); leftSubstring.pop();
	return new Argument(lhs, expression, moreArgument);
}

Node* NodeFactory::createMoreArgument(eSymbolName lhs, const std::vector<eSymbolName>& rhs, std::stack<Node*>& leftSubstring)
{
	Node* moreArgument = leftSubstring.top(); leftSubstring.pop();
	Node* expression = leftSubstring.top(); leftSubstring.pop();
	delete leftSubstring.top(); leftSubstring.pop(); // comma
	return new Argument(lhs, expression, moreArgument);
}

Node* NodeFactory::createCond(eSymbolName lhs, const std::vector<eSymbolName>& rhs, std::stack<Node*>& leftSubstring)
{
	Node* logicExpr = leftSubstring.top(); leftSubstring.pop();
	Node* condExpr = leftSubstring.top(); leftSubstring.pop();
	return new Condition(condExpr, logicExpr);
}
Node* NodeFactory::createCondExpr(eSymbolName lhs, const std::vector<eSymbolName>& rhs, std::stack<Node*>& leftSubstring)
{
	if (rhs.size() == 1) {
		Node* successor = leftSubstring.top(); leftSubstring.pop();
		return successor;
	}
	Node* rightOperand = leftSubstring.top(); leftSubstring.pop();
	Node* op = leftSubstring.top(); leftSubstring.pop();
	Node* leftOperand = leftSubstring.top(); leftSubstring.pop();

	BinaryExpression* binaryExpression = new BinaryExpression(lhs, leftOperand, op->GetValue(), rightOperand);
	delete op;
	return binaryExpression;
}

Node* NodeFactory::createLogicExpr(eSymbolName lhs, const std::vector<eSymbolName>& rhs, std::stack<Node*>& leftSubstring)
{
	Node* cond = leftSubstring.top(); leftSubstring.pop();
	Node* op = leftSubstring.top(); leftSubstring.pop();

	LogicExpression* logicExpression = new LogicExpression(op->GetValue(), cond);
	delete op;
	return logicExpression;
}

Node* NodeFactory::createElse(eSymbolName lhs, const std::vector<eSymbolName>& rhs, std::stack<Node*>& leftSubstring)
{
	delete leftSubstring.top(); leftSubstring.pop(); // rbrace
	Node* block = leftSubstring.top(); leftSubstring.pop();
	delete leftSubstring.top(); leftSubstring.pop(); // rbrace
	delete leftSubstring.top(); leftSubstring.pop(); // else keyword

	return block;
}

Node* NodeFactory::createReturn(eSymbolName lhs, const std::vector<eSymbolName>& rhs, std::stack<Node*>& leftSubstring)
{
	delete leftSubstring.top(); leftSubstring.pop(); // semi
	Node* expression = leftSubstring.top(); leftSubstring.pop();
	delete leftSubstring.top(); leftSubstring.pop(); // return keyword
	return expression;

}


const std::unordered_map<eSymbolName, NodeFactory::SemanticAction> NodeFactory::sSemanticActions =
{
	{ eSymbolName::CODE, &NodeFactory::createCode },
	{ eSymbolName::FDECL, &NodeFactory::createFDecl },
	{ eSymbolName::PARAMETER, &NodeFactory::createParameter },
	{ eSymbolName::MORE_PARAMETER, &NodeFactory::createMoreParameter },
	{ eSymbolName::VDECL, &NodeFactory::createVDecl },
	{ eSymbolName::ASSIGN, &NodeFactory::createAssign },
	{ eSymbolName::EXPR, &NodeFactory::createExpr },
	{ eSymbolName::TERM, &NodeFactory::createTerm },
	{ eSymbolName::FACT, &NodeFactory::createFact },
	{ eSymbolName::BLOCK, &NodeFactory::createBlock },
	{ eSymbolName::STMT, &NodeFactory::createStmt },
	{ eSymbolName::PREFIX_STMT, &NodeFactory::createPrefixStmt },
	{ eSymbolName::POSTFIX_STMT, &NodeFactory::createPostfixStmt },
	{ eSymbolName::FUNC_CALL, &NodeFactory::createFuncCall },
	{ eSymbolName::ARGUMENT, &NodeFactory::createArgument },
	{ eSymbolName::MORE_ARGUMENT, &NodeFactory::createMoreArgument },
	{ eSymbolName::COND, &NodeFactory::createCond },
	{ eSymbolName::COND_EXPR, &NodeFactory::createCondExpr },
	{ eSymbolName::LOGIC_EXPR, &NodeFactory::createLogicExpr },
	{ eSymbolName::ELSE, &NodeFactory::createElse },
	{ eSymbolName::RETURN, &NodeFactory::createReturn },
};