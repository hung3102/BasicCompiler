/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#ifndef __ERROR_H__
#define __ERROR_H__
#include "token.h"

typedef enum {
  ERR_ENDOFCOMMENT,
  ERR_IDENTTOOLONG,
  ERR_INVALIDCHARCONSTANT,
  ERR_INVALIDSYMBOL,
  ERR_INVALIDNUMBER,
  ERR_INVALIDCONSTANT,
  ERR_INVALIDTYPE,
  ERR_INVALIDBASICTYPE,
  ERR_INVALIDPARAM,
  ERR_INVALIDSTATEMENT,
  ERR_INVALIDCOMPARATOR,
  ERR_INVALIDFACTOR
} ErrorCode;


#define ERM_ENDOFCOMMENT "End of comment expected!"
#define ERM_IDENTTOOLONG "Identification too long!"
#define ERM_INVALIDCHARCONSTANT "Invalid const char!"
#define ERM_INVALIDSYMBOL "Invalid symbol!"
#define ERM_INVALIDNUMBER "Invalid number!"
#define ERM_INVALIDCONSTANT "Invalid const!"
#define ERM_INVALIDTYPE "Invalid type!"
#define ERM_INVALIDBASICTYPE "Invalid type basic!"
#define ERM_INVALIDPARAM "Invalid param!"
#define ERM_INVALIDSTATEMENT "Invalid statement!"
#define ERM_INVALIDCOMPARATOR "Invalid comparator!"
#define ERM_INVALIDFACTOR "Invalid factor!"

void error(ErrorCode err, int lineNo, int colNo);
void missingToken(TokenType tokenType, int lineNo, int colNo);
void assert(char *msg);
#endif
