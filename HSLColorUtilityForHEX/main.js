const fs = require("fs");
const convert = require("color-convert");

function hslColorUtilityForHex(
  inputText,
  hFactor = 0,
  sFactor = 0,
  lFactor = 0
) {
  const hexColorRegex = /#[0-9a-fA-F]{6}|#[0-9a-fA-F]{3}/g;
  const updatedText = inputText.replace(hexColorRegex, (match) => {
    const rgbColor = convert.hex.rgb(match);
    const hslColor = convert.rgb.hsl(rgbColor);
    hslColor[0] = (hslColor[0] + 360 * hFactor) % 360;
    hslColor[1] = Math.min(100, hslColor[1] + sFactor * 100);
    hslColor[2] = Math.min(100, hslColor[2] + lFactor * 100);
    const newRgbColor = convert.hsl.rgb(hslColor);
    const newHexColor = convert.rgb.hex(newRgbColor);
    return `#${newHexColor}`;
  });

  return updatedText;
}

const path = process.argv[1].replace("/main.js", "");
const buffer = fs.readFileSync(`${path}/input.json`);
const rows = buffer.toString().split("\n");
const output = rows
  .map((color) => hslColorUtilityForHex(color, 0.3, -0.1, 0.5))
  .join("\n");

fs.writeFileSync(`${path}/output.json`, output, "utf8");
