// Cradle that you can start with.

// Original Pascal code snippet from https://compilers.iecc.com/crenshaw/tutor1.txt
/*
*****************************************************************
*                                                               *
*                        COPYRIGHT NOTICE                       *
*                                                               *
*   Copyright (C) 1988 Jack W. Crenshaw. All rights reserved.   *
*                                                               *
*****************************************************************

{--------------------------------------------------------------}
program Cradle;

{--------------------------------------------------------------}
{ Constant Declarations }

const TAB = ^I;

{--------------------------------------------------------------}
{ Variable Declarations }

var Look: char;              { Lookahead Character }
                              
{--------------------------------------------------------------}
{ Read New Character From Input Stream }

procedure GetChar;
begin
   Read(Look);
end;

{--------------------------------------------------------------}
{ Report an Error }

procedure Error(s: string);
begin
   WriteLn;
   WriteLn(^G, 'Error: ', s, '.');
end;


{--------------------------------------------------------------}
{ Report Error and Halt }

procedure Abort(s: string);
begin
   Error(s);
   Halt;
end;


{--------------------------------------------------------------}
{ Report What Was Expected }

procedure Expected(s: string);
begin
   Abort(s + ' Expected');
end;

{--------------------------------------------------------------}
{ Match a Specific Input Character }

procedure Match(x: char);
begin
   if Look = x then GetChar
   else Expected('''' + x + '''');
end;


{--------------------------------------------------------------}
{ Recognize an Alpha Character }

function IsAlpha(c: char): boolean;
begin
   IsAlpha := upcase(c) in ['A'..'Z'];
end;
                              

{--------------------------------------------------------------}

{ Recognize a Decimal Digit }

function IsDigit(c: char): boolean;
begin
   IsDigit := c in ['0'..'9'];
end;


{--------------------------------------------------------------}
{ Get an Identifier }

function GetName: char;
begin
   if not IsAlpha(Look) then Expected('Name');
   GetName := UpCase(Look);
   GetChar;
end;


{--------------------------------------------------------------}
{ Get a Number }

function GetNum: char;
begin
   if not IsDigit(Look) then Expected('Integer');
   GetNum := Look;
   GetChar;
end;


{--------------------------------------------------------------}
{ Output a String with Tab }

procedure Emit(s: string);
begin
   Write(TAB, s);
end;




{--------------------------------------------------------------}
{ Output a String with Tab and CRLF }

procedure EmitLn(s: string);
begin
   Emit(s);
   WriteLn;
end;

{--------------------------------------------------------------}
{ Initialize }

procedure Init;
begin
   GetChar;
end;


{--------------------------------------------------------------}
{ Main Program }

begin
   Init;
end.
{--------------------------------------------------------------}

*/

// C code starts below
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE_OF_ERROR_STRING    (128)

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

// Check If an Addop
BOOL IsAddop(char c)
{
    if (c == '+' || c == '-')
        return TRUE;
    else
        return FALSE;
}

// Check If a Mulop
BOOL IsMulop(char c)
{
    if (c == '*' || c == '/')
        return TRUE;
    else
        return FALSE;
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
}