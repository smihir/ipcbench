import numpy as np
import matplotlib.pyplot as plt

with open("outputlatency/pipe_s4.txt") as f1:
    data1 = f1.read()
with open("outputlatency/pipe_s16.txt") as f2:
    data2 = f2.read()
with open("outputlatency/pipe_s64.txt") as f3:
    data3 = f3.read()
with open("outputlatency/pipe_s256.txt") as f4:
    data4 = f4.read()
with open("outputlatency/pipe_s1024.txt") as f5:
    data5 = f5.read()
with open("outputlatency/pipe_s4096.txt") as f6:
    data6 = f6.read()
with open("outputlatency/pipe_s16k.txt") as f7:
    data7 = f7.read()
with open("outputlatency/pipe_s64k.txt") as f8:
    data8 = f8.read()
with open("outputlatency/pipe_s256k.txt") as f9:
    data9 = f9.read()
with open("outputlatency/pipe_s512k.txt") as f10:
    data10 = f10.read()

with open("outputlatency/socket_s4.txt") as f1:
    data11 = f1.read()
with open("outputlatency/socket_s16.txt") as f2:
    data12 = f2.read()
with open("outputlatency/socket_s64.txt") as f3:
    data13 = f3.read()
with open("outputlatency/socket_s256.txt") as f4:
    data14 = f4.read()
with open("outputlatency/socket_s1024.txt") as f5:
    data15 = f5.read()
with open("outputlatency/socket_s4096.txt") as f6:
    data16 = f6.read()
with open("outputlatency/socket_s16k.txt") as f7:
    data17 = f7.read()
with open("outputlatency/socket_s64k.txt") as f8:
    data18 = f8.read()
with open("outputlatency/socket_s256k.txt") as f9:
    data19 = f9.read()
with open("outputlatency/socket_s512k.txt") as f10:
    data20 = f10.read()


with open("outputlatency/smemipc_s4.txt") as f1:
    data21 = f1.read()
with open("outputlatency/smemipc_s16.txt") as f2:
    data22 = f2.read()
with open("outputlatency/smemipc_s64.txt") as f3:
    data23 = f3.read()
with open("outputlatency/smemipc_s256.txt") as f4:
    data24 = f4.read()
with open("outputlatency/smemipc_s1024.txt") as f5:
    data25 = f5.read()
with open("outputlatency/smemipc_s4096.txt") as f6:
    data26 = f6.read()
with open("outputlatency/smemipc_s16k.txt") as f7:
    data27 = f7.read()
with open("outputlatency/smemipc_s64k.txt") as f8:
    data28 = f8.read()
with open("outputlatency/smemipc_s256k.txt") as f9:
    data29 = f9.read()
with open("outputlatency/smemipc_s512k.txt") as f10:
    data30 = f10.read()


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
'''
y = [x / 1000 for x in y]

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
z.append(min(y1))
z.append(min(y2))
z.append(min(y3))
z.append(min(y4))
z.append(min(y5))
z.append(min(y6))
z.append(min(y7))
z.append(min(y8))
z.append(min(y9))
z.append(min(y10))
'''
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
z = [x / 1000 for x in z]

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
w.append(min(y1))
w.append(min(y2))
w.append(min(y3))
w.append(min(y4))
w.append(min(y5))
w.append(min(y6))
w.append(min(y7))
w.append(min(y8))
w.append(min(y9))
w.append(min(y10))
'''
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

xlabels = ['0', '4', '16', '64', '256', '1KB', '4KB', '16KB', '64KB', '256KB', '512KB']

w = [x / 1000 for x in w]

x = ['4', '16', '64', '256', '1024', '4096', '16384', '65536', '262144', '524288']
x1 = ['4', '16', '64', '256', '1024', '4096', '16384']
x2 = ['65536', '262144', '524288']
fig2 = plt.figure()

ax2 = fig2.add_subplot(111)

ax2.set_title("Latency")
ax2.set_xlabel('Message Size')
ax2.set_ylabel('Latency in us')
y2=y[7:10]
z2=z[7:10]
w2=w[7:10]
ax2.plot(x2,y2, 'ro', x2, z2, 'gs', x2, w2, 'b^')
#ax1.plot(x,w, 'gs')

ax2.plot(x2, y2, c='r', label='pipe')
ax2.plot(x2, z2, c='g', label='socket')
ax2.plot(x2, w2, c='b', label='sharedmem')
leg = ax2.legend()
ax2.set_xscale('log', basex=2)
ax2.legend(loc=2)
##################################################
fig3 = plt.figure()
ax3 = fig3.add_subplot(111)

ax3.set_title("Latency")
ax3.set_xlabel('Message Size')
ax3.set_ylabel('Latency in us')

ax3.plot(x,y, 'ro', x, z, 'gs', x, w, 'b^')
#ax1.plot(x,w, 'gs')

ax3.plot(x, y, c='r', label='pipe')
ax3.plot(x, z, c='g', label='socket')
ax3.plot(x, w, c='b', label='sharedmem')
leg = ax3.legend()
ax3.set_xscale('log', basex=2)
ax3.legend(loc=2)

##################################################
fig1 = plt.figure()

ax1 = fig1.add_subplot(111)

ax1.set_title("Latency")
ax1.set_xlabel('Message Size')
ax1.set_ylabel('Latency in us')
y1=y[0:7]
z1=z[0:7]
w1=w[0:7]
ax1.plot(x1,y1, 'ro', x1, z1, 'gs', x1, w1, 'b^')

ax1.plot(x1, y1, c='r', label='pipe')
ax1.plot(x1, z1, c='g', label='socket')
ax1.plot(x1, w1, c='b', label='sharedmem')
leg = ax1.legend()
ax1.set_xscale('log', basex=2)
ax1.legend(loc=2)

my_xticks = ['4', '16', '64', '256', '1024', '4096', '16384']
#plt.xticks(x1, my_xticks)

#ax1.set_xticklabels(xlabels, rotation='vertical')
ax2.set_xticklabels(xlabels, rotation='vertical')
ax3.set_xticklabels(xlabels, rotation='vertical')
#plt.xticks(np.arange(int(min(x1)), int(max(x1))+1, 1.0))
plt.tick_params(axis='both', which='major', labelsize=14)

##############################################

#x_bar = [4, 16, 64, 256, 1024, 4096, 16384, 65536, 262144, 524288]
#BAR GRAPH
x_bar=np.arange(10)

fig4 = plt.figure()
ax4 = fig4.add_subplot(111)
ax4.set_title("Latency")
ax4.set_xlabel('Message Size')
ax4.set_ylabel('Latency in logarithmic scale of us')
wd = 0.15
#width = [0.35, 0.35, 0.35, 0.35, 0.35, 0.35, 0.35, 0.35, 0.35, 0.35]
y = [float(x) for x in y]
z = [float(x) for x in z]
w = [float(x) for x in w]

rects1 = ax4.bar(x_bar, y, wd, color='r')
rects2 = ax4.bar(x_bar+wd, z, wd, color='g')
rects3 = ax4.bar(x_bar+wd+wd, w, wd, color='b')

xlabels2 = ['4', '16', '64', '256', '1KB', '4KB', '16KB', '64KB', '256KB', '512KB']
plt.xticks(x_bar + wd/2., xlabels)

ax4.set_xticklabels(xlabels2, rotation='vertical')
ax4.set_yscale('log', basex=2)
ax4.legend((rects1[0], rects2[0], rects3[0]), ('Pipe', 'Socket', 'Sharedmem'), loc = 'upper left')


##############################################
plt.show()
