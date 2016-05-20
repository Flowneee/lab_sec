#include "validator.hpp"


Validator::Validator(std::wstring pattern, std::wstring explanation)
    : explanation(explanation)
{
    this->function = construct_validator_function(pattern);
}

bool Validator::operator()(std::wstring password)
{
    return this->function(password);
}

std::wstring Validator::get_explanation()
{
    return this->explanation;
}

ValidatorFunction latin_upper = [](std::wstring password) -> bool
{
    return std::regex_match(password, std::wregex(L".*[A-Z].*"));
};

ValidatorFunction latin_lower = [](std::wstring password) -> bool
{
    return std::regex_match(password, std::wregex(L".*[a-z].*"));
};

ValidatorFunction latin = [](std::wstring password) -> bool
{
    return latin_upper(password) || latin_lower(password);
};

ValidatorFunction number = [](std::wstring password) -> bool
{
    return std::regex_match(password, std::wregex(L".*[0-9].*"));
};

ValidatorFunction math = [](std::wstring password) -> bool
{
    return std::regex_match(password, std::wregex(L".[\+|\-|\*|\/].*"));
};

ValidatorFunction punctuation = [](std::wstring password) -> bool
{
    return std::regex_match(password, std::wregex(L".*[\.|\!|\?|\;|\:|\,].*"));
};

ValidatorFunction cyrillic_upper = [](std::wstring password) -> bool
{
    return std::regex_match(password, std::wregex(L".*[А-ЯЁ].*"));
};

ValidatorFunction cyrillic_lower = [](std::wstring password) -> bool
{
    return std::regex_match(password, std::wregex(L".*[а-яё].*"));
};

ValidatorFunction cyrillic = [](std::wstring password) -> bool
{
    return cyrillic_upper(password) || cyrillic_lower(password);
};

ValidatorFunction upper = [](std::wstring password) -> bool
{
    return cyrillic_upper(password) || latin_upper(password);
};

ValidatorFunction lower = [](std::wstring password) -> bool
{
    return latin_lower(password) || cyrillic_lower(password);
};

ValidatorFunction construct_validator_function(std::wstring pattern)
{
    return [pattern](std::wstring password) -> bool
    {
        return std::regex_match(password, std::wregex(pattern));
    };
}

/*const std::vector<Validator> VALIDATORS =
{
    { [](std::wstring in) -> bool
      {
          return latin_upper(in) && latin_lower(in) && math(in);
      },
      L"Наличие строчных и прописных букв, а также знаков арифметических операций"},

    { [](std::wstring in) -> bool
      {
          return ((latin_upper(in) || latin_lower(in)) && math(in) &&
                  (cyrillic_upper(in) || cyrillic_lower(in)));
      },
      L"Наличие латинских букв, символов кириллицы и знаков арифметических операций"},

    { construct_validator_function(L"[a-zA-Zа-яёА-ЯЁ]+[0-9]+[a-zA-Zа-яёА-ЯЁ]+"),
      L"Чередование букв, цифр и снова букв"},

    { [](std::wstring in) -> bool
      {
          return latin_upper(in) && latin_lower(in) && cyrillic(in) && number(in);
      },
      L"Наличие строчных и прописных латинских букв, цифр и символов кириллицы" },

    { [](std::wstring in) -> bool
      {
          return latin(in) && punctuation(in) && cyrillic(in) && number(in);
      },
      L"Наличие латинских букв, символов кириллицы, цифр и знаков препинания" },

    { [](std::wstring in) -> bool
      {
          return upper(in) && punctuation(in) && lower(in) && number(in);
      },
      L"Наличие строчных и прописных букв, цифр и знаков препинания" },

    { [](std::wstring in) -> bool
      {
          return cyrillic_upper(in) && punctuation(in) && cyrillic_lower(in) && number(in);
      },
      L"Наличие строчных и прописных символов кириллицы, цифр и знаков препинания." },

    { [](std::wstring in) -> bool
      {
          return latin_upper(in) && math(in) && latin_lower(in) && number(in);
      },
      L"Наличие строчных и прописных латинских букв, цифр и знаков арифметических операций" }
};
*/
