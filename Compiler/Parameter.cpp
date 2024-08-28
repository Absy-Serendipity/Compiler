#include "Parameter.h"

eDataType Parameter::GetType() const
{
    return mType;
}
Node* Parameter::GetNextParameter() const
{
    return mMoreParameter;
}