#include "FunctionSignature.h"

FunctionSignature::FunctionSignature() 
	: mReturnType(eDataType::Void) 
{}

FunctionSignature::FunctionSignature(const eDataType returnType, const std::vector<eDataType>& parameterTypes)
	: mReturnType(returnType)
	, mParameterTypes(parameterTypes) 
{}

void FunctionSignature::AddParameterType(const eDataType parameterType)
{
	mParameterTypes.push_back(parameterType);
}
bool FunctionSignature::VerifyParameterTypes(const std::vector<eDataType>& parameterTypes) const
{
	return mParameterTypes == parameterTypes;
}
const eDataType FunctionSignature::GetReturnType() const 
{ 
	return mReturnType; 
}