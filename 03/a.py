key = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
total = 0

input = open('input.txt', 'r')
lines = input.readlines()

print(len(lines))

for line in lines:
    text = line[:-1]
    compartment_size = int(len(text) / 2)

    first = text[:compartment_size]
    last = text[compartment_size:]

    for char in first:
        if char in last:
            value = key.find(char) + 1
            print("{} found, with a value of {}".format(char, value))
            total += value
            break

print(total)