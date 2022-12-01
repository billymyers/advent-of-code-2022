using System.IO;
using System.Collections.Generic;
using System.Linq;

// Variable setup
var elves = new List<int>();
elves.Add(0);

// Read input as separate lines
var input = await File.ReadAllLinesAsync(Args[0]);
WriteLine($"Read {input.Length} lines");

// Get elves count
foreach(var line in input)
{
    var success = int.TryParse(line, out var result);

    if (!success)
    {
        elves.Add(0);
        continue;
    }

    elves[^1] += result;
}

elves.Sort();
var array = elves.ToArray();
var topElves = array[^3..];

for (int i = 2; i >= 0; i--)
{
    WriteLine($"{i+1}: {topElves[i]} cals");
}

WriteLine($"Total: {topElves.Sum()} cals");