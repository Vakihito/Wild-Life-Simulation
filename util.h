#ifndef UTIL_H
#define UTIL_H

#include <iostream>

using namespace std;

/*
    Imprime texto colorido
    @param text: conteúdo da impressão
    @param color: cor da impressão
    @param new_line: indica quebra de linha ao término da mensagem
*/
void print_text(string text, string color, bool new_line);

/*
    Imprime nome no formato "[name]: " com a cor especificada
    @param name: nome a ser impresso
    @param color: cor da impressão 
*/
void print_name(string name, string color);

#endif