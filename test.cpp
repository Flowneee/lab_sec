#include <iostream>
#include <vector>
#include <sstream>

#include "user.hpp"
#include "passwdmanager.hpp"

int main (int argc, char *argv[])
{
    PasswdManager pm("passwd");
    for (auto i: pm.get_users()) {
        std::cout << i.str(sys) << std::endl;
    }
    return 0;
}
