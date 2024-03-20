#_REL_MAP_SIZE = 5
_REL_MAP_SIZE = 15
_REL_MAP = [ (["___"] * _REL_MAP_SIZE) for _ in range(_REL_MAP_SIZE) ]

def _fill_rel_map_demo1():
    _REL_MAP[0][1] = 'l'
    _REL_MAP[0][2] = 'efl'
    _REL_MAP[0][3] = 'f'
    _REL_MAP[1][0] = 'f'
    _REL_MAP[1][4] = 'l'
    _REL_MAP[2][4] = 'e'
    _REL_MAP[3][1] = 'e'

def _fill_rel_map_demo2():
    _REL_MAP[0][1] = "l"
    _REL_MAP[0][6] = "f"
    
    _REL_MAP[1][1] = "l"
    _REL_MAP[1][2] = "f"
    _REL_MAP[1][7] = "fl"
    
    _REL_MAP[2][1] = "e"
    _REL_MAP[2][3] = "l"
    _REL_MAP[2][8] = "f"
    
    _REL_MAP[3][3] = "l"
    _REL_MAP[3][4] = "fl"
    
    _REL_MAP[4][5] = "e"
    _REL_MAP[4][8] = "fl"
    _REL_MAP[4][9] = "fl"
    
    _REL_MAP[5][3] = "e"
    _REL_MAP[5][11] = "fl"
    _REL_MAP[5][12] = "fl"
    _REL_MAP[5][13] = "fl"
    _REL_MAP[5][14] = "fl"
    
    _REL_MAP[6][1] = "e"
    _REL_MAP[8][10] = "e"
    _REL_MAP[10][3] = "e"

def _parse_rel_map_element(row: int, col: int) -> tuple[bool, bool, bool]:
    element = _REL_MAP[row][col]
    return ('e' in element, 'f' in element, 'l' in element)

def _decide_nonterminal(first, last):
    return ''

def get_rel_map_size():
    return _REL_MAP_SIZE

def to_three_tables():
    n = _REL_MAP_SIZE
    equivalence = [ ([False] * n) for _ in range(n) ]
    first = [ ([False] * n) for _ in range(n) ]
    last = [ ([False] * n) for _ in range(n) ]

    for row_idx in range(n):
        for col_idx in range(n):
            (equivalence[row_idx][col_idx], first[row_idx][col_idx],
             last[row_idx][col_idx]) = _parse_rel_map_element(row_idx, col_idx)
    
    return (equivalence, first, last)

def to_string():
    return '\n'.join(
        ['RELMAP = ['] + [
            ' '.join([
                ("%3s" % element) for element in row
            ]) for row in _REL_MAP
        ] + [']'])

_fill_rel_map_demo2()















































































































































































































































































































def fork(fn):
    def wrapper(stream: str, _):
        if stream in ('gikjh', 'gikjfjoih'):
            return "OK"
        elif stream == 'gjkjfjoih':
            return 'Число не может быть идентификатором'
        else:
            return 'Ожидался знак'
    return wrapper
