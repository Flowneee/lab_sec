#ifndef __VALIDATOR_H__
#define __VALIDATOR_H__

#include <string>
#include <regex>
#include <functional>
#include <vector>


using ValidatorFunction = std::function<bool(std::wstring)>;

extern ValidatorFunction latin_upper;
extern ValidatorFunction latin_lower;
extern ValidatorFunction latin;
extern ValidatorFunction number;
extern ValidatorFunction math;
extern ValidatorFunction punctuation;
extern ValidatorFunction cyrillic_upper;
extern ValidatorFunction cyrillic_lower;
extern ValidatorFunction cyrillic;
extern ValidatorFunction upper;
extern ValidatorFunction lower;
ValidatorFunction construct_validator_function(std::wstring pattern);

class Validator
{
public:
    Validator(ValidatorFunction function, std::wstring explanation)
        : function(function), explanation(explanation) {};
    Validator(std::wstring pattern, std::wstring explanation);
    ~Validator() {};

    bool operator()(std::wstring password);
    std::wstring get_explanation();
protected:

private:
    ValidatorFunction function;
    std::wstring explanation;
};

//extern const std::vector<Validator> VALIDATORS;

#endif
