#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <random>
#include "quantumcomputer.h"
#include "UI.h"
#include "parser.h"

using namespace std;

const std::string bar      = "+==============================================================================+";
const std::string subar    = "|                                                                              |";
const std::string titlebar = "Quantum Simulator V 2.0 by Tallys Assis";

void printCircuitBox(std::vector<std::string> circuit, string measures)
{
    cout<<titlebar<<endl;
    cout<<bar<<endl<<subar<<endl;
    for(int i = 0; i < circuit.size(); i++)
    {
        std::string line = "| " + circuit[i];
        line.append(79 - line.length(), ' ');
        line += '|';
        cout<<line<<endl;
    }
    cout<<subar<<endl<<bar<<endl<<endl;

    cout<<"Measures: ";
    cout<<measures;
    cout<<endl;
}

string dec_to_bin(int dec)
{
    string bin = "";
    while(dec > 0)
    {
        if(dec % 2 == 0)
            bin = "0" + bin;
        else
            bin = "1" + bin;

        dec = dec >> 1;
    }

    return bin;
}

int main()
{
    //A seed do computador é gerada pelo dia, um offset arbitrário e inicializada
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);
    const int dia = now->tm_mday;
    const int mes = now->tm_mon + 1;
    const int seedOffset = 2;
    int seed = (dia * mes) + seedOffset; //Seed para inicializar o computador

    int circuitSize = 0;

    std::vector<std::string> screen;
        std::string measures = "";

        Circuit* c = nullptr;

        bool stop = false;
        bool started = false;
        std::string input;

        char gate = '\0';
        //Apesar de nomes descritivos esses dois vão gerenciar todos os argumentos dos inputs
        int control = -1, target = -1;

        //the bug zone
        //Usei isso para carregar inicializações durante fase de testes
        //the bug zone

        QuantumComputer qc(seed);

        cout<<"\033c";
        printCircuitBox(screen, measures);

        /*
         O flow de funcionamento é bem simples
         Started determina se o computador está ligado ou não, e determina quais comandos estão disponíveis
         stop determina se o programa deve continuar rodando
         comandos como poweroff irão desligar o computador mas não parar o programa
         */
        while(!stop)
        {
            cout<<endl<<"> ";
            std::getline(std::cin, input);
            //input.pop_back();

            if(!started)
            {
                if(parseBoot(input, control))
                {
                    qc.boot(control);
                    c = new Circuit(control);
                    started = true;
                    circuitSize = control;
                    //qc.h(0);
                }
                if(parseQuit(input))
                {
                    stop = true;
                }
            }
            else
            {
                //Em teoria é possível paralelizar esses ifs, mas não creio que o ganho valha a pena
                //Aqui processar os inputs
                if( parseAdd (input, gate, control))
                {

                    switch(gate) //Um código assim é O(1), então apesar de feio é rápido
                    {
                    case 'I':
                        qc.id(control);
                        break;
                    case 'X':
                        qc.x(control);
                        break;
                    case 'Y':
                        qc.y(control);
                        break;
                    case 'Z':
                        qc.z(control);
                        break;
                    case 'T':
                        qc.t(control);
                        break;
                    case 'S':
                        qc.s(control);
                        break;
                    case 'H':
                        qc.h(control);
                        break;
                    case 's':
                        qc.sdg(control);
                        break;
                    case 't':
                        qc.tdg(control);
                        break;
                    }

                    c->insertGate(gate, control, target);

                }
                else if( parseControl(input, gate, control, target))
                {
                    switch(gate)
                    {
                    case '+':
                        qc.cnot(control, target);
                        break;
                    }
                    c->insertGate(gate, target, control); //Macete pra porta não ficar invertida
                }
                else if( parseQuit (input))
                {
                    stop = true;
                }
                else if( parseShutdown (input))
                {
                    delete c;
                    started = false;
                    screen.clear();
                }
                else if( parseMeasure (input))
                {
                    int measure = qc.measureQreg();
                    measures = to_string(measure);
                    string complement = "";
                    complement.append(circuitSize - dec_to_bin(measure).length(), '0');
                    measures += " \t |" + complement + dec_to_bin(measure) + ">";
                    started = false;
                }
                else if( parseFakeMeasure(input))
                {
                    seed++;
                    int measure = qc.fakemeasure(seed);
                    measures = to_string(measure);
                    string complement = "";
                    complement.append(circuitSize - dec_to_bin(measure).length(), '0');
                    measures += " \t |" + complement + dec_to_bin(measure) + ">";
                }
            }

            if(started)
                screen = c->getScreen();
            cout<<"\033c"; // Limpar tela
            printCircuitBox(screen, measures);

            gate = '\0';
            control = -1, target = -1;
        }
    return 0;
}
