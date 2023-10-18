import matplotlib.pyplot as plt

data_fifo = []
# read the contents in FIFO.txt
with open('FIFO.txt', 'r') as f:
    data = f.readlines()
    data_fifo = [float(line.strip()) for line in data]
data_other = []
# read the contents in OTHER.txt
with open('OTHER.txt', 'r') as f:
    data = f.readlines()
    data_other = [float(line.strip()) for line in data]
data_RR =[]
# read the contents in RR.txt
with open('RR.txt', 'r') as f:
    data = f.readlines()
    data_RR = [float(line.strip()) for line in data]

fifo_avg = sum(data_fifo)/len(data_fifo)
other_avg = sum(data_other)/len(data_other)
RR_avg = sum(data_RR)/len(data_RR)

# plot the bar graph. X-axis will show different scheduling policies(FIFO, OTHER, RR)
# Y-axis will show the time

plt.bar(['FIFO', 'OTHER', 'RR'], [fifo_avg, other_avg, RR_avg])
plt.xlabel('Scheduling Policy')
plt.ylabel('Time')
plt.title('Average Time for Different Scheduling Policies')
plt.savefig("histogram.png")

