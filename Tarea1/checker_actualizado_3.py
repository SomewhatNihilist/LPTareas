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


def error_mark(Token):

    #[ [[(tipo,valor,linea,columna),...],error_linea], ... ]

    pos = 0

    dont_check_me = []

    while (pos < len(Token)):

        typ,value = Token[pos][0][0][0],Token[pos][0][0][1]

        if (typ == 'CODE_START'):

            if (value != 'HAI'): #Si el inicio no es HAI

                Token[pos][1] = False

            else:

                if (len(Token[pos][0]) > 1): #Verifica si en la linea donde se encuentra HAI, hay mas cosas

                    Token[pos][1] = False

                else: #Si solo esta HAI alli:

                    Token[pos][1] = True

        elif (typ == 'DECLARE'):

            if (len(Token[pos][0]) == 1): # Verifica I HAS A num y I HAS A num ITZ 5

                Token[pos][1] = False

            else:

                if (len(Token[pos][0]) == 2 and Token[pos][0][1][0] == 'VAR'): #Verifica si I HAS A num es correcto

                    Token[pos][1] = True

                elif (Token[pos][0][1][0] == 'VAR' and Token[pos][0][2][0] == 'INICIALIZE' and isExpression(Token[pos][0][3:len(Token[pos][0])])): #Verifica si I HAS A num ITZ 5 es correcto

                    Token[pos][1] = True

        elif (typ == 'UNARIO'):

            answer = isExpression(Token[pos][0])

            Token[pos][1] = answer

        elif (typ == 'BINARY'):

            answer = isCorrectBinary(Token[pos][0]) #Devuelve un booleano que dice si la linea donde se encuentra el binario es correcta
            Token[pos][1] = answer

        elif (typ == 'CONDICIONAL'):

            correct_structure = []

            try:
                if (isExpression(Token[pos-1][0])):

                    for i in range(pos,len(Token)):

                        if (Token[i][0][0][0] == 'CONDICIONAL'and len(Token[i][0]) == 1):

                            correct_structure.append((Token[i][0][0][1],i))

                    if (len(correct_structure) == 4):

                        if (correct_structure[0][0] == "O RLY?" and correct_structure[1][0] == "YA RLY" and correct_structure[2][0] == "NO WAI" and correct_structure[3][0] == "OIC"):

                            for _,i in correct_structure:

                                Token[i][1] = True
                                dont_check_me.append(i)

                        else:

                            Token[pos][1] = False

                else:

                    Token[pos][1] == False

            except IndexError:

                Token[pos][1] = False

        elif (typ == "MISMATCH"):

            Token[pos][1] = False

        elif (typ == 'VAR'):

            if (len(Token[pos][0]) > 1):

                if (Token[pos][0][1][0] == 'ASSIGN' and isExpression(Token[pos][0][2:len(Token[pos][0])])):

                    Token[pos][1] = True

                else:

                    Token[pos][1] = False

            else:

                Token[pos][1] = False

        elif (typ == 'CODE_END'):

            if (value != 'KTHXBYE'):

                Token[pos][1] = False

            else:

                if (len(Token[pos][0]) > 1): #Verifica si en la linea donde se encuentra KTHXBYE, hay mas cosas

                    Token[pos][1] = False

                else: #Si solo esta KTHXBYE alli:

                    Token[pos][1] = True

        else:
            pass

        if ((pos+1) in dont_check_me):

            pos += 2

        else:

            pos += 1



error_mark(Token)

for token in Token:
    print(token)



colors = {# NOTE: Remember to close the coloring with clear
          "blue":  "\033[34m", #Operadores (incluye ’AN’)
          "cyan":  "\033[36m", #Condicionales
          "purple":"\033[35m", #Loops
          "green": "\033[32m", #HAI y KTHXBYE
          "yellow":"\033[33m", #Declaracin e inicializacion de variables
          "red":   "\033[31m", #Asignacion de variables, Entrada y Salida de datos
          "error": "\033[30m\033[41m", #Error
          "clear": "\033[0m",
}
type_color ={
            'CODE_START':   colors["green"],
            'CODE_END':     colors["green"],
            'DECLARE':      colors["yellow"],
            'CONDICIONAL':  colors["cyan"],
            'INICIALIZE':   colors["yellow"],
            'ASSIGN':       colors["red"],
            'BINARY':       colors["blue"],
            'NOT':       colors["blue"], #'UNARIO', r"\bNOT\b|\bVISIBLE\b"
            'VISIBLE':       colors["red"],
            'GIMMEH':       colors["red"],
            'AN':           colors["blue"],
            'LOOP':         colors["purple"],
            'LOOPOP':       colors["purple"],
}
# COLOR TEST
# cols = ("blue","cyan","purple","green","yellow","red","error","clear")
# print(" ".join(["{0}{1}".format(Colors[i], i) for i in cols]))


def print_colorize(filename, t_data):
    # t_data = [
    #   [ [(tipo,valor,linea= n,columna), ...], error linea],
    #   [ [(tipo,valor,linea= n+1 ,columna), ...], error linea?], ...lineas...]

    curr_line = 1
    curr_data = 0
    with open(filename, "r") as file:
        for line in file:
            line = line.rstrip("\n")
            if curr_line == t_data[curr_data][0][0][2]:
                if not t_data[curr_data][1]: # if line has error
                    line = colors["error"] + line + colors["clear"]
                else:
                    diff = 0
                    for type, val, l, c in t_data[curr_data][0]:
                        if type == "UNARIO": type = val
                        clr = type_color.get(type, "")
                        added = clr + val + colors["clear"]
                        print(">" + line[:c+diff] + line[c+len(added)+diff:])
                        line = line[:c+diff] + added + line[c+len(added)+diff:]
                        diff += len(added)
                curr_data += 1
            elif curr_line > t_data[curr_data][0][0][2]: pass
            else: pass
            print(line)
            curr_line += 1

print_colorize("check_me.txt", Token)
