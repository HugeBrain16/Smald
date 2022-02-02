#include <smald.h>
#include <string>

int main() {
    std::string str = "  conductor we have a problem!!  ";
    std::string expectedStr = "conductor we have a problem!!";
    std::string trimmedStr = smald::util::string::trim(str);

    return trimmedStr == expectedStr;
}
