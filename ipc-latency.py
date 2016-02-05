import numpy as np
import matplotlib.pyplot as plt
'''
with open("output/pipe_s4.txt") as f1:
    data1 = f1.read()
with open("output/pipe_s16.txt") as f2:
    data2 = f2.read()
with open("output/pipe_s64.txt") as f3:
    data3 = f3.read()
with open("output/pipe_s256.txt") as f4:
    data4 = f4.read()
with open("output/pipe_s1024.txt") as f5:
    data5 = f5.read()
with open("output/pipe_s4096.txt") as f6:
    data6 = f6.read()
with open("output/pipe_s16k.txt") as f7:
    data7 = f7.read()
with open("output/pipe_s64k.txt") as f8:
    data8 = f8.read()
with open("output/pipe_s256k.txt") as f9:
    data9 = f9.read()
with open("output/pipe_s512k.txt") as f10:
    data10 = f10.read()

with open("output/socket_s4.txt") as f1:
    data11 = f1.read()
with open("output/socket_s16.txt") as f2:
    data12 = f2.read()
with open("output/socket_s64.txt") as f3:
    data13 = f3.read()
with open("output/socket_s256.txt") as f4:
    data14 = f4.read()
with open("output/socket_s1024.txt") as f5:
    data15 = f5.read()
with open("output/socket_s4096.txt") as f6:
    data16 = f6.read()
with open("output/socket_s16k.txt") as f7:
    data17 = f7.read()
with open("output/socket_s64k.txt") as f8:
    data18 = f8.read()
with open("output/socket_s256k.txt") as f9:
    data19 = f9.read()
with open("output/socket_s512k.txt") as f10:
    data20 = f10.read()

'''
with open("output/smemipc_s4.txt") as f1:
    data21 = f1.read()
with open("output/smemipc_s16.txt") as f2:
    data22 = f2.read()
with open("output/smemipc_s64.txt") as f3:
    data23 = f3.read()
with open("output/smemipc_s256.txt") as f4:
    data24 = f4.read()
with open("output/smemipc_s1024.txt") as f5:
    data25 = f5.read()
with open("output/smemipc_s4096.txt") as f6:
    data26 = f6.read()
with open("output/smemipc_s16k.txt") as f7:
    data27 = f7.read()
with open("output/smemipc_s64k.txt") as f8:
    data28 = f8.read()
with open("output/smemipc_s256k.txt") as f9:
    data29 = f9.read()
with open("output/smemipc_s512k.txt") as f10:
    data30 = f10.read()

'''
data1 = data1.split('\n')
data2 = data2.split('\n')
data3 = data3.split('\n')
data4 = data4.split('\n')
data5 = data5.split('\n')
data6 = data6.split('\n')
data7 = data7.split('\n')
data8 = data8.split('\n')
data9 = data9.split('\n')
data10 = data10.split('\n')

data11 = data11.split('\n')
data12 = data12.split('\n')
data13 = data13.split('\n')
data14 = data14.split('\n')
data15 = data15.split('\n')
data16 = data16.split('\n')
data17 = data17.split('\n')
data18 = data18.split('\n')
data19 = data19.split('\n')
data20 = data20.split('\n')
'''
data21 = data21.split('\n')
data22 = data22.split('\n')
data23 = data23.split('\n')
data24 = data24.split('\n')
data25 = data25.split('\n')
data26 = data26.split('\n')
data27 = data27.split('\n')
data28 = data28.split('\n')
data29 = data29.split('\n')
data30 = data30.split('\n')

'''
y1 = map(int, [row.split(' ')[0] for row in data1])
y2 = map(int, [row.split(' ')[0] for row in data2])
y3 = map(int, [row.split(' ')[0] for row in data3])
y4 = map(int, [row.split(' ')[0] for row in data4])
y5 = map(int, [row.split(' ')[0] for row in data5])
y6 = map(int, [row.split(' ')[0] for row in data6])
y7 = map(int, [row.split(' ')[0] for row in data7])
y8 = map(int, [row.split(' ')[0] for row in data8])
y9 = map(int, [row.split(' ')[0] for row in data9])
y10 = map(int, [row.split(' ')[0] for row in data10])
y = []
y.append(sum((y1))/len(y1))
y.append(sum((y2))/len(y2))
y.append(sum((y3))/len(y3))
y.append(sum((y4))/len(y4))
y.append(sum((y5))/len(y5))
y.append(sum((y6))/len(y6))
y.append(sum((y7))/len(y7))
y.append(sum((y8))/len(y8))
y.append(sum((y9))/len(y9))
y.append(sum((y10))/len(y10))

y1 = map(int, [row.split(' ')[0] for row in data11])
y2 = map(int, [row.split(' ')[0] for row in data12])
y3 = map(int, [row.split(' ')[0] for row in data13])
y4 = map(int, [row.split(' ')[0] for row in data14])
y5 = map(int, [row.split(' ')[0] for row in data15])
y6 = map(int, [row.split(' ')[0] for row in data16])
y7 = map(int, [row.split(' ')[0] for row in data17])
y8 = map(int, [row.split(' ')[0] for row in data18])
y9 = map(int, [row.split(' ')[0] for row in data19])
y10 = map(int, [row.split(' ')[0] for row in data20])
z = []
z.append(sum((y1))/len(y1))
z.append(sum((y2))/len(y2))
z.append(sum((y3))/len(y3))
z.append(sum((y4))/len(y4))
z.append(sum((y5))/len(y5))
z.append(sum((y6))/len(y6))
z.append(sum((y7))/len(y7))
z.append(sum((y8))/len(y8))
z.append(sum((y9))/len(y9))
z.append(sum((y10))/len(y10))
'''

y1 = map(int, [row.split(' ')[0] for row in data21])
y2 = map(int, [row.split(' ')[0] for row in data22])
y3 = map(int, [row.split(' ')[0] for row in data23])
y4 = map(int, [row.split(' ')[0] for row in data24])
y5 = map(int, [row.split(' ')[0] for row in data25])
y6 = map(int, [row.split(' ')[0] for row in data26])
y7 = map(int, [row.split(' ')[0] for row in data27])
y8 = map(int, [row.split(' ')[0] for row in data28])
y9 = map(int, [row.split(' ')[0] for row in data29])
y10 = map(int, [row.split(' ')[0] for row in data30])
w = []
w.append(sum((y1))/len(y1))
w.append(sum((y2))/len(y2))
w.append(sum((y3))/len(y3))
w.append(sum((y4))/len(y4))
w.append(sum((y5))/len(y5))
w.append(sum((y6))/len(y6))
w.append(sum((y7))/len(y7))
w.append(sum((y8))/len(y8))
w.append(sum((y9))/len(y9))
w.append(sum((y10))/len(y10))

'''
y.append(min(y1))
y.append(min(y2))
y.append(min(y3))
y.append(min(y4))
y.append(min(y5))
y.append(min(y6))
y.append(min(y7))
y.append(min(y8))
y.append(min(y9))
y.append(min(y10))
'''
x = ['4', '16', '64', '256', '1024', '4096', '16384', '65536', '262144', '524288']
fig = plt.figure()

ax1 = fig.add_subplot(111)

ax1.set_title("Throughput")
ax1.set_xlabel('Size of message')
ax1.set_ylabel('Throughput in ns')

#ax1.plot(x,y, 'r--', x, z, 'bs', x, w, 'g^')
ax1.plot(x,w, 'gs')
ax1.plot(x, w, c='r', label='sharedmem')
#ax1.plot(x, z, c='g', label='socket')
#ax1.plot(x, w, c='b', label='sharedmem')

print(x)
#print(y)
#print(z)
#print(w)

leg = ax1.legend()
ax1.set_xscale('log', basex=2)
plt.show()