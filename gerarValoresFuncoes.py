import numpy as np
array = np.arange(0, 51, 5)
print(array)

result = []
for x in array:
    # 2x + x
    # result.append(x * 2 + x)
    # result.append(x * x + x)
    # result.append((5 - 4) * (x * x) + x)
    # result.append((2 - 4) - (4 * 3) + x )
    result.append((5 + x) + (x * x) - 3)

result = np.array(result)
print(result)

