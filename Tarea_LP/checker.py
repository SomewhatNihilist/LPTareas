import re

Token = []

def tokenize(code):

    token_specification = [
        ('CODE_START',  r"\bHAI\b"),  
        ('CODE_END',  r"\bKTHXBYE\b"),           
        ('DECLARE',     r"\bI[ \t]+HAS[ \t]+A\b"),
        ('CONDICIONAL',r"\bO[ \t]+RLY\?\B|\bYA[ \t]+RLY\b|\bNO[ \t]+WAI\b|\bOIC\b"),
        ('INICIALIZE', r"\bITZ\b"),
        ('ASSIGN', r"\bR\b"),            
        ('BINARY',      r'\bSUM[ \t]+OF\b|\bDIFF[ \t]+OF\b|\bPRODUKT[ \t]+OF\b|\bQUOSHUNT[ \t]+OF\b|\bMOD[ \t]+OF\b|\bBIGGER[ \t]+OF\b|\bSMALLR[ \t]+OF\b|\bBOTH[ \t]+OF\b|\bEITHER[ \t]+OF\b|\bBOTH[ \t]+SAEM\b|\bDIFFRINT\b'),
        ('UNARIO', r"\bNOT\b|\bVISIBLE\b"),  
        ('AN',r"\bAN\b"),
        ('LOOP',r"\bIM[ \t]+IN[ \t]+YR\b"),
        ('LOOPOP', r"\b(NERFIN|UPPIN)[ \t]+YR\b"),
        ('VAR',      r"[A-Za-z][A-Za-z0-9_]*"),
        ('NUMBER',  r'\d+(\.\d*)?'),   
        ('NEWLINE', r'\n'),           
        ('SKIP',    r'[ \t]+'),       
        ('MISMATCH',r'.'),            
    ]
    tok_regex = '|'.join('(?P<%s>%s)' % pair for pair in token_specification)
    line_num = 1
    line_start = 0
    for mo in re.finditer(tok_regex, code):
        kind = mo.lastgroup
        value = mo.group(kind)
        if kind == 'NEWLINE':
            line_start = mo.end()
            line_num += 1
            ####
            #Token.append((kind))
        elif kind == 'SKIP':
            pass
        elif kind == 'MISMATCH':
            print(value)#raise RuntimeError(f'{value!r} unexpected on line {line_num}')
        else:
            if kind == 'ID': #and value in keywords:
                kind = value
            column = mo.start() - line_start
            Token.append((kind, value, line_num, column))




with open("check_me.txt","r") as file:
    read_data = file.read()

#[(tipo,valor,linea,columna),.....]

tokenize(read_data)

for token in Token:
    print(token)

def isCorrectBinary(string):

    checker = list(string)

    j = len(checker) - 1

    flag = True

    if (len(checker) < 4):

        return False

    while (j >= 0 and len(checker) > 4):

        if (checker[j][0] == 'BINARY'):

            try:
                if (checker[j+3][0] == "NUMBER"):
                    pass

            except IndexError:

                return False

            if ((checker[j+1][0] == 'VAR' or checker[j+1][0] == 'NUMBER') and checker[j+2][0] == 'AN' and (checker[j+3][0] == 'VAR' or checker[j+3][0] == 'NUMBER')):

                del checker[j]
                del checker[j]
                del checker[j]
                del checker[j]

                checker.insert(j,('NUMBER','27',0,0))

            else:

                return False

        j -= 1


    if (checker[0][0] == 'BINARY' and (checker[1][0] == 'VAR' or checker[1][0] == 'NUMBER') and checker[2][0] == 'AN' and (checker[3][0] == 'VAR' or checker[3][0] == 'NUMBER')):

        return True

    else:

        return False




def error_check(Token):

    end_line = 0

    error_check = []

    pos = 0

    while (pos < len(Token)):

        typ,value,line,column = Token[pos][0],Token[pos][1],Token[pos][2],Token[pos][3]

        if (typ == 'HAI'):

            if (Token[0][0] != 'HAI'):

                lista = [[Token[0]],False]
                error_check.append(lista)

            else:

                lista = [[Token[0]],True]
                error_check.append(lista)

            pos += 1

        elif (typ == 'BINARY'):

            flag = False

            for i in range(pos,len(Token)):

                if (Token[i][2] != line):

                    end_line = i - 1
                    flag = True
                    break

            if (not flag):

                end_line = len(Token) - 1

            answer = isCorrectBinary(Token[pos:end_line+1])

            print(answer)

            lista = [Token[pos:end_line+1],answer]

            error_check.append(lista)

            pos = end_line + 1

        elif (typ == 'CONDICIONAL'):

            if (typ != 'O RLY?'):

                for s in range(pos,len(Token)):

                    if (Token[s][1] == 'OIC'):

                        oic_pos = s
                        break

                lista = [Token[pos:oic_pos+1],False]
                error_check.append(lista)

                pos = oic_pos + 1 




        else:

            lista = ["GARBAGE",False]

            error_check.append(lista)

error_check(Token)
