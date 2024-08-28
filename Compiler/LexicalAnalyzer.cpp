#include "LexicalAnalyzer.h"

Terminal* LexicalAnalyzer::GetToken()
{
	// End of Input
	if (mInput.length() <= mCursor) {
		return &(mEndTermianl);
	}
	
	// Composite Operator such as '==', '!=', '<=', '>=', '++', '--'
	if (mInput.length() > mCursor + 1) {
		const std::string op = mInput.substr(mCursor, 2);
		const auto itDualOperator = sCompositeOperators.find(op);

		if (itDualOperator != sCompositeOperators.end()) {
			mCursor += 2;
			return new Terminal(itDualOperator->second, op);
		}
	}

	// Syntactic Symbol
	const auto itSyntacticSymbol = sSyntaxticOperators.find(mInput[mCursor]);
	if (itSyntacticSymbol != sSyntaxticOperators.end()) {
		++mCursor;
		return new Terminal(itSyntacticSymbol->second);
	}

	// Single Operator such as '+', '-', '*', '/', '<', '>', '&', '|'
	const auto itSingleOperator = sSingleOperators.find(mInput[mCursor]);
	if (itSingleOperator != sSingleOperators.end()) {
		mCursor++;
		return new Terminal(itSingleOperator->second, mInput.substr(mCursor - 1, 1));
	}

	// Character
	if (mInput[mCursor] == '\'') {
		std::string value(1, mInput[++mCursor]);
		if (++mCursor >= mInput.length() || mInput[mCursor] != '\'') {
			throw std::runtime_error("Single quote is not closed");
		}
		mCursor++;
		return new Terminal(eSymbolName::Character, value);
	}


	// Integer
	if (std::isdigit(mInput[mCursor])) {
		std::string value(1, mInput[mCursor]);
		while (std::isdigit(mInput[++mCursor])) {
			value += mInput[mCursor];
		}
		return new Terminal(eSymbolName::Integer, value);
	}


	// Identifier or Keyword
	if (std::isalpha(mInput[mCursor]) || mInput[mCursor] == '_') {
		std::string value(1, mInput[mCursor]);
		while (std::isalnum(mInput[++mCursor]) || mInput[mCursor] == '_') {
			value += mInput[mCursor];
		}
		// Keyword
		const auto itKeyword = sKeywords.find(value);
		if (itKeyword != sKeywords.end()) {
			return new Terminal(itKeyword->second, value);
		}
		// Identifier
		return new Terminal(eSymbolName::Identifier, value);
	}

	// Invalid Token
	throw std::runtime_error("Invalid Token");
}

const std::unordered_map<char, eSymbolName> LexicalAnalyzer::sSyntaxticOperators = {
	{'\n', eSymbolName::WhiteSpace}, {' ', eSymbolName::WhiteSpace}, {'\t', eSymbolName::WhiteSpace},
	{',', eSymbolName::Comma}, {';', eSymbolName::Semi}, {'(', eSymbolName::LParen}, {')', eSymbolName::RParen},
	{'{', eSymbolName::LBrace}, {'}', eSymbolName::RBrace}
};


const std::unordered_map<std::string, eSymbolName> LexicalAnalyzer::sCompositeOperators = {
	{"++", eSymbolName::UnaryOp},{"--", eSymbolName::UnaryOp}, {"==", eSymbolName::CompOp},
	{"!=", eSymbolName::CompOp}, {"<=", eSymbolName::CompOp}, {">=", eSymbolName::CompOp}
};

const std::unordered_map<char, eSymbolName> LexicalAnalyzer::sSingleOperators = {
	{'+', eSymbolName::AddSub}, {'-', eSymbolName::AddSub},{'=', eSymbolName::Assign},{'*', eSymbolName::MulDiv},{'/', eSymbolName::MulDiv},
	{'<', eSymbolName::CompOp},{'>', eSymbolName::CompOp}, {'&', eSymbolName::LogicOp}, {'|', eSymbolName::LogicOp}
};

const std::unordered_map<std::string, eSymbolName> LexicalAnalyzer::sKeywords = {
	{"int", eSymbolName::Type}, {"char", eSymbolName::Type}, {"bool", eSymbolName::Type},
	{"true", eSymbolName::Boolean}, {"false", eSymbolName::Boolean},
	{"if", eSymbolName::If}, {"else", eSymbolName::Else}, {"while", eSymbolName::While}, {"return", eSymbolName::Return},
};