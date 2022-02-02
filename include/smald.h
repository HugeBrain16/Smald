#include <string>
#include <vector>
#include <map>
#include <functional>
#include <exception>

#define SMALD_VERSION_MAJOR 0
#define SMALD_VERSION_MINOR 3
#define SMALD_VERSION_PATCH 0

namespace smald {
    void printVersion(void);
    std::vector<std::string> parseArgs(std::string str);
    class Parser {
        public:
            std::string text;
            int index;
            char currentChar;
            
            Parser(std::string text);
            virtual void parse();
            void shift();
    };

    namespace util {
        namespace string {
            std::string ltrim(std::string str, const char chr = ' ');
            std::string rtrim(std::string str, const char chr = ' ');
            std::string trim(std::string str, const char chr = ' ');

            /* set limit to 0 or lower to disable limitation */
            std::vector<std::string> split(const char *string, const char separator, int limit = 0);
        }

        namespace file {
            typedef std::map<std::string, std::string> Option;

            class Conf {
                Option data;

                public:
                    Conf(const char *filePath);
                    const char *get(const char *key);
                    void set(const char *key, const char *value);
                    void remove(const char *key);
                    bool hasKey(const char *key);

                private:
                    std::vector<std::string> parseOption(std::string line);
            };
        }
    }

    namespace exception {
        class ParsingError : public std::exception {
            std::string message;

            public:
                ParsingError(const char* message);
                const char *what() const throw();
        };
    }

    namespace command {
        class PrefixParser : public Parser {
            public:
                std::string prefix;
                std::string args;

                PrefixParser(std::string text, const char *prefix = "/");
                void parse();
        };

        class Command {
            /* A class for parsing command like in irc server
            *
            * kind of like implementation of https://github.com/HugeBrain16/cmdtools in C++
            *
            * Constructor parameters:
            *     - <std::string> text:
            *         A text in a command form like to parse,
            *
            *         example: "/whisper madlad21 'who are you?'"
            *
            *         prefix is removed from the text, 'whisper' is the name of the command,
            *         'madlad21' and 'who are you?' are the arguments.
            *
            *     - <const char *> prefix:
            *         prefix of the command
            *
            *     - <int> maxArgs:
            *         max argument allowed, if not enough argument passed,
            *         it will be filled with empty strings.
            *
            * Methods:
            *     - <const char *> getName():
            *         - Returns:
            *             the name of the command
            *
            *     - <std::vector<std::string> getArgs():
            *         - Returns:
            *             vector containing string arguments
            *
            *     - <const char *> getArg(int index):
            *         - Parameters:
            *             - <int> index:
            *                 index of element that contains an argument
            *
            *         - Returns:
            *             a string argument
            *     - <const char *> getPrefix():
            *         - Returns:
            *             the command prefix
            */

            std::vector<std::string> args;
            std::string name;
            std::string prefix;

            public:
                Command(std::string text, const char *prefix = "/", int maxArgs = 0);
                const char *getName();
                const char *getPrefix();
                std::vector<std::string> getArgs();
                const char *getArg(int index);
        };
    }
}
