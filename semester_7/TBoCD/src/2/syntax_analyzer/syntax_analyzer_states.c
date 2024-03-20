#include "syntax_analyzer.pvt.h"

#define ESE END_SYNTAX_ERROR
#define E_IFE END_IDENT_FORMAT_ERROR
#define E_MFPE END_MISSING_FRAC_PART_ERROR

const static int _states[LITER_MAX_CODE][16] = {
  [LITER_F]              = {                  1,   6,   6,            6,   6,         ESE,     6,     8,             10,    10,          E_IFE, ESE,    ESE, ESE, ESE,       ESE },
  [LITER_O]              = {                  6,   2,   6,            6,   5,         ESE,     6,     8,             10,    10,          E_IFE, ESE,    ESE, ESE, ESE,       ESE },
  [LITER_R]              = {                  6,   6,   3,            6,   6,         ESE,     6,     8,             10,    10,          E_IFE, ESE,    ESE, ESE, ESE,       ESE },
  [LITER_T]              = {                  4,   6,   6,            6,   6,         ESE,     6,     8,             10,    10,          E_IFE, ESE,    ESE, ESE, ESE,       ESE },
  [LITER_ANY_SYMBOL]     = {                  6,   6,   6,            6,   6,         ESE,     6,     8,             10,    10,          E_IFE, ESE,    ESE, ESE, ESE,       ESE },
  [LITER_NON_ZERO_DIGIT] = {                 12,   6,   6,            6,   6,         ESE,     6,     7,              9,     9,              9,  12,     12,  12,  15,        15 },
  [LITER_ZERO]           = {                 12,   7,   7,            7,   7,         ESE,     7,     7,              9,     9,              9,  12,     12,  12,  15,        15 },
  [LITER_SIGN_PLUS]      = {                 11, ESE, ESE, END_WORD_FOR, ESE, END_WORD_TO, E_IFE, E_IFE, END_IDENTIFIER, E_IFE, END_IDENTIFIER, ESE, E_MFPE, ESE, ESE, END_CONST },
  [LITER_SIGN_MINUS]     = {                 13, ESE, ESE, END_WORD_FOR, ESE, END_WORD_TO, E_IFE, E_IFE, END_IDENTIFIER, E_IFE, END_IDENTIFIER, ESE, E_MFPE, ESE, ESE, END_CONST },
  [LITER_OPEN_BRACE]     = {     END_OPEN_BRACE, ESE, ESE, END_WORD_FOR, ESE, END_WORD_TO, E_IFE, E_IFE, END_IDENTIFIER, E_IFE, END_IDENTIFIER, ESE, E_MFPE, ESE, ESE, END_CONST },
  [LITER_CLOSE_BRACE]    = {    END_CLOSE_BRACE, ESE, ESE, END_WORD_FOR, ESE, END_WORD_TO, E_IFE, E_IFE, END_IDENTIFIER, E_IFE, END_IDENTIFIER, ESE, E_MFPE, ESE, ESE, END_CONST },
  [LITER_SIGN_EQUAL]     = {         END_ASSIGN, ESE, ESE, END_WORD_FOR, ESE, END_WORD_TO, E_IFE, E_IFE, END_IDENTIFIER, E_IFE, END_IDENTIFIER, ESE, E_MFPE, ESE, ESE, END_CONST },
  [LITER_SEMICOLON]      = {      END_SEMICOLON, ESE, ESE, END_WORD_FOR, ESE, END_WORD_TO, E_IFE, E_IFE, END_IDENTIFIER, E_IFE, END_IDENTIFIER, ESE, E_MFPE, ESE, ESE, END_CONST },
  [LITER_STAR]           = {           END_STAR, ESE, ESE, END_WORD_FOR, ESE, END_WORD_TO, E_IFE, E_IFE, END_IDENTIFIER, E_IFE, END_IDENTIFIER, ESE, E_MFPE, ESE, ESE, END_CONST },
  [LITER_DIVIDE]         = {          END_SLASH, ESE, ESE, END_WORD_FOR, ESE, END_WORD_TO, E_IFE, E_IFE, END_IDENTIFIER, E_IFE, END_IDENTIFIER, ESE, E_MFPE, ESE, ESE, END_CONST },
  [LITER_DOT]            = {   END_SYNTAX_ERROR, ESE, ESE, END_WORD_FOR, ESE, END_WORD_TO, E_IFE, E_IFE, END_IDENTIFIER, E_IFE, END_IDENTIFIER, ESE,     14, ESE, ESE, END_CONST },
  [LITER_SPACE]          = {                  0, ESE, ESE, END_WORD_FOR, ESE, END_WORD_TO, E_IFE, E_IFE, END_IDENTIFIER, E_IFE, END_IDENTIFIER, ESE, E_MFPE, ESE, ESE, END_CONST },
  [LITER_INCORRECT_SYMBOL] = { END_SYNTAX_ERROR, ESE, ESE, END_WORD_FOR, ESE, END_WORD_TO, E_IFE, E_IFE, END_IDENTIFIER, E_IFE, END_IDENTIFIER, ESE,    ESE, ESE, ESE, END_CONST }
};

int _analyzer_next_state(state_liter_t liter, int state) {
  return _states[liter][state];
}
