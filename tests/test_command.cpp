#include <smald.h>
#include <cstring>

using namespace smald::command;

int main() {
    int result = 0;
    const char *expectedArgs[3] = {
        "foo", "bar", "foo bar"
    };
    Command ping("!ping foo bar 'foo bar'", "!");

    if (strcmp(ping.getName(), "ping"))
        result = 1 ;

    if (strcmp(ping.getPrefix(), "!"))
        result = 2;

    if (ping.getArgs().size() != 3)
        result = 3;

    for(int i = 0; i < (sizeof(expectedArgs) / sizeof(*expectedArgs)); i++) {
        if (strcmp(expectedArgs[i], ping.getArgs()[i].c_str()))
            result = 4;
            break;
    }

    return result;
}
