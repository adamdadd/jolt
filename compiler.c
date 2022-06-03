#include <stdio.h>
#include <string.h>

#include "common.h"
#include "compiler.h"
#include "scanner.h"
#include "constpool.h"

bool isCompiled(const char* source, Chunk* chunk) {
    // advance();
    // expression();
    // consume(TOKEN_EOF, "Expect end of expression");
    parse(source);
    return false;
}

void compiler(const char* source) {
    ConstPool cp;
    initScanner(source);
    initConstPool(&cp);

    int line = -1;
    for (;;) {
        Token token = scanToken();
        if (token.line  != line) {
            printf("%4d ", token.line );
            line = token.line;
        } else {
            printf("    |  ");
        }
        printf("%2d '%.*s'\n", token.type, token.length, token.start);

        if (token.type == TOKEN_EOF) {
            freeConstPool(&cp);
            break;
        }
    }
}

void parse(const char* source) {
    ConstPool cp;
    /* initScanner(source); */
    initConstPool(&cp);
    uint64_t magic = (source[0] << 24) | (source[1] << 16) | (source[2] << 8) | source[3];
    uint16_t major_version = (source[4] << 8) | source[5];
    uint16_t minor_version = (source[6] << 8) | source[7];
    printf("magic: %x\nmajor: %x\nminor: %x\n", magic, major_version, minor_version);
    uint16_t constpool_size = (source[8] << 8) | source[9];
    printf("constpool size: %d\n", constpool_size);

    int i = 10;
    do {
        switch(source[i]) {
            case 0x0a: {
                Const c;
                c.Tag = FieldAndMethod;
                c.ClassIndex = (source[i + 1] << 8) | (source[i + 2]);
                c.NameAndTypeIndex = (source[i + 3] << 8) | (source[i + 4]);
                printf("Const num: %d\n ", cp.count);
                printf("Field/Method: CI: %x\n", c.ClassIndex);
                printf("Field/Method: NTI: %x\n", c.NameAndTypeIndex);
                writeConstPool(&cp, c);
                i = i + 5;
                break;
            }
            case 0x09: {
                Const c;
                c.Tag = FieldAndMethod;
                c.ClassIndex = (source[i + 1] << 8) | (source[i + 2]);
                c.NameAndTypeIndex = (source[i + 3] << 8) | (source[i + 4]);
                printf("Const num: %d\n ", cp.count);
                printf("Field/Method: CI: %x\n", c.ClassIndex);
                printf("Field/Method: NTI: %x\n", c.NameAndTypeIndex);
                writeConstPool(&cp, c);
                i = i + 5;
                break;
            }
            case 0x0c: {
                Const c;
                c.Tag = NameAndType;
                c.NameIndex = (source[i + 1] << 8) | (source[i + 2]);
                c.DescIndex = (source[i + 3] << 8) | (source[i + 4]);
                printf("Const num: %d\n ", cp.count);
                printf("NameType: NI: %x\n", c.NameIndex);
                printf("NameType: DI: %x\n", c.DescIndex);
                writeConstPool(&cp, c);
                i = i + 5;
                break;
            }
            case 0x07: {
                Const c;
                c.Tag = NameIndex;
                c.NameIndex = (source[i  + 1] << 8) | (source[i  + 2]);
                printf("Const num: %d\n NameIndex: %x\n", cp.count, c.NameIndex);
                writeConstPool(&cp, c);
                i = i + 3;
                break;
            }
            case 0x08: {
                Const c;
                c.Tag = StringIndex;
                c.StringIndex = (source[i  + 1] << 8) | (source[i  + 2]);
                printf("Const num: %d\n StringIndex: %x\n", cp.count, c.StringIndex);
                writeConstPool(&cp, c);
                i = i + 3;
                break;
            }
            case 0x01: {
                Const c;
                c.Tag = String;
                char a[256] = "";
                uint16_t slen = (source[i + 1] << 8) | (source[i  + 2]);
                for (int j=0; j < slen + 1; j++) {
                    a[j] = source[i + 3 + j];
                }
                strcpy(c.String, a);
                printf("Const num: %d\n ", cp.count);
                printf("String: %s\n", c.String);
                writeConstPool(&cp, c);
                i = i + slen + 3;
                break;
            }
            default: {
                printf("UNKNOWN %x \n", source[i]);
                i++;
                break;
            }
        }
    } while (cp.count < constpool_size - 1);
    printf("Current index: %d with Value: %x\n", i, source[i]);

    uint16_t flags = (source[i] << 8) | source[i + 1];
    i = i + 2;

    uint16_t classname_idx = (source[i] << 8) | source[i + 1];
    printf("classname idx: %d\n", classname_idx);
    char* classname = getConstPoolString(&cp, classname_idx);
    printf("classname: %s\n", classname);
    i = i + 2;

    uint16_t supername_idx = (source[i] << 8) | source[i + 1];
    printf("supername idx: %d\n", supername_idx);
    char* supername = getConstPoolString(&cp, supername_idx);
    printf("supername: %s\n", supername);
    i = i + 2;

    uint16_t interface_count = (source[i] << 8) | source[i + 1];
    printf("interface count: %d\n", interface_count);
    i = i + 2;

    for (uint16_t j = 0; j <= interface_count; j++) {
        uint16_t idx = (source[i + j] << 8) | source[i + j + 1];
        printf("idx value: %d\n", idx);
        char *val = getConstPoolString(&cp, idx);
        printf("interface value: %s\n", val);
        i++;
    }

    freeConstPool(&cp);
}
