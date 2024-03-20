class RecursiveParsingAlgo:
    def __init__(self, chars: str) -> None:
        self._chars = chars
        self._offset = 0

    def nonterm(self, expect: str) -> bool:
        nonterminals = {
            'S': lambda _: self.term('a') and self.term('e') \
                and self.nonterm('B') and self.term('f') \
                    and self.term('b') and self.term('d') \
                        and self.term('e') and self.nonterm('A'),
            'A': lambda start: (self.term('f') and self.term('g')) \
                if (start == 'f') else (self.nonterm('B') \
                    and self.term('g') and self.nonterm('A')),
            'B': lambda _: self.term('c') and self.term('h') \
                and self.nonterm('C'),
            'C': lambda _: self.nonterm('D') \
                and self.optional(lambda: self.nonterm('E'),
                                  lambda: self.nonterm('E') \
                                    and self.nonterm('D')),
            'D': lambda start: self.term('c') if (start == 'c') \
                else self.term('d'),
            'E': lambda start: self.term('i') if (start == 'i') \
                else self.term('j'),
        }

        return nonterminals\
            .get(expect, lambda _: False)(self._chars[self._offset])

    def optional(self, expect_fn, consumer_fn) -> bool:
        ret = True
        old_offset = self._offset
        while expect_fn():
            self._offset = old_offset
            ret = ret and consumer_fn()
            old_offset = self._offset
        self._offset = old_offset
        return ret

    def term(self, expect: str) -> bool:
        ret = (self._offset < len(self._chars)) \
            and (expect == self._chars[self._offset])
        self._offset += 1
        return ret

    def process(self) -> bool:
        return self.nonterm('S')

def main():
    test_cases = {
        'aechdfbdechcidgchcjdidgfg': 'Правильно построенный цикл с двумя операторами в теле',
        'aechdidfbdefg': 'Правильно построенный цикл с пустым телом',
        'aedhdidfbdefg': 'Цикл с ошибкой в операторе (число вместо идентификатора)',
    }

    counter = 1
    for (program, desc) in test_cases.items():
        print(f"""\
{counter}) {desc}
    Программа: {program}
    Результат: {'OK' if RecursiveParsingAlgo(program).process() else 'ERROR'}\
""")
        counter += 1

main()
