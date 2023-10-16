#ifndef PARSER_H
#define PARSER_H

#pragma once

#include <string>
#include <regex>

/*
 Todos os parsers aqui são iguais
 Se der match, os devidos argumentos serão colocados em suas variáveis.
 */

bool parseAdd(const std::string& input, char& letter, int& control)
{
    std::regex command("add ([IXYZTSHst]) (\\d+)");
    std::smatch match;
    bool hasTarget;

    if (std::regex_match(input, match, command)) {
        // O parsing foi bem-sucedido
        letter = match[1].str()[0];
        control = std::stoi(match[2]);
        return true;
    }

    return false;
}

bool parseControl(const std::string& input, char& letter, int& control, int& target)
{
    std::regex command("add ([+]) (\\d+) \\-t (\\d+)");
    std::smatch match;
    bool hasTarget;

    if (std::regex_match(input, match, command)) {
        // O parsing foi bem-sucedido
        letter = match[1].str()[0];
        control = std::stoi(match[2]);
        target = std::stoi(match[3]);
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

bool parseFakeMeasure(const std::string& input)
{
    std::regex command("fake");
    std::smatch match;

    if (std::regex_match(input, match, command))
    {
        return true;
    }

    return false;
}


#endif // PARSER_H
