#include <smald.h>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>

namespace smald {
    void printVersion() {
        std::cout << "Smald version: v" << SMALD_VERSION_MAJOR << '.' << SMALD_VERSION_MINOR << '.' << SMALD_VERSION_PATCH << std::endl;
    }

    namespace util {
        namespace string {
            std::string ltrim(std::string str, const char chr) {
                std::string result;
                bool trimming = true;

                for (char &schr : str) {
                    if (!trimming) {
                        result += schr;
                    } else {
                        if (schr != chr)
                            trimming = false;
                            result += schr;
                    }
                }

                return result;
            }

            std::string rtrim(std::string str, const char chr) {
                std::string result;
                std::reverse(str.begin(), str.end());
                bool trimming = true;

                for (char &schr : str) {
                    if (!trimming) {
                        result += schr;
                    } else {
                        if (schr != chr)
                            trimming = false;
                            result += schr;
                    }
                }

                std::reverse(result.begin(), result.end());
                return result;
            }

            std::string trim(std::string str, const char chr) {
                return rtrim(ltrim(str, chr), chr);
            }

            std::vector<std::string> split(const char *str, const char separator, int limit) {
                std::vector<std::string> result;
                std::stringstream stream(str);
                std::string token;

                while (std::getline(stream, token, separator)) {
                    if (result.size() < limit || limit <= 0) {
                        result.push_back(token);
                    } else {
                        break;
                    }
                }

                return result;
            }
        }

        namespace file {
            Conf::Conf(const char *filePath) {
                std::string line;
                std::vector<std::string> lineopt;
                std::fstream confile;
                confile.open(filePath, std::ios::in);

                while (getline(confile, line)) {
                    line = util::string::trim(line);

                    if (line[0] == '#')
                        continue;

                    if (!line.empty() || line.length() > 0) {
                        lineopt = this->parseOption(line);

                        if (!this->hasKey(lineopt[0].c_str()))
                            this->data.insert({lineopt[0], lineopt[1]});
                        else
                            this->data[lineopt[0]] = lineopt[1];
                    }
                }

                confile.close();
            }

            std::vector<std::string> Conf::parseOption(std::string line) {
                std::string key;
                std::string value;
                std::vector<std::string> result;

                std::vector<std::string> tokens = util::string::split(line.c_str(), '=', 2);

                if (tokens.size() == 2) {
                    key = util::string::trim(tokens[0]);
                    value = util::string::trim(tokens[1]);
                    result.push_back(key);
                    result.push_back(value);

                    return result;
                } else {
                    throw exception::ParsingError("invalid option");
                }
            }

            const char *Conf::get(const char *key) {
                return this->data[key].c_str();
            }

            void Conf::set(const char *key, const char *value) {
                if (!hasKey(key))
                    this->data.insert({key, value});
                else
                    this->data[key] = value;
            }

            void Conf::remove(const char *key) {
                this->data.erase(key);
            }

            bool Conf::hasKey(const char *key) {
                return this->data.count(key) > 0;
            }
        }
    }

    std::vector<std::string> parseArgs(std::string str) {
        std::vector<std::string> result;
        std::string segment;
        bool inQuote = false;
        char quoteType = NULL;

        for (char &chr : str) {
            if (!inQuote) {
                if (chr == ' ') {
                    if (!segment.empty())
                        result.push_back(segment);
                        segment.clear();
                } else if (chr == '"' || chr == '\'') {
                    inQuote = true;
                    quoteType = chr;
                } else {
                    segment += chr;
                }
            } else {
                if (quoteType == chr) {
                    if (!segment.empty())
                        result.push_back(segment);
                        segment.clear();
                    inQuote = false;
                    quoteType = NULL;
                } else {
                    segment += chr;
                }
            }
        }

        if (!segment.empty())
            result.push_back(segment);
            segment.clear();

        if (inQuote == true)
            throw exception::ParsingError("No closing quotation!");

        return result;
    }

    Parser::Parser(std::string text) {
        this->text = text;
        this->index = -1;
        this->currentChar = NULL;
    }

    void Parser::shift() {
        this->index++;
        this->currentChar = (this->index < this->text.length()) ? this->text[this->index] : NULL;
    }

    void Parser::parse() {
        while (this->currentChar != NULL) {
            this->shift();
        }
    }

    namespace exception {
        ParsingError::ParsingError(const char *message) {
            this->message = message;
        }

        const char *ParsingError::what() const throw() {
            return this->message.c_str();
        }
    }

    namespace command {
        PrefixParser::PrefixParser(std::string text, const char *prefix) : Parser(text) {
            this->prefix = prefix;
        }

        void PrefixParser::parse() {
            size_t spaceCount = 0;
            std::string __pref;

            this->shift();
            while (this->currentChar != NULL) {
                if (this->currentChar == ' ') {
                    spaceCount++;
                } else {
                    __pref = util::string::rtrim(this->text.substr(0, this->index));

                    if (__pref == this->prefix && spaceCount <= 1) {
                        this->args = util::string::ltrim(this->text.substr(this->index, this->text.length()));
                        break;
                    }
                }

                this->shift();
            }
        }

        Command::Command(std::string text, const char *prefix, int maxArgs) {
            std::vector<std::string> argres;

            this->prefix = prefix;

            PrefixParser prefargs(text, prefix);
            prefargs.parse();

            if (!prefargs.args.empty())
                for(std::string elm : parseArgs(prefargs.args)) {
                    argres.push_back(elm);
                }

            if (maxArgs == 0)
                maxArgs = (argres.size() - 1) >= 0 ? argres.size() - 1 : 0;

            if ((argres.size() - 1) >= 0 && (argres.size() - 1) > maxArgs)
                throw exception::ParsingError("arguments exceeds max arguments");

            while ((argres.size() - 1) >= 0 && (argres.size() - 1) < maxArgs) {
                argres.push_back("");
            }

            if (argres.size())
                this->name = argres[0];
                for(int i = 1; i < argres.size(); i++) {
                    this->args.push_back(argres[i]);
                }
        }

        const char *Command::getName() {
            return this->name.c_str();
        }

        const char *Command::getPrefix() {
            return this->prefix.c_str();
        }

        std::vector<std::string> Command::getArgs() {
            return this->args;
        }

        const char *Command::getArg(int index) {
            return this->args[index].c_str();
        }
    }
}
