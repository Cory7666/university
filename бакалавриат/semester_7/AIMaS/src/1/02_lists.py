l = [2, 4, 6, 7, 6, 8]

l.append(50)
print('append', l)

print('count', l.count(6))

l.extend(val*100 for val in range(5))
print('extend', l)

print('index', l.index(6))

l.insert(4, 67677)
print('insert', l)

l.pop(4)
print('pop(4)', l)

l.remove(6)
print('remove(6)', l)

l.reverse()
print('reverse', l)

l.sort()
print('sort', l)
