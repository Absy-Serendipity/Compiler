#pragma once
#include "LexicalAnalyzer.h"
#include "NodeFactory.h"


class SyntaxAnalyzer
{
public:
	SyntaxAnalyzer();
	~SyntaxAnalyzer() = default;

	Node* Analyze(LexicalAnalyzer&);

private:
	bool implementAction();
	void goTo(const unsigned int);
	void shift(const unsigned int);
	bool reduce(const unsigned int);

private:
	std::stack<unsigned int> mStates;
	std::stack<Node*> mLeftSubstring;
	Node* mToken;

	static const std::vector<eSymbolName> LHS_LIST;
	static const std::vector<std::vector<eSymbolName>> RHS_LIST;
	static const std::vector<std::unordered_map<eSymbolName, std::string>> SLR_TABLE;
};

