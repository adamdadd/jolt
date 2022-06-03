# Classfile Reference - Java

0xCAFEBABE = 4u
Major Version = 2u
Minor Version = 2u

## Constant Pool - unint16 (max 64k)

Pool Count = 2u

Pool count is number of uint16 (2u) values in constant pool.

Tag = 1u

Possible Tags:

0x01 - UTF8 String literal 

    String length = 2u
    data = number of bytes from string length

0x07 - NameIndex = 2u

0x08 - String Reference Index = 2u

0x09 , 0x0a - Field and Method (Represented the same, as fields) Index

    Class Index = 2u
    Name and Type Index = 2u

0x0c - Name and Type

    Name Index = 2u
    DescIndex = 2u

