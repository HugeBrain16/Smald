#include <smald.h>
#include <cstring>
#include <iostream>

using namespace smald::util::file;

int main() {
    int result = 0;

    Conf testconf(TEST_CONF_FILEPATH);

    if (!testconf.hasKey("foo")) {
        result = 1;
    } else {
        if (strcmp(testconf.get("foo"), "bar"))
            result = 2;
    }

    return result;
}
