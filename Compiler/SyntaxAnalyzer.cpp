#include "SyntaxAnalyzer.h"

SyntaxAnalyzer::SyntaxAnalyzer()
	: mToken(nullptr) 
{}

Node* SyntaxAnalyzer::Analyze(LexicalAnalyzer& lexicalAnalyzer)
{
	mStates.push(0);
    while (true) 
	{
		mToken = lexicalAnalyzer.GetToken();
        if (mToken->GetName() == eSymbolName::WhiteSpace) 
		{
            continue;
        }

        if (implementAction()) 
		{
            std::cout << "Syntaxtic Analysis has succeeded\n" << std::endl;
            return mLeftSubstring.top();
        }
    }
}


bool SyntaxAnalyzer::implementAction()
{
    // look up a behavior by state and token
	const unsigned int currentState = mStates.top();
    const auto& itBehavior = SLR_TABLE.at(currentState).find(mToken->GetName());

	// if there is no behavior for the current state and token
	if (itBehavior == SLR_TABLE.at(currentState).end()) 
	{
		std::cout << "Unexpected Token: " << STRING_SYMOL_NAMES.at(mToken->GetName()) << std::endl;
		exit(1);
	}


    const std::string& behavior = itBehavior->second;
    const std::string& targetNumber = behavior.substr(1, behavior.length() - 1);
    switch (behavior[0])
    {
    case 's':
        shift(std::stoi(targetNumber));
        return false;
    case 'r':
        return reduce(std::stoi(targetNumber));
    case 'a':
        return true;

    // action is a number -> goto
    default:
        goTo(std::stoi(behavior));
        return false;
    }
}

void SyntaxAnalyzer::goTo(const unsigned int targetState)
{
    mStates.push(targetState);
}

void SyntaxAnalyzer::shift(const unsigned int targetState)
{
    mLeftSubstring.push(mToken);
    goTo(targetState);
}

bool SyntaxAnalyzer::reduce(const unsigned int targetRuleNumber)
{
    const eSymbolName lhs = LHS_LIST.at(targetRuleNumber);
    const std::vector<eSymbolName>& rhs = RHS_LIST.at(targetRuleNumber);


    for (int i = 0; i < rhs.size(); i++) 
	{
        mStates.pop();
    }

    Node* node = NodeFactory::CreateNode(lhs, rhs, mLeftSubstring);
    mLeftSubstring.push(node);
    goTo(std::stoi(SLR_TABLE[mStates.top()].at(lhs)));
    return implementAction();
}




const std::vector<eSymbolName> SyntaxAnalyzer::LHS_LIST = 
{
	eSymbolName::S,
	eSymbolName::CODE,
	eSymbolName::CODE,
	eSymbolName::FDECL,
	eSymbolName::PARAMETER,
	eSymbolName::PARAMETER,
	eSymbolName::MORE_PARAMETER,
	eSymbolName::MORE_PARAMETER,
	eSymbolName::VDECL,
	eSymbolName::VDECL,
	eSymbolName::ASSIGN,
	eSymbolName::EXPR,
	eSymbolName::EXPR,
	eSymbolName::EXPR,
	eSymbolName::EXPR,
	eSymbolName::TERM,
	eSymbolName::TERM,
	eSymbolName::FACT,
	eSymbolName::FACT,
	eSymbolName::FACT,
	eSymbolName::FACT,
	eSymbolName::FACT,
	eSymbolName::FACT,
	eSymbolName::FACT,
	eSymbolName::FACT,
	eSymbolName::FACT,
	eSymbolName::BLOCK,
	eSymbolName::BLOCK,
	eSymbolName::STMT,
	eSymbolName::STMT,
	eSymbolName::STMT,
	eSymbolName::STMT,
	eSymbolName::STMT,
	eSymbolName::STMT,
	eSymbolName::STMT,
	eSymbolName::PREFIX_STMT,
	eSymbolName::POSTFIX_STMT,
	eSymbolName::FUNC_CALL,
	eSymbolName::ARGUMENT,
	eSymbolName::ARGUMENT,
	eSymbolName::MORE_ARGUMENT,
	eSymbolName::MORE_ARGUMENT,
	eSymbolName::COND,
	eSymbolName::COND_EXPR,
	eSymbolName::COND_EXPR,
	eSymbolName::LOGIC_EXPR,
	eSymbolName::LOGIC_EXPR,
	eSymbolName::ELSE,
	eSymbolName::ELSE,
	eSymbolName::RETURN,
};
const std::vector<std::vector<eSymbolName>> SyntaxAnalyzer::RHS_LIST = 
{
	{eSymbolName::CODE},
	{eSymbolName::FDECL , eSymbolName::CODE},
	{},
	{eSymbolName::Type , eSymbolName::Identifier , eSymbolName::LParen , eSymbolName::PARAMETER , eSymbolName::RParen , eSymbolName::LBrace , eSymbolName::BLOCK , eSymbolName::RETURN , eSymbolName::RBrace},
	{eSymbolName::Type , eSymbolName::Identifier , eSymbolName::MORE_PARAMETER},
	{},
	{eSymbolName::Comma , eSymbolName::Type , eSymbolName::Identifier , eSymbolName::MORE_PARAMETER},
	{},
	{eSymbolName::Type , eSymbolName::Identifier , eSymbolName::Semi},
	{eSymbolName::Type , eSymbolName::ASSIGN , eSymbolName::Semi},
	{eSymbolName::Identifier , eSymbolName::Assign , eSymbolName::EXPR},
	{eSymbolName::FUNC_CALL},
	{eSymbolName::COND_EXPR},
	{eSymbolName::TERM , eSymbolName::AddSub , eSymbolName::EXPR},
	{eSymbolName::TERM},
	{eSymbolName::FACT , eSymbolName::MulDiv , eSymbolName::TERM},
	{eSymbolName::FACT},
	{eSymbolName::Integer},
	{eSymbolName::AddSub , eSymbolName::Integer},
	{eSymbolName::Character},
	{eSymbolName::AddSub , eSymbolName::Character},
	{eSymbolName::Identifier},
	{eSymbolName::AddSub , eSymbolName::Identifier},
	{eSymbolName::PREFIX_STMT},
	{eSymbolName::POSTFIX_STMT},
	{eSymbolName::LParen , eSymbolName::EXPR , eSymbolName::RParen},
	{eSymbolName::STMT , eSymbolName::BLOCK},
	{},
	{eSymbolName::VDECL},
	{eSymbolName::ASSIGN , eSymbolName::Semi},
	{eSymbolName::FUNC_CALL , eSymbolName::Semi},
	{eSymbolName::If , eSymbolName::LParen , eSymbolName::COND , eSymbolName::RParen , eSymbolName::LBrace , eSymbolName::BLOCK , eSymbolName::RBrace , eSymbolName::ELSE},
	{eSymbolName::While , eSymbolName::LParen , eSymbolName::COND , eSymbolName::RParen , eSymbolName::LBrace , eSymbolName::BLOCK , eSymbolName::RBrace},
	{eSymbolName::PREFIX_STMT , eSymbolName::Semi},
	{eSymbolName::POSTFIX_STMT , eSymbolName::Semi},
	{eSymbolName::UnaryOp , eSymbolName::Identifier},
	{eSymbolName::Identifier , eSymbolName::UnaryOp},
	{eSymbolName::Identifier , eSymbolName::LParen , eSymbolName::ARGUMENT , eSymbolName::RParen},
	{eSymbolName::EXPR , eSymbolName::MORE_ARGUMENT},
	{},
	{eSymbolName::Comma , eSymbolName::EXPR , eSymbolName::MORE_ARGUMENT},
	{},
	{eSymbolName::COND_EXPR , eSymbolName::LOGIC_EXPR},
	{eSymbolName::Boolean},
	{eSymbolName::FACT , eSymbolName::CompOp , eSymbolName::FACT},
	{},
	{eSymbolName::LogicOp , eSymbolName::COND},
	{eSymbolName::Else , eSymbolName::LBrace , eSymbolName::BLOCK , eSymbolName::RBrace},
	{},
	{eSymbolName::Return , eSymbolName::EXPR , eSymbolName::Semi},
};
const std::vector<std::unordered_map<eSymbolName, std::string>> SyntaxAnalyzer::SLR_TABLE = 
{
	{{eSymbolName::Type, "s3"}, {eSymbolName::$, "r2"}, {eSymbolName::CODE, "1"}, {eSymbolName::FDECL, "2"}},
	{{eSymbolName::$, "acc"}},
	{{eSymbolName::Type, "s3"}, {eSymbolName::$, "r2"}, {eSymbolName::CODE, "4"}, {eSymbolName::FDECL, "2"}},
	{{eSymbolName::Identifier, "s5"}},
	{{eSymbolName::$, "r1"}},
	{{eSymbolName::LParen, "s6"}},
	{{eSymbolName::Type, "s8"}, {eSymbolName::RParen, "r5"}, {eSymbolName::PARAMETER, "7"}},
	{{eSymbolName::RParen, "s9"}},
	{{eSymbolName::Identifier, "s10"}},
	{{eSymbolName::LBrace, "s11"}},
	{{eSymbolName::RParen, "r7"}, {eSymbolName::Comma, "s13"}, {eSymbolName::MORE_PARAMETER, "12"}},
	{{eSymbolName::Type, "s23"}, {eSymbolName::Identifier, "s24"}, {eSymbolName::RBrace, "r27"}, {eSymbolName::If, "s19"}, {eSymbolName::While, "s20"}, {eSymbolName::UnaryOp, "s25"}, {eSymbolName::Return, "r27"}, {eSymbolName::VDECL, "16"}, {eSymbolName::ASSIGN, "17"}, {eSymbolName::BLOCK, "14"}, {eSymbolName::STMT, "15"}, {eSymbolName::PREFIX_STMT, "21"}, {eSymbolName::POSTFIX_STMT, "22"}, {eSymbolName::FUNC_CALL, "18"}},
	{{eSymbolName::RParen, "r4"}},
	{{eSymbolName::Type, "s26"}},
	{{eSymbolName::Return, "s28"}, {eSymbolName::RETURN, "27"}},
	{{eSymbolName::Type, "s23"}, {eSymbolName::Identifier, "s24"}, {eSymbolName::RBrace, "r27"}, {eSymbolName::If, "s19"}, {eSymbolName::While, "s20"}, {eSymbolName::UnaryOp, "s25"}, {eSymbolName::Return, "r27"}, {eSymbolName::VDECL, "16"}, {eSymbolName::ASSIGN, "17"}, {eSymbolName::BLOCK, "29"}, {eSymbolName::STMT, "15"}, {eSymbolName::PREFIX_STMT, "21"}, {eSymbolName::POSTFIX_STMT, "22"}, {eSymbolName::FUNC_CALL, "18"}},
	{{eSymbolName::Type, "r28"}, {eSymbolName::Identifier, "r28"}, {eSymbolName::RBrace, "r28"}, {eSymbolName::If, "r28"}, {eSymbolName::While, "r28"}, {eSymbolName::UnaryOp, "r28"}, {eSymbolName::Return, "r28"}},
	{{eSymbolName::Semi, "s30"}},
	{{eSymbolName::Semi, "s31"}},
	{{eSymbolName::LParen, "s32"}},
	{{eSymbolName::LParen, "s33"}},
	{{eSymbolName::Semi, "s34"}},
	{{eSymbolName::Semi, "s35"}},
	{{eSymbolName::Identifier, "s36"}, {eSymbolName::ASSIGN, "37"}},
	{{eSymbolName::LParen, "s39"}, {eSymbolName::Assign, "s38"}, {eSymbolName::UnaryOp, "s40"}},
	{{eSymbolName::Identifier, "s41"}},
	{{eSymbolName::Identifier, "s42"}},
	{{eSymbolName::RBrace, "s43"}},
	{{eSymbolName::Identifier, "s48"}, {eSymbolName::LParen, "s56"}, {eSymbolName::AddSub, "s52"}, {eSymbolName::Integer, "s51"}, {eSymbolName::Character, "s53"}, {eSymbolName::UnaryOp, "s25"}, {eSymbolName::Boolean, "s49"}, {eSymbolName::EXPR, "44"}, {eSymbolName::TERM, "47"}, {eSymbolName::FACT, "50"}, {eSymbolName::PREFIX_STMT, "54"}, {eSymbolName::POSTFIX_STMT, "55"}, {eSymbolName::FUNC_CALL, "45"}, {eSymbolName::COND_EXPR, "46"}},
	{{eSymbolName::RBrace, "r26"}, {eSymbolName::Return, "r26"}},
	{{eSymbolName::Type, "r29"}, {eSymbolName::Identifier, "r29"}, {eSymbolName::RBrace, "r29"}, {eSymbolName::If, "r29"}, {eSymbolName::While, "r29"}, {eSymbolName::UnaryOp, "r29"}, {eSymbolName::Return, "r29"}},
	{{eSymbolName::Type, "r30"}, {eSymbolName::Identifier, "r30"}, {eSymbolName::RBrace, "r30"}, {eSymbolName::If, "r30"}, {eSymbolName::While, "r30"}, {eSymbolName::UnaryOp, "r30"}, {eSymbolName::Return, "r30"}},
	{{eSymbolName::Identifier, "s60"}, {eSymbolName::LParen, "s56"}, {eSymbolName::AddSub, "s52"}, {eSymbolName::Integer, "s51"}, {eSymbolName::Character, "s53"}, {eSymbolName::UnaryOp, "s25"}, {eSymbolName::Boolean, "s49"}, {eSymbolName::FACT, "59"}, {eSymbolName::PREFIX_STMT, "54"}, {eSymbolName::POSTFIX_STMT, "55"}, {eSymbolName::COND, "57"}, {eSymbolName::COND_EXPR, "58"}},
	{{eSymbolName::Identifier, "s60"}, {eSymbolName::LParen, "s56"}, {eSymbolName::AddSub, "s52"}, {eSymbolName::Integer, "s51"}, {eSymbolName::Character, "s53"}, {eSymbolName::UnaryOp, "s25"}, {eSymbolName::Boolean, "s49"}, {eSymbolName::FACT, "59"}, {eSymbolName::PREFIX_STMT, "54"}, {eSymbolName::POSTFIX_STMT, "55"}, {eSymbolName::COND, "61"}, {eSymbolName::COND_EXPR, "58"}},
	{{eSymbolName::Type, "r33"}, {eSymbolName::Identifier, "r33"}, {eSymbolName::RBrace, "r33"}, {eSymbolName::If, "r33"}, {eSymbolName::While, "r33"}, {eSymbolName::UnaryOp, "r33"}, {eSymbolName::Return, "r33"}},
	{{eSymbolName::Type, "r34"}, {eSymbolName::Identifier, "r34"}, {eSymbolName::RBrace, "r34"}, {eSymbolName::If, "r34"}, {eSymbolName::While, "r34"}, {eSymbolName::UnaryOp, "r34"}, {eSymbolName::Return, "r34"}},
	{{eSymbolName::Semi, "s62"}, {eSymbolName::Assign, "s38"}},
	{{eSymbolName::Semi, "s63"}},
	{{eSymbolName::Identifier, "s48"}, {eSymbolName::LParen, "s56"}, {eSymbolName::AddSub, "s52"}, {eSymbolName::Integer, "s51"}, {eSymbolName::Character, "s53"}, {eSymbolName::UnaryOp, "s25"}, {eSymbolName::Boolean, "s49"}, {eSymbolName::EXPR, "64"}, {eSymbolName::TERM, "47"}, {eSymbolName::FACT, "50"}, {eSymbolName::PREFIX_STMT, "54"}, {eSymbolName::POSTFIX_STMT, "55"}, {eSymbolName::FUNC_CALL, "45"}, {eSymbolName::COND_EXPR, "46"}},
	{{eSymbolName::Identifier, "s48"}, {eSymbolName::LParen, "s56"}, {eSymbolName::RParen, "r39"}, {eSymbolName::AddSub, "s52"}, {eSymbolName::Integer, "s51"}, {eSymbolName::Character, "s53"}, {eSymbolName::UnaryOp, "s25"}, {eSymbolName::Boolean, "s49"}, {eSymbolName::EXPR, "66"}, {eSymbolName::TERM, "47"}, {eSymbolName::FACT, "50"}, {eSymbolName::PREFIX_STMT, "54"}, {eSymbolName::POSTFIX_STMT, "55"}, {eSymbolName::FUNC_CALL, "45"}, {eSymbolName::ARGUMENT, "65"}, {eSymbolName::COND_EXPR, "46"}},
	{{eSymbolName::RParen, "r36"}, {eSymbolName::Comma, "r36"}, {eSymbolName::Semi, "r36"}, {eSymbolName::AddSub, "r36"}, {eSymbolName::MulDiv, "r36"}, {eSymbolName::CompOp, "r36"}, {eSymbolName::LogicOp, "r36"}},
	{{eSymbolName::RParen, "r35"}, {eSymbolName::Comma, "r35"}, {eSymbolName::Semi, "r35"}, {eSymbolName::AddSub, "r35"}, {eSymbolName::MulDiv, "r35"}, {eSymbolName::CompOp, "r35"}, {eSymbolName::LogicOp, "r35"}},
	{{eSymbolName::RParen, "r7"}, {eSymbolName::Comma, "s13"}, {eSymbolName::MORE_PARAMETER, "67"}},
	{{eSymbolName::Type, "r3"}, {eSymbolName::$, "r3"}},
	{{eSymbolName::Semi, "s68"}},
	{{eSymbolName::RParen, "r11"}, {eSymbolName::Comma, "r11"}, {eSymbolName::Semi, "r11"}},
	{{eSymbolName::RParen, "r12"}, {eSymbolName::Comma, "r12"}, {eSymbolName::Semi, "r12"}},
	{{eSymbolName::RParen, "r14"}, {eSymbolName::Comma, "r14"}, {eSymbolName::Semi, "r14"}, {eSymbolName::AddSub, "s69"}},
	{{eSymbolName::LParen, "s39"}, {eSymbolName::RParen, "r21"}, {eSymbolName::Comma, "r21"}, {eSymbolName::Semi, "r21"}, {eSymbolName::AddSub, "r21"}, {eSymbolName::MulDiv, "r21"}, {eSymbolName::UnaryOp, "s40"}, {eSymbolName::CompOp, "r21"}, {eSymbolName::LogicOp, "r21"}},
	{{eSymbolName::RParen, "r43"}, {eSymbolName::Comma, "r43"}, {eSymbolName::Semi, "r43"}, {eSymbolName::LogicOp, "r43"}},
	{{eSymbolName::RParen, "r16"}, {eSymbolName::Comma, "r16"}, {eSymbolName::Semi, "r16"}, {eSymbolName::AddSub, "r16"}, {eSymbolName::MulDiv, "s71"}, {eSymbolName::CompOp, "s70"}},
	{{eSymbolName::RParen, "r17"}, {eSymbolName::Comma, "r17"}, {eSymbolName::Semi, "r17"}, {eSymbolName::AddSub, "r17"}, {eSymbolName::MulDiv, "r17"}, {eSymbolName::CompOp, "r17"}, {eSymbolName::LogicOp, "r17"}},
	{{eSymbolName::Identifier, "s74"}, {eSymbolName::Integer, "s72"}, {eSymbolName::Character, "s73"}},
	{{eSymbolName::RParen, "r19"}, {eSymbolName::Comma, "r19"}, {eSymbolName::Semi, "r19"}, {eSymbolName::AddSub, "r19"}, {eSymbolName::MulDiv, "r19"}, {eSymbolName::CompOp, "r19"}, {eSymbolName::LogicOp, "r19"}},
	{{eSymbolName::RParen, "r23"}, {eSymbolName::Comma, "r23"}, {eSymbolName::Semi, "r23"}, {eSymbolName::AddSub, "r23"}, {eSymbolName::MulDiv, "r23"}, {eSymbolName::CompOp, "r23"}, {eSymbolName::LogicOp, "r23"}},
	{{eSymbolName::RParen, "r24"}, {eSymbolName::Comma, "r24"}, {eSymbolName::Semi, "r24"}, {eSymbolName::AddSub, "r24"}, {eSymbolName::MulDiv, "r24"}, {eSymbolName::CompOp, "r24"}, {eSymbolName::LogicOp, "r24"}},
	{{eSymbolName::Identifier, "s48"}, {eSymbolName::LParen, "s56"}, {eSymbolName::AddSub, "s52"}, {eSymbolName::Integer, "s51"}, {eSymbolName::Character, "s53"}, {eSymbolName::UnaryOp, "s25"}, {eSymbolName::Boolean, "s49"}, {eSymbolName::EXPR, "75"}, {eSymbolName::TERM, "47"}, {eSymbolName::FACT, "50"}, {eSymbolName::PREFIX_STMT, "54"}, {eSymbolName::POSTFIX_STMT, "55"}, {eSymbolName::FUNC_CALL, "45"}, {eSymbolName::COND_EXPR, "46"}},
	{{eSymbolName::RParen, "s76"}},
	{{eSymbolName::RParen, "r45"}, {eSymbolName::LogicOp, "s78"}, {eSymbolName::LOGIC_EXPR, "77"}},
	{{eSymbolName::CompOp, "s70"}},
	{{eSymbolName::RParen, "r21"}, {eSymbolName::Comma, "r21"}, {eSymbolName::Semi, "r21"}, {eSymbolName::AddSub, "r21"}, {eSymbolName::MulDiv, "r21"}, {eSymbolName::UnaryOp, "s40"}, {eSymbolName::CompOp, "r21"}, {eSymbolName::LogicOp, "r21"}},
	{{eSymbolName::RParen, "s79"}},
	{{eSymbolName::Type, "r8"}, {eSymbolName::Identifier, "r8"}, {eSymbolName::RBrace, "r8"}, {eSymbolName::If, "r8"}, {eSymbolName::While, "r8"}, {eSymbolName::UnaryOp, "r8"}, {eSymbolName::Return, "r8"}},
	{{eSymbolName::Type, "r9"}, {eSymbolName::Identifier, "r9"}, {eSymbolName::RBrace, "r9"}, {eSymbolName::If, "r9"}, {eSymbolName::While, "r9"}, {eSymbolName::UnaryOp, "r9"}, {eSymbolName::Return, "r9"}},
	{{eSymbolName::Semi, "r10"}},
	{{eSymbolName::RParen, "s80"}},
	{{eSymbolName::RParen, "r41"}, {eSymbolName::Comma, "s82"}, {eSymbolName::MORE_ARGUMENT, "81"}},
	{{eSymbolName::RParen, "r6"}},
	{{eSymbolName::RBrace, "r49"}},
	{{eSymbolName::Identifier, "s48"}, {eSymbolName::LParen, "s56"}, {eSymbolName::AddSub, "s52"}, {eSymbolName::Integer, "s51"}, {eSymbolName::Character, "s53"}, {eSymbolName::UnaryOp, "s25"}, {eSymbolName::Boolean, "s49"}, {eSymbolName::EXPR, "83"}, {eSymbolName::TERM, "47"}, {eSymbolName::FACT, "50"}, {eSymbolName::PREFIX_STMT, "54"}, {eSymbolName::POSTFIX_STMT, "55"}, {eSymbolName::FUNC_CALL, "45"}, {eSymbolName::COND_EXPR, "46"}},
	{{eSymbolName::Identifier, "s60"}, {eSymbolName::LParen, "s56"}, {eSymbolName::AddSub, "s52"}, {eSymbolName::Integer, "s51"}, {eSymbolName::Character, "s53"}, {eSymbolName::UnaryOp, "s25"}, {eSymbolName::FACT, "84"}, {eSymbolName::PREFIX_STMT, "54"}, {eSymbolName::POSTFIX_STMT, "55"}},
	{{eSymbolName::Identifier, "s60"}, {eSymbolName::LParen, "s56"}, {eSymbolName::AddSub, "s52"}, {eSymbolName::Integer, "s51"}, {eSymbolName::Character, "s53"}, {eSymbolName::UnaryOp, "s25"}, {eSymbolName::TERM, "85"}, {eSymbolName::FACT, "86"}, {eSymbolName::PREFIX_STMT, "54"}, {eSymbolName::POSTFIX_STMT, "55"}},
	{{eSymbolName::RParen, "r18"}, {eSymbolName::Comma, "r18"}, {eSymbolName::Semi, "r18"}, {eSymbolName::AddSub, "r18"}, {eSymbolName::MulDiv, "r18"}, {eSymbolName::CompOp, "r18"}, {eSymbolName::LogicOp, "r18"}},
	{{eSymbolName::RParen, "r20"}, {eSymbolName::Comma, "r20"}, {eSymbolName::Semi, "r20"}, {eSymbolName::AddSub, "r20"}, {eSymbolName::MulDiv, "r20"}, {eSymbolName::CompOp, "r20"}, {eSymbolName::LogicOp, "r20"}},
	{{eSymbolName::RParen, "r22"}, {eSymbolName::Comma, "r22"}, {eSymbolName::Semi, "r22"}, {eSymbolName::AddSub, "r22"}, {eSymbolName::MulDiv, "r22"}, {eSymbolName::CompOp, "r22"}, {eSymbolName::LogicOp, "r22"}},
	{{eSymbolName::RParen, "s87"}},
	{{eSymbolName::LBrace, "s88"}},
	{{eSymbolName::RParen, "r42"}},
	{{eSymbolName::Identifier, "s60"}, {eSymbolName::LParen, "s56"}, {eSymbolName::AddSub, "s52"}, {eSymbolName::Integer, "s51"}, {eSymbolName::Character, "s53"}, {eSymbolName::UnaryOp, "s25"}, {eSymbolName::Boolean, "s49"}, {eSymbolName::FACT, "59"}, {eSymbolName::PREFIX_STMT, "54"}, {eSymbolName::POSTFIX_STMT, "55"}, {eSymbolName::COND, "89"}, {eSymbolName::COND_EXPR, "58"}},
	{{eSymbolName::LBrace, "s90"}},
	{{eSymbolName::RParen, "r37"}, {eSymbolName::Comma, "r37"}, {eSymbolName::Semi, "r37"}},
	{{eSymbolName::RParen, "r38"}},
	{{eSymbolName::Identifier, "s48"}, {eSymbolName::LParen, "s56"}, {eSymbolName::AddSub, "s52"}, {eSymbolName::Integer, "s51"}, {eSymbolName::Character, "s53"}, {eSymbolName::UnaryOp, "s25"}, {eSymbolName::Boolean, "s49"}, {eSymbolName::EXPR, "91"}, {eSymbolName::TERM, "47"}, {eSymbolName::FACT, "50"}, {eSymbolName::PREFIX_STMT, "54"}, {eSymbolName::POSTFIX_STMT, "55"}, {eSymbolName::FUNC_CALL, "45"}, {eSymbolName::COND_EXPR, "46"}},
	{{eSymbolName::RParen, "r13"}, {eSymbolName::Comma, "r13"}, {eSymbolName::Semi, "r13"}},
	{{eSymbolName::RParen, "r44"}, {eSymbolName::Comma, "r44"}, {eSymbolName::Semi, "r44"}, {eSymbolName::LogicOp, "r44"}},
	{{eSymbolName::RParen, "r15"}, {eSymbolName::Comma, "r15"}, {eSymbolName::Semi, "r15"}, {eSymbolName::AddSub, "r15"}},
	{{eSymbolName::RParen, "r16"}, {eSymbolName::Comma, "r16"}, {eSymbolName::Semi, "r16"}, {eSymbolName::AddSub, "r16"}, {eSymbolName::MulDiv, "s71"}},
	{{eSymbolName::RParen, "r25"}, {eSymbolName::Comma, "r25"}, {eSymbolName::Semi, "r25"}, {eSymbolName::AddSub, "r25"}, {eSymbolName::MulDiv, "r25"}, {eSymbolName::CompOp, "r25"}, {eSymbolName::LogicOp, "r25"}},
	{{eSymbolName::Type, "s23"}, {eSymbolName::Identifier, "s24"}, {eSymbolName::RBrace, "r27"}, {eSymbolName::If, "s19"}, {eSymbolName::While, "s20"}, {eSymbolName::UnaryOp, "s25"}, {eSymbolName::Return, "r27"}, {eSymbolName::VDECL, "16"}, {eSymbolName::ASSIGN, "17"}, {eSymbolName::BLOCK, "92"}, {eSymbolName::STMT, "15"}, {eSymbolName::PREFIX_STMT, "21"}, {eSymbolName::POSTFIX_STMT, "22"}, {eSymbolName::FUNC_CALL, "18"}},
	{{eSymbolName::RParen, "r46"}},
	{{eSymbolName::Type, "s23"}, {eSymbolName::Identifier, "s24"}, {eSymbolName::RBrace, "r27"}, {eSymbolName::If, "s19"}, {eSymbolName::While, "s20"}, {eSymbolName::UnaryOp, "s25"}, {eSymbolName::Return, "r27"}, {eSymbolName::VDECL, "16"}, {eSymbolName::ASSIGN, "17"}, {eSymbolName::BLOCK, "93"}, {eSymbolName::STMT, "15"}, {eSymbolName::PREFIX_STMT, "21"}, {eSymbolName::POSTFIX_STMT, "22"}, {eSymbolName::FUNC_CALL, "18"}},
	{{eSymbolName::RParen, "r41"}, {eSymbolName::Comma, "s82"}, {eSymbolName::MORE_ARGUMENT, "94"}},
	{{eSymbolName::RBrace, "s95"}},
	{{eSymbolName::RBrace, "s96"}},
	{{eSymbolName::RParen, "r40"}},
	{{eSymbolName::Type, "r48"}, {eSymbolName::Identifier, "r48"}, {eSymbolName::RBrace, "r48"}, {eSymbolName::If, "r48"}, {eSymbolName::While, "r48"}, {eSymbolName::UnaryOp, "r48"}, {eSymbolName::Else, "s98"}, {eSymbolName::Return, "r48"}, {eSymbolName::ELSE, "97"}},
	{{eSymbolName::Type, "r32"}, {eSymbolName::Identifier, "r32"}, {eSymbolName::RBrace, "r32"}, {eSymbolName::If, "r32"}, {eSymbolName::While, "r32"}, {eSymbolName::UnaryOp, "r32"}, {eSymbolName::Return, "r32"}},
	{{eSymbolName::Type, "r31"}, {eSymbolName::Identifier, "r31"}, {eSymbolName::RBrace, "r31"}, {eSymbolName::If, "r31"}, {eSymbolName::While, "r31"}, {eSymbolName::UnaryOp, "r31"}, {eSymbolName::Return, "r31"}},
	{{eSymbolName::LBrace, "s99"}},
	{{eSymbolName::Type, "s23"}, {eSymbolName::Identifier, "s24"}, {eSymbolName::RBrace, "r27"}, {eSymbolName::If, "s19"}, {eSymbolName::While, "s20"}, {eSymbolName::UnaryOp, "s25"}, {eSymbolName::Return, "r27"}, {eSymbolName::VDECL, "16"}, {eSymbolName::ASSIGN, "17"}, {eSymbolName::BLOCK, "100"}, {eSymbolName::STMT, "15"}, {eSymbolName::PREFIX_STMT, "21"}, {eSymbolName::POSTFIX_STMT, "22"}, {eSymbolName::FUNC_CALL, "18"}},
	{{eSymbolName::RBrace, "s101"}},
	{{eSymbolName::Type, "r47"}, {eSymbolName::Identifier, "r47"}, {eSymbolName::RBrace, "r47"}, {eSymbolName::If, "r47"}, {eSymbolName::While, "r47"}, {eSymbolName::UnaryOp, "r47"}, {eSymbolName::Return, "r47"}},
};
