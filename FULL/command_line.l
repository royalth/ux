%{
#include "parser.h"
#include "command_line.tab.h"
%}

%option reentrant

/* === State definitions === */
/* Single-quoted string: we are in between 'these characters' and nothing really matters until we encounter another single quote. */
%x single_quoted_string

%%
<single_quoted_string>[^']*                   { yylval.text = strdup(yytext); return ANYTHING_BUT_SINGLE_QUOTE; }
<INITIAL>'                                    { BEGIN(single_quoted_string); return SINGLE_QUOTE; }
<single_quoted_string>'                       { BEGIN(INITIAL); return SINGLE_QUOTE; }
<INITIAL>[ \t\n]+ ;
\|                                            { return PIPE; }
[0-9]+                                        { sscanf(yytext, "%d", &yylval); return NUMBER; }
[a-zA-Z0-9_\-\.,\[\]\/]+                        { yylval.text = strdup(yytext); return WORD; }

\(                                            { return LPAREN; }
\)                                            { return RPAREN; }
&                                             { return AMPERSAND; }
\>                                            { return REDIRECT_OUT; }
\<                                            { return REDIRECT_IN; }
$\(                                           { return SUBSTITUTION_START; }
.                                             { return UNKNOWN; }

%%
