with open('rpq.data', 'r') as infile:
    data = infile.read()
my_list = data.splitlines()

l = my_list.index('data.1')
N = int(my_list[l + 1])

data_blocks = []

for item in my_list[l + 2:l + 2 + N]:
    nums = [int(n) for n in item.split()]
    data_blocks.append(nums)
print(data_blocks)

