#pragma once
#include "Terminal.h"
#include <memory>

class LexicalAnalyzer
{
public:
	LexicalAnalyzer(const std::string&);
	~LexicalAnalyzer() = default;
	 
	Terminal* GetToken();

private:
	Terminal mEndTermianl;
	const std::string mInput;
	unsigned int mCursor;

	// static
    static const std::unordered_map<char, eSymbolName> sSyntaxticOperators;
	static const std::unordered_map<std::string, eSymbolName> sCompositeOperators;
	static const std::unordered_map<char, eSymbolName> sSingleOperators;
	static const std::unordered_map<std::string, eSymbolName> sKeywords;
};