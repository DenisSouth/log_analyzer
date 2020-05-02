import matplotlib.pyplot as plt
import numpy as np

# data format: value:delay_microseconds:value:delay_microseconds:....:
data = """0:16:1:40:0:16:1:40:0:16:1:40:0:12:1:40:0:16:1:40:0:16:1:40:0:16:1:36:0:16:1:40:0:16:1:169656:0:16:1:40:0:16:1:40:0:16:1:40:0:12:1:40:0:16:1:40:0:16:1:40:0:16:1:36:0:16:1:40:0:16:1:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:
0:52:1:56:0:112:1:169892:0:52:1:56:0:56:1:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:
"""

data = data.split("\n")

s1 = data[0]
s2 = data[1]


def logic_to_signal(s):
    s = s.split(":")
    rez = []
    i = 0
    while i < len(s) - 2:
        try:
            val = int(s[i])
            lenght = int(s[i + 1])
            rez = rez + [val] * lenght

        except:
            pass
        i += 2
    return rez


plt.figure(figsize=(15, 5))
plt.plot(logic_to_signal(s1), linewidth=4)
plt.plot(np.array(logic_to_signal(s2)) * 0.95, linewidth=2)
plt.xlabel("TIme microseconds")
plt.show()
