#include <smald.h>
#include <string>
#include <vector>

int main() {
    std::string str = "foo bar 'deez nuts'";
    std::vector<std::string> expectedArgs {
        "foo", "bar", "deez nuts"
    };
    std::vector<std::string> args = smald::parseArgs(str);
    int expectedElementCount = 3;

    if (args.size() == expectedElementCount)
        for (int i = 0; i < args.size(); i++) {
            if (args[i] != expectedArgs[i])
                return 2;
        }

        return 0;

    return 1;
}