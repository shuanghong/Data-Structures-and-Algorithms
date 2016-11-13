#include "String.h"


int main(int argc, char* argv[])
{
    /*
    myString string1("C-style string1");

    myString string2("C-style string2");
    */

    /*
    const myString string3("string for copy");

    myString string_copy2(string3);

    myString string_move(std::move(string_copy2));

    myString string_list = {'C', '-', 's', 't', 'y', 'l', 'e', ' ', 's', 't', 'r', 'i', 'n', 'g'};
    */

    myString string_copy1 = "string for copy";

    myString string_copy_assignment = "string for copy assignment";

    //string_copy1 = string_copy_assignment;
    string_copy1 = std::move(string_copy_assignment);

    return 0;

}
