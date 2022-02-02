/* demo program for library smald */

#include <smald.h>
#include <iostream>
#include <cstring>

using namespace smald::command;

int main() {
    smald::printVersion();

    std::string cmdtxt;
    while (1 != 0) {
        std::cout << ">> ";
        std::getline(std::cin, cmdtxt);
        Command cmd(cmdtxt);

        if (*cmd.getName()) {
            if (!strcmp(cmd.getName(), "ping")) {
                std::cout << "Pong!" << std::endl;
            } else if (!strcmp(cmd.getName(), "ban")) {
                if (cmd.getArgs().size() < 1) {
                    std::cout << "Correct usage: " << cmd.getPrefix() << cmd.getName() << " [username]" << std::endl;
                } else {
                    std::cout << cmd.getArg(0) << " Has been banned!" << std::endl;
                }
            } else if (!strcmp(cmd.getName(), "exit") || !strcmp(cmd.getName(), "quit")) {
                break;
            } else {
                std::cout << "Unknown command: " << cmd.getName() << std::endl;
            }
        } else {
            if (cmdtxt == "exit" || cmdtxt == "quit") {
                break;
            } else {
                std::cout << cmdtxt << std::endl;
            }
        }
    }

    std::cout << "Bye!" << std::endl;
    return 0;
}
