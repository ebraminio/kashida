var fs = require('fs');
var { spawnSync } = require('child_process');

var i = 0;
function kashida(text) {
  i++;
  if (i % 1000 === 0) {
    console.log('Reached to ' + i);
  }
  return spawnSync(
    'kashida.exe',
    ['C:\\Windows\\Fonts\\tahoma.ttf', '20000'].concat(text.split('').map(x => x.charCodeAt(0)))
  ).stdout.toString().trim().split('\n').map(x => x.split("'")[1]).join(',');
}

var all = Array.from(new Set(fs.readFileSync('train.conll').toString().split('\n').map(x => x.split('\t')[1])))
  .filter(x => x !== '.' && x !== undefined);

console.log('All: ' + all.length)

fs.writeFileSync(
  'output.txt',
  all.map(word => kashida(word) + '\t' + word).join('\n')
);
