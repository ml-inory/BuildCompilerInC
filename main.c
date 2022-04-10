#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE_OF_ERROR_STRING    (128)
#define MAX_SIZE_OF_EXP             (256)

// boolean type
typedef enum _BOOL
{
    FALSE = 0,
    TRUE  = 1
} BOOL;

// Constant Declarations

// Variable Declarations
char Look;      // Lookahead Character

// Read New Character From Input Stream
void GetChar()
{
    Look = getchar();
}

// Report an Error
void Error(const char* s)
{
    printf("\n");
    printf("Error: %s.", s);
}

// Report Error and Halt
void Abort(const char* s)
{
    Error(s);
    exit(-1);
}

// Report What Was Expected
void Expected(const char* s)
{
    char s_e[MAX_SIZE_OF_ERROR_STRING];
    snprintf(s_e, MAX_SIZE_OF_ERROR_STRING, "%s Expected\n", s);
    Abort(s_e);
}

// Match a Specific Input Character
void Match(char x)
{
    if (Look == x)
        GetChar();
    else
    {
        char s_e[MAX_SIZE_OF_ERROR_STRING];
        snprintf(s_e, MAX_SIZE_OF_ERROR_STRING, "\"%c\"", x);
        Expected(s_e);
    }
}

// Recognize an Alpha Character
BOOL IsAlpha(char c)
{
    // [A .. Z]: 65 ~ 90
    // [a .. z]: 97 ~ 122
    if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
        return TRUE;
    else
        return FALSE;
}

// Recognize a Decimal Digit
BOOL IsDigit(char c)
{
    // [0 .. 9]: 48 ~ 57
    if (c >= 48 && c <= 57)
        return TRUE;
    else
        return FALSE;
}

// Get Uppercase of Character
char Upcase(char c)
{
    // [A .. Z]: 65 ~ 90
    // [a .. z]: 97 ~ 122
    if (c >= 65 && c <= 90) 
        return c;
    else if (c >= 97 && c <= 122)
        return c - 32;
    else
        return 0;
}

// Get an Identifier
char GetName()
{
    if (FALSE == IsAlpha(Look))
    {
        Expected("Name");
    }
    
    char ret = Upcase(Look);
    GetChar();
    return ret;
}

// Get a Number
char GetNum()
{
    if (FALSE == IsDigit(Look))
    {
        Expected("Integer");
    }

    char ret = Look;
    GetChar();
    return ret;
}

// Output a String with Tab
void Emit(const char* s)
{
    printf("\t%s", s);
}

// Output a String with Tab and CRLF
void EmitLn(const char* s)
{
    Emit(s);
    printf("\n");
}

// Parse and Translate a Math Term
void Term()
{
    char exp[MAX_SIZE_OF_EXP];
    snprintf(exp, MAX_SIZE_OF_EXP, "mov edx, %c", GetNum());
    EmitLn(exp);
}

// Recognize and Translate an Add
void Add()
{
    Match('+');
    Term();
    EmitLn("add edx, ecx");
}

// Recognize and Translate a Subtract
void Subtract()
{
    Match('-');
    Term();
    EmitLn("sub edx, ecx");
    EmitLn("neg edx");
}

// Parse and Translate a Math Expression
void Expression()
{
    Term();
    while (Look == '+' || Look == '-')
    {
        EmitLn("mov ecx, edx");
        switch (Look)
        {
        case '+':
        {
            Add();
            break;
        }
        case '-':
        {
            Subtract();
            break;
        }
        default:
        {
            Expected("Addop");
            break;
        }
        }
    }
}

// Initialize
void Init()
{
    GetChar();
}

// Main Program
void main()
{
    Init();
    Expression();
}