def dict_factory():
    return { 50: 'fifty', 100: 'hundred', 10: 'ten', 11: 'eleven' }

def main():
    d = dict_factory()
    d.clear()
    print('clear', d)

    d = dict_factory().copy()
    d[1000] = 'thousand'
    print('copy', 'Origin:', dict_factory(), 'Mod copy:', d)

    d = dict_factory().fromkeys([18, 66, 33],
                                ['eighteen', 'sixty six', 'thirty three'])
    print('fromkeys', d)

    print('get', dict_factory().get(55, 'non-exist fifty five'))

    print('items', dict_factory().items())

    print('keys', dict_factory().keys())

    print('values', dict_factory().values())

    d = dict_factory()
    d.pop(100)
    print('pop(100)', d)

    item = dict_factory().popitem()
    print('popitem', item)



main()
