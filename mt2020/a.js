const fs = require('fs');

const data = fs.readFileSync('small.txt', 'utf8').split('\n');

const res = data.map(s => (/void f(\d+)\(\)\{f(\d+)\(\);f(\d+)\(\);\}/.exec(s))).map(([str, a, b, c]) => [a, b, c])

fs.writeFileSync('out.txt', res.map(s => s.join(' ')).join('\n'))
