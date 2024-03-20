strs = sorted([method for method in dir(str) if not method.startswith('__')],
              key=lambda method: len(method))[:5]
new_strs = [s.lower() for s in strs if len(s) >= 5]

print(strs)
print(new_strs)
