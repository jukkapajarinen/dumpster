const util = require("util");
const readline = require("readline");
const stream = readline.createInterface({ input: process.stdin, output: process.stdout });
const c = { rst: "\x1b[0m", ylw: "\x1b[33m", grn: "\x1b[32m", red: "\x1b[31m", blu: "\x1b[34m" };
const rand = max => Math.floor(Math.random() * Math.floor(max));

const treeString = input => {
  const names = input.split(", ");
  const ornaments = ['@', '', '©'];
  let treeString = `*` + names.map((name, idx) => {
    let ornament = ` ${ornaments[rand(ornaments.length)]} `;
    let wish = `${idx > 0 ? ornament : ""}Hyvää joulua ${name}!`;
    return wish;
  }).join("");
  return treeString;
};

const colorize = str => {
  let colorizedString = `${c.grn}${str}${c.rst}`;
  colorizedString = colorizedString.replaceAll("*", `${c.ylw}*${c.grn}`);
  colorizedString = colorizedString.replaceAll("@", `${c.red}@${c.grn}`);
  colorizedString = colorizedString.replaceAll("", `${c.blu}${c.grn}`);
  colorizedString = colorizedString.replaceAll("©", `${c.rst}©${c.grn}`);
  return colorizedString;
};

const christmasTree = names => {
  let treeStr = treeString(names), rows = [];
  for (let x = 0, i = 0, sum = 0, remaining = treeStr; sum <= treeStr.length && remaining.trim().length > 0; i++) {
    x = 1 + i * 2;
    sum += x;
    let padding = Math.floor((Math.floor(treeStr.length / 2) - x) / 2);
    let treeRow = (padding > 0 ? Array(padding).join(" ") : "") + remaining.slice(0, x);
    remaining = remaining.slice(x);
    rows.push(treeRow);
  }
  let [secondLast, last] = [rows[rows.length - 2], rows[rows.length - 1]];
  if (secondLast.trim().length > last.trim().length) {
    let extraPadding = Math.floor((secondLast.trim().length - last.trim().length) / 2) + 2;
    rows[rows.length - 1] = Array(extraPadding).join(" ") + last;
  }
  return colorize(`${rows.join("\n")}`);
};

stream.question(`Hi, please enter ${c.grn}names${c.rst}: `, input => {
  console.log(`\n\n${christmasTree(input)}\n\n`);
  stream.close();
});