import numpy as np
import matplotlib.pyplot as plt

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

data1 = data1[:-1]
data2 = data2[:-1]
data3 = data3[:-1]
data4 = data4[:-1]
data5 = data5[:-1]
data6 = data6[:-1]
data7 = data7[:-1]
data8 = data8[:-1]
data9 = data9[:-1]
data10 = data10[:-1]


data11 = data11[:-1]
data12 = data12[:-1]
data13 = data13[:-1]
data14 = data14[:-1]
data15 = data15[:-1]
data16 = data16[:-1]
data17 = data17[:-1]
data18 = data18[:-1]
data19 = data19[:-1]
data20 = data20[:-1]


data21 = data21[:-1]
data22 = data22[:-1]
data23 = data23[:-1]
data24 = data24[:-1]
data25 = data25[:-1]
data26 = data26[:-1]
data27 = data27[:-1]
data28 = data28[:-1]
data29 = data29[:-1]
data30 = data30[:-1]

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


y1 = map(float, [row.split(' ')[0] for row in data1])
y2 = map(float, [row.split(' ')[0] for row in data2])
y3 = map(float, [row.split(' ')[0] for row in data3])
y4 = map(float, [row.split(' ')[0] for row in data4])
y5 = map(float, [row.split(' ')[0] for row in data5])
y6 = map(float, [row.split(' ')[0] for row in data6])
y7 = map(float, [row.split(' ')[0] for row in data7])
y8 = map(float, [row.split(' ')[0] for row in data8])
y9 = map(float, [row.split(' ')[0] for row in data9])
y10 = map(float, [row.split(' ')[0] for row in data10])
y = []
y.append(max(y1))
y.append(max(y2))
y.append(max(y3))
y.append(max(y4))
y.append(max(y5))
y.append(max(y6))
y.append(max(y7))
y.append(max(y8))
y.append(max(y9))
y.append(max(y10))


y1 = map(float, [row.split(' ')[0] for row in data11])
y2 = map(float, [row.split(' ')[0] for row in data12])
y3 = map(float, [row.split(' ')[0] for row in data13])
y4 = map(float, [row.split(' ')[0] for row in data14])
y5 = map(float, [row.split(' ')[0] for row in data15])
y6 = map(float, [row.split(' ')[0] for row in data16])
y7 = map(float, [row.split(' ')[0] for row in data17])
y8 = map(float, [row.split(' ')[0] for row in data18])
y9 = map(float, [row.split(' ')[0] for row in data19])
y10 = map(float, [row.split(' ')[0] for row in data20])
z = []
z.append(max(y1))
z.append(max(y2))
z.append(max(y3))
z.append(max(y4))
z.append(max(y5))
z.append(max(y6))
z.append(max(y7))
z.append(max(y8))
z.append(max(y9))
z.append(max(y10))


y1 = map(float, [row.split(' ')[0] for row in data21])
y2 = map(float, [row.split(' ')[0] for row in data22])
y3 = map(float, [row.split(' ')[0] for row in data23])
y4 = map(float, [row.split(' ')[0] for row in data24])
y5 = map(float, [row.split(' ')[0] for row in data25])
y6 = map(float, [row.split(' ')[0] for row in data26])
y7 = map(float, [row.split(' ')[0] for row in data27])
y8 = map(float, [row.split(' ')[0] for row in data28])
y9 = map(float, [row.split(' ')[0] for row in data29])
y10 = map(float, [row.split(' ')[0] for row in data30])
w = []
w.append(max(y1))
w.append(max(y2))
w.append(max(y3))
w.append(max(y4))
w.append(max(y5))
w.append(max(y6))
w.append(max(y7))
w.append(max(y8))
w.append(max(y9))
w.append(max(y10))


x = ['4', '16', '64', '256', '1024', '4096', '16384', '65536', '262144', '524288']
fig = plt.figure()

ax1 = fig.add_subplot(111)

ax1.set_title("Throughput")
ax1.set_xlabel('Message Size')
ax1.set_ylabel('Throughput in MB/s')

ax1.plot(x,y, 'ro', x, z, 'gs', x, w, 'b^')
ax1.plot(x, y, c='r', label='pipe')
ax1.plot(x, z, c='g', label='socket')
ax1.plot(x, w, c='b', label='sharedmem')

leg = ax1.legend()
ax1.set_xscale('log', basex=2)
xlabels = ['0', '4', '16', '64', '256', '1KB', '4KB', '16KB', '64KB', '256KB', '512KB']
labels = [item.get_text() for item in ax1.get_xticklabels()]
print len(labels)
print len(xlabels)
print(labels)
print(xlabels)
print len(xlabels)
ax1.set_xticklabels(xlabels, rotation='vertical')

ax1.legend(loc=2)
plt.show()
