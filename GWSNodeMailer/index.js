"use strict";
const nodemailer = require("nodemailer");

const transporter = nodemailer.createTransport({
  host: "smtp.gmail.com",
  port: 465,
  secure: true,
  auth: {
    user: "you@example.com",
    pass: "ADD YOUR PASSWORD HERE",
  },
});

async function main() {
  const info = await transporter.sendMail({
    from: '"You" <you@example.com>', // sender address
    to: "someone@example.com", // list of receivers
    subject: "Nodemailer test", // Subject line
    text: "Nodemailer test", // plain text body
    html: "<b>Nodermailer test</b>", // html body
  });

  console.log("Message sent: %s", info.messageId);
}

main().catch(console.error);