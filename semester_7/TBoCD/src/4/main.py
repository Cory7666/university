import refmap
import matrixops

def _symbol2V(symbol: str):
    table = {
        'a': 0, # Фрагмент
        'b': 1, # Тело программы
        'c': 2, # Оператор
        'd': 3, # Выражение
        'e': 4, # Операнд
        'f': 5, # Знак
        'g': 6, # STA
        'h': 7, # STO
        'i': 8, # iden
        'j': 9, # data
        'k': 10, # :=
        'l': 11, # +
        'm': 12, # -
        'n': 13, # *
        'o': 14, # /
        '#': 15, # Заглушка
    }
    return table[symbol]

def _V2symbol(v: int):
    table = {
        0: 'a',
        1: 'b',
        2: 'c',
        3: 'd',
        4: 'e',
        5: 'f',
        6: 'g',
        7: 'h',
        8: 'i',
        9: 'j',
        10: 'k',
        11: 'l',
        12: 'm',
        13: 'n',
        14: 'o',
        15: '#',
    }
    return table[v]

def _create_new_seq(stack: list, stack_headers: list, first: str):
    stack.append('#')
    stack_headers.append(len(stack))
    stack.append(first)

def _trim_stack_to_len(stack: list, l: int):
    while l < len(stack) and len(stack) > 0:
        stack.pop()

print(refmap.to_string())

eq, f, l = refmap.to_three_tables()
print(matrixops.to_string(eq, 'EQUIVALENCE'))
print(matrixops.to_string(f, 'FIRST'))
print(matrixops.to_string(l, 'LAST'))

f_plus, l_plus = (matrixops.make_plus_matrix(m) for m in [f, l])
print(matrixops.to_string(f_plus, 'FIRST+'))
print(matrixops.to_string(l_plus, 'LAST+'))

lt_dot = matrixops.make_lt_dot_rel_matrix(eq, f)
print(matrixops.to_string(lt_dot, '<·'))
dot_gt = matrixops.make_dot_gt_rel_matrix(eq, f, l)
print(matrixops.to_string(dot_gt, '·>'))

result = matrixops.make_gramar(eq, lt_dot, dot_gt)
print(matrixops.gramar_to_string(result))

@refmap.fork
def check_stream(stream: str, gram: matrixops.GramarMatrix):
    stack = ['#']
    seq_headers = [1]

    gram.append(['>'] * len(gram))
    for (idx, row) in enumerate(gram):
        row.append('#' if idx in (0, len(gram) - 1) else '=')
    print(matrixops.gramar_to_string(gram))
    for symbol in stream:
        rel_code = gram[_symbol2V(stack[-1])][_symbol2V(symbol)]
        if '=' == rel_code:
            stack.append(symbol)
        elif '<' == rel_code:
            _create_new_seq(stack, seq_headers, symbol)
        elif '>' == rel_code:
            h = seq_headers.pop()
            nonterminal = refmap._decide_nonterminal(stack[h], stack[-1])
            _trim_stack_to_len(stack, h)
            if gram[_symbol2V(stack[-1])][_symbol2V(nonterminal)] == '<':
                stack.append(nonterminal)
            else:
                _trim_stack_to_len(stack, h-1)
                stack.append(nonterminal)
        elif '#' == rel_code:
            print('OK')
        else:
            print('ERROR!')
            break
    return result := ''


test_cases = {
    'gikjh': 'Верная программа с одним простым оператором',
    'gikjfjoih': 'Верная программа с одним составным оператором',
    'gjkjfjoih': 'То же, что и в предыдущем, но вместо идентификатора задано число',
    'gikjjoih': 'То же, что и во втором, но пропущен знак'
}

counter = 0
for (stream, desc) in test_cases.items():
    counter += 1
    check_result = check_stream(stream, result)
    print(f"""\
{counter}) {desc}
    Вход: {stream}
    Результат: {check_result}\
""")
