let greet: (a: string, b: string) => void;
greet = (name: string, greeting: string) => {
  console.log(`${name} says hello ${greeting}`);
}

let calc: (a: number, b: number, c: string) => number;
calc = (numOne: number, numTwo: number, action: string) => {
  if (action === "add") {
    return numOne + numTwo;
  }
  else {
    return numOne - numTwo;
  }
}

let logDetails: (obj: {name: string, age: number}) => void;
type person = {name: string, age: number};
logDetails = (ninja: person) => {
  console.log(`${ninja.name} is ${ninja.age} years old`);
}