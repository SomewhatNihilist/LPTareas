#From https://docs.python.org/3.6/library/re.html#writing-a-tokenizer

import re


def tokenize(code):
    binarios = (
        r'SUM[ \t]+OF', r'DIFF[ \t]+OF', r'PRODUKT[ \t]+OF', r'QUOSHUNT[ \t]+OF',
        r'MOD[ \t]+OF', r'BIGGR[ \t]+OF', r'SMALLR[ \t]+OF', r'BOTH[ \t]+OF',
        r'EITHER[ \t]+OF', r'BOTH[ \t]+SAEM', r'DIFFRINT'
    )
    # r'\bO[ \t]+RLY\?\B'
    token_specification = [
        ('CODESTART',   r'\bHAI\b'),          # LOLCODE BEGIN CODE
        ('CODESTOP',    r'\bKTHXBYE\b'),      # LOLCODE END CODE
        ('VAR_DECLARE', r'\bI[ \t]+HAS[ \t]+A\b'),
        ('VAR_INIT'     r'\bITZ\b'),      #
        ('ASSIGN',      r'\bR\b'),        # Assignment operator
        ('NUMBER',      r'\d+(\.\d*)?'),  # Integer or decimal number
        ('STRING',      r'"[^\n]*"'),
        ('ID',          r'[A-Za-z][A-Za-z0-9_]*'),    # Identifiers
        ('BINARY',      r'|'.join('\\b{0}\\b'.format(a) for a in binarios)),
        ('UNARY',       r'')
        ('NEWLINE',     r'\n'),           # Line endings
        ('IGNORE',      r'[ \t]+'),       # Skip over spaces and tabs
        ('MISMATCH',    r'.'),            # Any other character
    ]
    tok_regex = '|'.join('(?P<{0}>{1})'.format(*pair) for pair in token_specification)
    line_num = 1
    line_start = 0
    for mo in re.finditer(tok_regex, code):
        kind = mo.lastgroup
        value = mo.group(kind)
        if kind == 'NEWLINE':
            line_start = mo.end()
            line_num += 1
        elif kind == 'SKIP':
            pass
        elif kind == 'MISMATCH':
            pass#raise RuntimeError(f'{value!r} unexpected on line {line_num}')
        else:
            column = mo.start() - line_start
            yield (kind, value, line_num, column, mo.start())


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


tokens = []

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
                    line = colors["error"] + line+ colors["clear"]
                else:
                    diff = 0
                    for type, val, l, c in t_data[curr_data][0]:
                        if type == "UNARIO": type = val
                        clr = type_color.get(type, False)
                        if clr:
                            length = len(clr + colors["clear"])
                            line = line[c+diff:] + clr + val + colors["clear"] + line[:length+len(val)+diff]
                            diff += length
                curr_data++
            elif curr_line > t_data[curr_data][0][0][2]: pass
            else: pass
            print(line)
            curr_line++


with open("file.txt", "r") as ins:
    array = []
    for line in ins:
        array.append(line)
statements = ""
for token in tokenize(statements):
    print(token)
