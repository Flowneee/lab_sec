#ifndef __VALIDATOR_H__
#define __VALIDATOR_H__

/**
 * lab_sec
 * Copyright (C) 2016  Kononov Andrey <flowneee@protonmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

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
