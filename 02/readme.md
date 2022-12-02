# Day 2

I saw [a Reddit post](https://www.reddit.com/r/adventofcode/comments/za3lqv/2022_day_1excel_is_this_the_way/) on r/adventofcode that showed someone solving Day 1 using spreadsheets. I lowkey thought that was funny as hell, so I decided to give it a go for myself the next day. I used Google Sheets, so I can't necessarily commit the original file to source, but I did include an Excel spreadsheet that I downloaded from Google Sheets.

Here's my process:

1) Replace all letters with numbers (A/X = 1, B/Y = 2, C/Z = 3)
2) Replace all spaces with commas (to make a csv - you can find the result in [`input.csv`](./input.csv).)
3) Create three columns - one for checking a tie (if the first two columns were equal, set value to 3, otherwise set to zero), and one for checking a win (6 for win, 0 otherwise), and a third column for the sum of the last three columns.
4) Get the sum, finish part one
5) Create a separate sheet for part 2, this time modifying the prior two columns to just check the second column and adding a fourth column (before the sum) for choosing what answer to pick:
   - If the second column was 1, choose the losing result (calculated via `A - 1` and setting to 3 if the result was `0`)
   - 2, copy the first column
   - 3, choose the winning result (calculated via `A % 3 + 1`)
6) Get the sum, finish part two

Overall pretty simple. Not fast, but who cares, I'm here to learn, not to speedrun the Advent of Code.
