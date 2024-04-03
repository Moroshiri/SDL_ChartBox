#ifndef _ERROR_HPP_
#define _ERROR_HPP_

#include <string>

enum ErrorCode
{
    ERROR_BLANK,
    ERROR_EXCEPTION,
    ERROR_WINDOW_SDLINIT,
    ERROR_WINDOW_IMGINIT,
    ERROR_WINDOW_WINCREATION,
    ERROR_WINDOW_RENDCREATION,
    ERROR_TEXTURE_LOAD,
    ERROR_TEXTURE_CREATE,
    ERROR_GRID_SIZESET,
    ERROR_GRID_OUTOFRANGE,
    ERROR_LAST
};

typedef std::string ErrorMsg;

class Error
{
public:

    Error();
    Error(ErrorCode code, ErrorMsg msg);
    ~Error();

    ErrorMsg GetErrorMsg();
    ErrorCode GetErrorCode();
    Error GetError();

    typedef void (*printErrorHandle)(Error);
    static printErrorHandle PrintError;

    bool IsOK();

    bool operator ==(Error a);
    bool operator !=(Error a);

protected:
    ErrorMsg _errorMsg;
    ErrorCode _errorCode;
    bool _OKFlag;
};

class ResourceLoadException : public std::exception
{
public:
    ResourceLoadException();
    ResourceLoadException(const char* message);

    const char *what();
private:
    const char* _mes;
};

#endif