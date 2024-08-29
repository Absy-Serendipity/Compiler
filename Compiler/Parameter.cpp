#include "Parameter.h"


Parameter::Parameter(const eSymbolName symbol, const std::string& type, const std::string& identifier, Node* moreParameter)
    : Node(symbol, identifier)
    , mMoreParameter(moreParameter)
    , mType(DATA_TYPES.at(type)) 
{}


eDataType Parameter::GetType() const
{
    return mType;
}
Node* Parameter::GetNextParameter() const
{
    return mMoreParameter;
}