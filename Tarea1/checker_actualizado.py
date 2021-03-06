import re

Token = []

def tokenize(code):

    temp_Token = []

    token_specification = [
        ('CODE_START',  r"\bHAI\b"),  
        ('CODE_END',  r"\bKTHXBYE\b"),           
        ('DECLARE',     r"\bI[ \t]+HAS[ \t]+A\b"),
        ('CONDICIONAL',r"\bO[ \t]+RLY\?\B|\bYA[ \t]+RLY\b|\bNO[ \t]+WAI\b|\bOIC\b"),
        ('INICIALIZE', r"\bITZ\b"),
        ('ASSIGN', r"\bR\b"),            
        ('BINARY',      r'\bSUM[ \t]+OF\b|\bDIFF[ \t]+OF\b|\bPRODUKT[ \t]+OF\b|\bQUOSHUNT[ \t]+OF\b|\bMOD[ \t]+OF\b|\bBIGGER[ \t]+OF\b|\bSMALLR[ \t]+OF\b|\bBOTH[ \t]+OF\b|\bEITHER[ \t]+OF\b|\bBOTH[ \t]+SAEM\b|\bDIFFRINT\b'),
        ('UNARIO', r"\bNOT\b|\bVISIBLE\b"),
        ('GIMMEH',r"\bGIMMEH\b"),
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
            temp_Token.append((kind, value, line_num, column))

    token_counter = 0
    error_linea = None
    end_line = 0

    while (token_counter < len(temp_Token)):

        flag_line = False

        linea = temp_Token[token_counter][2]

        for i in range(token_counter,len(temp_Token)):                

            if (temp_Token[i][2] != linea):

                end_line = i - 1
                flag_line = True
                break

        if (not flag_line):

            end_line = len(temp_Token) - 1

        Token.append([temp_Token[token_counter:end_line+1],error_linea])
        token_counter = end_line + 1






with open("check_me.txt","r") as file:
    read_data = file.read()

#[(tipo,valor,linea,columna),.....]

tokenize(read_data)

def isExpression(string):

    if (isCorrectBinary(string)):

        return True

    elif (string[0][0] == 'UNARIO' and isExpression(string[1:len(string)])):

        return True

    elif (len(string) == 1 and (string[0][0] == 'VAR' or string[0][0] == 'NUMBER')):

        return True

    elif (len(string) == 2 and string[0][0] == 'GIMMEH' and string[1][0] == 'VAR'):

        return True

    else:

        return False

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




def error_mark(Token):

    #[ [[(tipo,valor,linea,columna),...],error_linea], ... ]

    pos = 0

    while (pos < len(Token)):

        typ,value = Token[pos][0][0][0],Token[pos][0][0][1]

        if (typ == 'CODE_START'):

            if (value != 'HAI'): #Si el inicio no es HAI

                Token[pos][1] = False
                break

            else:

                if (len(Token[pos][0]) > 1): #Verifica si en la linea donde se encuentra HAI, hay mas cosas

                    Token[pos][1] = False

                else: #Si solo esta HAI alli:

                    Token[pos][1] = True

            pos += 1

        elif (typ == 'DECLARE'):

            if (not (len(Token[pos][0]) == 2 or len(Token[pos][0]) == 4)): # Verifica I HAS A num y I HAS A num ITZ 5

                Token[pos][1] = False
                pos += 1

            else:

                if (len(Token[pos][0]) == 2 and Token[pos][0][1][0] == 'VAR'): #Verifica si I HAS A num es correcto 

                    Token[pos][1] = True
                    pos += 1

                elif (Token[pos][0][1][0] == 'VAR' and Token[pos][0][2][0] == 'INICIALIZE' and Token[pos][0][3][0] == 'NUMBER'): #Verifica si I HAS A num ITZ 5 es correcto

                    Token[pos][1] = True
                    pos += 1

        elif (typ == 'BINARY'):

            answer = isCorrectBinary(Token[pos][0]) #Devuelve un booleano que dice si la linea donde se encuentra el binario es correcta
            Token[pos][1] = answer
            pos += 1

        elif (typ == 'CONDICIONAL'): #In progress...

            if (value != 'O RLY?'):

                pos += 1

            else:

                pos += 1 

        elif (typ == "MISMATCH"):

            Token[pos][1] = False
            pos += 1

        elif (typ == 'VAR'):

            if (len(Token[pos][0]) > 1):

                if (Token[pos][0][1][0] == 'ASSIGN' and isExpression(Token[pos][0][2:len(Token[pos][0])])):

                    Token[pos][1] = True
                    pos += 1

                else:

                    Token[pos][1] = False
                    pos += 1

            else:

                Token[pos][1] = False
                pos += 1

        elif (typ == 'CODE_END'):

            if (value != 'KTHXBYE'):

                Token[pos][1] = False
                pos += 1

            else:

                if (len(Token[pos][0]) > 1): #Verifica si en la linea donde se encuentra KTHXBYE, hay mas cosas

                    Token[pos][1] = False

                else: #Si solo esta KTHXBYE alli:

                    Token[pos][1] = True

            pos += 1

        else:

            #Something happens
            pos += 1



error_mark(Token)

for token in Token:
    print(token)    




