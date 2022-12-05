const regexp = /^move (\d+) from (\d+) to (\d+)$/m

class MoveCommand {
    Count: number;
    From: number;
    To: number;
    constructor(input: string) {
        const result = input.match(regexp);
        if (result) {
            this.Count = parseInt(result[1]);
            this.From = parseInt(result[2]) - 1;
            this.To = parseInt(result[3]) - 1;
            return;
        }

        this.Count = 0;
        this.From = 0;
        this.To = 0;
        console.log(`there was an error processing the command ${input}. please fix!`);
    }
}

// Read file
const input = await Deno.readTextFile('./input.txt').then(x => x.split('\n'));
let separator = input.findIndex(x => x.length == 1);

const crates = input.slice(0, separator);
const commands = input.slice(++separator);

// Setup our crates
// We know that we can split strings by fours
let sortedCrates = new Array(9);

for (let i = 0; i < 9; i++) {
    sortedCrates[i] = [];
}

// Sort through our crates backwards to get our crates set up properly
for (let i = crates.length - 2; i >= 0; i--) {
    const values = crates[i].match(/.{1,4}/g);
    if (!values) continue;
    for (let j = 0; j < values?.length; j++) {
        const result = values[j].match(/\w/);
        if (result) {
            sortedCrates[j].push(result[0]);
        }
    }
}

// Process commands
commands.forEach(x => {
    const pc = new MoveCommand(x);

    for (let i = 0; i < pc.Count; i++) {
        if (sortedCrates[pc.From].length == 0) break;

        sortedCrates[pc.To].push(sortedCrates[pc.From].pop());
    }
});

// Let's figure out the final crate arrangement
let result = "";
for (let i = 0; i < 9; i++) {
    result += sortedCrates[i].at(-1);
}

console.log(result);