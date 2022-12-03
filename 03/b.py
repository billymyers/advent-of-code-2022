key = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'
total = 0

input = open('input.txt', 'r')
lines = input.readlines()
lines = list(map(lambda x: x[:-1], lines))

for i in range(0,len(lines),3):
    group = lines[i:i+3]
    for char in group[0]:
        if char in group[1]:
            if char in group[2]:
                print('we found our char! it\'s {}'.format(char))
                total += key.find(char) + 1
                break

print(total)