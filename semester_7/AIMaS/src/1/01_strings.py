def test_argumentless_funcs():
    STRANGE_STR = '       I wish I was a disco boy  '
    for f in (str.strip, str.lstrip, str.rstrip, str.capitalize, str.title):
        print(f"Function {f.__name__:<12}"
              f"Result: [{f(STRANGE_STR)}]")


def test_chararg_funcs():
    STRANGE_STR = 'Rosenrot, oh rosenrot'
    CHAR = 't'
    for f in (str.count, str.index, str.rindex, str.startswith, str.endswith,
              str.split, str.rsplit, str.partition, str.rpartition):
        print(f"Function {f.__name__:<12}"
              f"Result: [{f(STRANGE_STR, CHAR)}]")


def test_other_funcs():
    print(f"Function {'format':<12}"
          f"Result: [{'{0}, oh {0}'.format('RoSeNrOt')}]")
    print(f"Function {'replace':<12}"
          f"Result: [{'Money, Money, Money'.replace('M', 'H')}]")
    print(f"Function {'join':<12}"
          f"Result: [{' '.join(str(x) for x in range(10))}]")


def main():
    test_argumentless_funcs()
    test_chararg_funcs()
    test_other_funcs()


main()
