
#ifndef PARAMETER_H
#define PARAMETER_H
#include <string>


class Parameter {
private:
    std::string parameter;

public:
    Parameter(std::string parameter);
    ~Parameter();
    std::string GetParameter();

};


#endif // PARAMETER_H
