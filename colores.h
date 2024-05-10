// YUSHAN YANG XU
// BRYAN XAVIER QUILUMBA FARINANGO

#ifndef COLORES_H
#define COLORES_H
#include <iostream>
#include <iomanip>
#include "juego.h"

// Otra idea de colores en C++:
//  
//https://gist.github.com/Alfonzzoj/db207b89d56f24d9d0b17ff93e091be8
// 
//     cout << BLUE << BG_LGREEN << "This text is BLUE!     " << RESET << endl;
//     cout << BLUE << "This text is BLUE!     "<< endl;

//===Color font code===/
#define BLACK   "\x1B[30m"
#define RED     "\x1B[38;2;255;0;0m"//"\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1B[38;2;255;255;0m" //"\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define WHITE   "\x1B[37m"
#define ORANGE  "\x1B[38;2;204;102;0m"
#define ROSE    "\x1B[38;2;255;151;203m"
#define LBLUE   "\x1B[38;2;53;149;240m"
#define LGREEN  "\x1B[38;2;17;245;120m"
#define GRAY    "\x1B[38;2;176;174;174m"
#define RESET   "\x1b[0m"

//===Color background code===/
#define BG_BLACK   "\x1B[40m"
#define BG_RED     "\x1B[41m"
#define BG_GREEN   "\x1B[42m"
#define BG_YELLOW  "\x1B[43m"
#define BG_BLUE    "\x1B[44m"
#define BG_MAGENTA "\x1B[45m"
#define BG_CYAN    "\x1B[46m"
#define BG_WHITE   "\x1B[47m"
#define BG_ORANGE  "\x1B[48;2;204;102;0m"
#define BG_LBLUE   "\x1B[48;2;53;149;240m"
#define BG_LGREEN  "\x1B[48;2;17;245;120m"
#define BG_GRAY    "\x1B[48;2;176;174;174m"
#define BG_ROSE    "\x1B[48;2;255;151;203m"

#define BG_VERDELIMA    "\x1B[48;2;204;255;0m"
#define BG_ROSA    "\x1B[48;2;255;0;255m"


// CONSTANTES
const char Horizontal = char(196);
const char UpperLeft = char(218);
const char UpperCross = char(194);
const char UpperRight = char(191);
const char Vertical = char(179);
const char MidLeft = char(195);
const char MidCross = char(197);
const char MidRight = char(180);
const char LowerLeft = char(192);
const char LowerCross = char(193);
const char LowerRight = char(217);
const char Square = char(219);

const int DEFAULT_COLOR = -1;

void mostrar(Juego const& juego);
#endif // COLORES_H