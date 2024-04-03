#include "Error.hpp"

Error::Error()
{ 
    _errorMsg = (char*)"No errors";
    _errorCode = ERROR_BLANK;
    _OKFlag = true;
}

Error::Error(ErrorCode code, ErrorMsg msg)
{
    _errorCode = code;
    _errorMsg = (char*)msg.c_str();
    _OKFlag = code != ERROR_BLANK;
}

Error::~Error()
{
    //delete _errorMsg;
}

std::string Error::GetErrorMsg()
{
    return std::string(_errorMsg);
}

ErrorCode Error::GetErrorCode()
{
    return _errorCode;
}

Error Error::GetError()
{
    return *this;
}

Error::printErrorHandle Error::PrintError = nullptr;

bool Error::IsOK()
{
    return _OKFlag;
}

bool Error::operator==(Error a)
{
    bool result = true;
    result &= this->_errorCode == a._errorCode;
    result &= this->_errorMsg == a._errorMsg;

    return result;
}

bool Error::operator!=(Error a)
{
    bool result = true;
    result &= this->_errorCode != a._errorCode;
    result &= this->_errorMsg != a._errorMsg;

    return result;
}


ResourceLoadException::ResourceLoadException() : _mes("Resource load error!")
{
    ;
}

ResourceLoadException::ResourceLoadException(const char* mes) : _mes(mes)
{
    ;
}

const char* ResourceLoadException::what()
{
    return _mes;
}