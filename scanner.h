#ifndef jolt_scanner_h
#define jolt_scanner_h

typedef enum {
    TOKEN_LEFT_PAREN, TOKEN_RIGHT_PARAN,
    TOKEN_LEFT_BRACE, TOKEN_RIGHT_BRACE,
    TOKEN_COMMA, TOKEN_DOT, TOKEN_MINUS, TOKEN_PLUS,
    TOKEN_SEMICOLON, TOKEN_SLASH, TOKEN_STAR,
    TOKEN_BANG, TOKEN_BANG_EQUAL,
    TOKEN_EQUAL, TOKEN_EQUAL_EQUAL,
    TOKEN_GREATER, TOKEN_GREATER_EQUAL,
    TOKEN_LESS, TOKEN_LESS_EQUAL,
    TOKEN_IDENTIFIER, TOKEN_STRING, TOKEN_NUMBER,
    TOKEN_AND, TOKEN_CLASS, TOKEN_ELSE, TOKEN_FALSE,
    TOKEN_FOR, TOKEN_PUBLIC, TOKEN_STATIC, TOKEN_VOID,
    TOKEN_IF, TOKEN_NIL, TOKEN_OR, TOKEN_PRINT, TOKEN_RETURN,
    TOKEN_SUPER, TOKEN_THIS, TOKEN_TRUE, TOKEN_VAR, TOKEN_WHILE,
    TOKEN_ERROR, TOKEN_EOF,
    TOKEN_NAMEIDX, TOKEN_STRINGIDX, TOKEN_CLASSIDX, TOKEN_NAMETYPEIDX, TOKENDESCIDX,
    TOKEN_FIELDMETHOD
} TokenType;

typedef struct {
    TokenType type;
    const char* start;
    int length;
    int line;
} Token;


void initScanner(const char* source);
uint32_t parse_4bytes(char* source, int index); 
uint16_t parse_2bytes(char* source, int index); 
uint8_t parse_byte(char* source, int index); 
Token scanToken();

#endif
