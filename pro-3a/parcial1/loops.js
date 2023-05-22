/*var nombres = ['Carlos', 'Alejandro', 'Cesar', 'Daniel', 'Eduardo', 'Fernando'];

function saludo(nombre){
    console.log(`Hola ${nombre}`);
}

for (var i of nombres){
    saludo(i);
}
*/

var nombres = ['Carlos', 'Alejandro', 'Cesar', 'Daniel', 'Eduardo', 'Fernando'];

function saludo(nombre){
    console.log(`Hola ${nombre}`);
}

while (nombres.length > 0){
    var nombre = nombres.shift(); //shift() elimina el primer elemento del array y lo devuelve como resultado
    saludo(nombre);
}
