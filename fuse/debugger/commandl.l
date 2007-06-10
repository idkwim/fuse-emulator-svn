/* commandl.l: Debugger command lexical scanner
   Copyright (c) 2002 Philip Kendall

   $Id$

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, write to the Free Software Foundation, Inc.,
   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

   Author contact information:

   E-mail: philip-fuse@shadowmagic.org.uk

*/

%{

#include <config.h>

#include <ctype.h>

#include "debugger.h"
#include "debugger_internals.h"

#include "commandy.h"

#define YY_INPUT(buf,result,max_size) \
{ \
  if( !debugger_command_input( buf, &result, max_size ) ) result = YY_NULL; \
}

%}

DIGIT	[0-9]
HEX	[0-9a-f]

%option caseless

%%

ba|bas|base { return BASE; }
br|bre|brea|break|breakp|breakpo|breakpoi|breakpoin|breakpoint { return BREAK;}
co|con|cont|contin|continu|continue { return CONTINUE; }
cond|condi|condit|conditi|conditio|condition { return CONDITION; }
cl|cle|clea|clear { return CLEAR; }
del|dele|delet|delete { return DEBUGGER_DELETE; }
di|dis|disa|disas|disass|disasse|disassm|disassmb|diasassmbl|disassemble {
	                                                  return DISASSEMBLE; }
fi|fin|fini|finis|finish { return FINISH; }
if { return IF; }
i|ig|ign|igno|ignor|ignore { return DEBUGGER_IGNORE; }
n|ne|nex|next { return NEXT; }
o|ou|out { return DEBUGGER_OUT; }	/* Different name to avoid clashing
					   with OUT from z80/z80_macros.h */
p|po|por|port { return PORT; }
r|re|rea|read { return READ; }
se|set { return SET; }
s|st|ste|step { return STEP; }
t|tb|tbr|tbre|tbrea|tbreak|tbreakp|tbreakpo|tbreakpoi|tbreakpoin|tbreakpoint {
							       return TBREAK; }
ti|tim|time { return TIME; }
w|wr|wri|writ|write { return WRITE; }

a|b|c|d|e|f|h|l { yylval.reg = debugger_register_hash( yytext );
		  return DEBUGGER_REGISTER; }

"a'"|"b'"|"c'"|"d'"|"e'"|"f'"|"h'"|"l'" {
                             yylval.reg = debugger_register_hash( yytext );
			     return DEBUGGER_REGISTER; }

af|bc|de|hl|"af\'"|"bc\'"|"de\'"|"hl\'" {
                             yylval.reg = debugger_register_hash( yytext );
			     return DEBUGGER_REGISTER; }

sp|pc|ix|iy { yylval.reg = debugger_register_hash( yytext );
	      return DEBUGGER_REGISTER; }

"("		{ return '('; }
")"		{ return ')'; }

"!"		{ yylval.token = '!'; return NEGATE; }
"~"		{ yylval.token = '~'; return NEGATE; }

 /* The hex constants used here are the appropriate Unicode characters */

"=="		{ yylval.token = DEBUGGER_TOKEN_EQUAL_TO; return EQUALITY; }
"!="		{ yylval.token = DEBUGGER_TOKEN_NOT_EQUAL_TO;
		  return EQUALITY; }

"<"		{ yylval.token = '<'; return COMPARISION; }
">"		{ yylval.token = '>'; return COMPARISION; }
"<="		{ yylval.token = DEBUGGER_TOKEN_LESS_THAN_OR_EQUAL_TO;
		  return COMPARISION; }
">="		{ yylval.token = DEBUGGER_TOKEN_GREATER_THAN_OR_EQUAL_TO;
		  return COMPARISION; }

"+"		{ return '+'; }
"-"		{ return '-'; }
"*"		{ yylval.token = '*'; return TIMES_DIVIDE; }
"/"		{ yylval.token = '/'; return TIMES_DIVIDE; }

"&"		{ return '&'; }
"^"		{ return '^'; }
"|"		{ return '|'; }

"&&"		{ return LOGICAL_AND; }
"||"		{ return LOGICAL_OR; }

":"		{ return ':'; }

${HEX}+		{ yylval.integer = strtol( yytext+1, NULL, 16 );
		  return NUMBER; }
0x{HEX}+	{ yylval.integer = strtol( yytext+2, NULL, 16 );
	          return NUMBER; }
{DIGIT}+	{ yylval.integer = atoi( yytext ); return NUMBER; }

[cdrx]{DIGIT}+	{ yylval.integer = debugger_page_hash( yytext ); return PAGE; }

[ \n]+		/* Swallow whitespace */

.		{ if( 0 ) unput( '\0' ); /* Prevent warning about yyunput
					    being defined and not used */
		  return DEBUGGER_ERROR; }