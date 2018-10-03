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


def error_mark(Token):
    end_line = 0
    error_check = [] #Aqui agrego las lineas y verifico si tiene error (False) o no (True)
    #[ [lista,Bool]......... ]
    pos = 0
    while (pos < len(Token)):
        typ,value,line,column = Token[pos][0],Token[pos][1],Token[pos][2],Token[pos][3]
        if (typ == 'CODE_START'):
            if (Token[0][1] != 'HAI'): #Si el inicio no es HAI
                lista = [[Token[0]],False]
                error_check.append(lista)
                break
            else:
                for i in range(pos,len(Token)):
                    if (Token[i][2] != line):
                        end_line = i - 1
                        break
                if (len(Token[pos:end_line+1]) > 1): #Verifica si en la linea donde se encuentra HAI, hay mas cosas
                    lista = [Token[pos:end_line+1],False]
                    error_check.append(lista)
                else: #Si solo esta HAI alli:
                    lista = [[Token[0]],True]
                    error_check.append(lista)
            pos += 1
        elif (typ == 'DECLARE'):
            if (Token[pos-1][2] == line): #Verifica si I HAS A no es la primera palabra en la linea
                for i in range(pos,len(Token)):
                    if (Token[i][2] != line):
                        end_line = i - 1
                        break
                lista = [Token[pos-1:end_line+1],False]
                error_check.append(lista)
                pos = end_line + 1
            else:
                for i in range(pos,len(Token)):
                    if (Token[i][2] != line):
                        end_line = i - 1
                        break
                declare_check = Token[pos:end_line+1] #Para checkear si la estructura de I HAS A es correcta
                if (not (len(declare_check) == 2 or len(declare_check) == 4)): # Verifica I HAS A num y I HAS A num ITZ 5
                    lista = [declare_check,False]
                    error_check.append(lista)
                    pos += end_line + 1
                else:
                    if (len(declare_check) == 2 and declare_check[1][0] == 'VAR'): #Verifica si I HAS A num es correcto
                        lista = [declare_check,True]
                        error_check.append(lista)
                        pos += end_line + 1
                    elif (declare_check[1][0] == 'VAR' and declare_check[2][0] == 'INICIALIZE' and declare_check[3][0] == 'NUMBER'): #Verifica si I HAS A num ITZ 5 es correcto
                        lista = [declare_check,True]
                        error_check.append(lista)
                        pos += end_line + 1
        elif (typ == 'BINARY'):
            flag = False
            for i in range(pos,len(Token)):
                if (Token[i][2] != line):
                    end_line = i - 1
                    flag = True
                    break
            if (not flag):
                end_line = len(Token) - 1
            answer = isCorrectBinary(Token[pos:end_line+1]) #Devuelve un booleano que dice si la linea donde se encuentra el binario es correcta
            print(answer)
            lista = [Token[pos:end_line+1],answer]
            error_check.append(lista)
            pos = end_line + 1
        elif (typ == 'CONDICIONAL'): #In progress...
            if (value != 'O RLY?'):
                for s in range(pos,len(Token)):
                    if (Token[s][1] == 'OIC'):
                        oic_pos = s
                        break
                lista = [Token[pos:oic_pos+1],False]
                error_check.append(lista)
                pos = oic_pos + 1
            else:
                if (error_check[len(error_check)-1][1] == True):
                    pass
                pos += 1

        else:
            lista = ["GARBAGE",False] #In progress...
            error_check.append(lista)
            pos += 1
    print(error_check)


error_mark(Token)
