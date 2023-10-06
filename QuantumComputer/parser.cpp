#include <string>
#include <regex>

bool parseAdd(const std::string& input, char& letter, int& control, int& target)
{
    std::regex command("add ([IXYZTSH+st]) (\\d+)( \\-t (\\d+))?");
    std::smatch match;
    bool hasTarget;

    if (std::regex_match(input, match, command)) {
        // O parsing foi bem-sucedido
        letter = match[1].str()[0];
        control = std::stoi(match[2]);
        hasTarget = match[4].matched; // Verifica se a parte opcional está presente
        if (hasTarget) {
            target = std::stoi(match[4]);
        }
        return true;
    }

    return false;
}

bool parseQuit(const std::string& input)
{
    std::regex command("(quit|exit)");
    std::smatch match;

    if (std::regex_match(input, match, command))
        return true;

    return false;
}

bool parseBoot(const std::string& input, int& qubits)
{
    std::regex command("start with (\\d+)");
    std::smatch match;

    if (std::regex_match(input, match, command))
    {
        qubits = std::stoi(match[1]);
        return true;
    }

    return false;
}

bool parseShutdown(const std::string& input)
{
    std::regex command("poweroff");
    std::smatch match;

    if (std::regex_match(input, match, command))
        return true;

    return false;
}

bool parseMeasure(const std::string& input)
{
    std::regex command("measure");
    std::smatch match;

    if (std::regex_match(input, match, command))
    {
        return true;
    }

    return false;
}
