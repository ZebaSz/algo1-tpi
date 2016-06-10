bool Sistema::listoParaCosechar() const
{
    int cantCosechables = 0;
    int cantCultivos = (_campo.dimensiones().ancho * _campo.dimensiones().largo) -2;
    int x = 0;
    while (_campo.dimensiones().ancho > x) {
        int y = 0;
        while(_campo.dimensiones().largo > y) {
            if(_estado.parcelas[x][y] == ListoParaCosechar) {
                ++cantCosechables;
            }
            ++y;
        }
        ++x;
    }
return (cantCosechables /(double) cantCultivos >= 0.9);
 
 
bool Sistema::listoParaCosechar() const
{
    int cantCosechables = 0;
    int cantCultivos = (_campo.dimensiones().ancho * _campo.dimensiones().largo) -2;
    int i = 0;
    while (_campo.dimensiones().ancho * _campo.dimensiones().largo > i) {
        if(_estado.parcelas[i/_campo.dimensiones().largo][i % _campo.dimensiones().largo] == ListoParaCosechar) {
            ++cantCosechables;
        }
        ++i;
    }
    return (cantCosechables /(double) cantCultivos >= 0.9);
}
 
 
 
 
    while (_campo.dimensiones().ancho * _campo.dimensiones().largo > i) {
        if(_estado.parcelas[i/_campo.dimensiones().largo][i % _campo.dimensiones().largo] == ListoParaCosechar) {
            ++cantCosechables;
        }
        ++i;
    }
 
 buscar practica de demostracion de ciclos aca: http://www.dc.uba.ar/materias/aed1/2016/1c/descargas/clases-practicas
 

Pc: cantCosechables == 0 ^ cantCultivos == (_campo.dimensiones().ancho * _campo.dimensiones().largo) -2 ^ i == 0
 
Qc: i == _campo.dimensiones().ancho * _campo.dimensiones().largo ^ cantCosechables = | [ 1 | j <-- [0..i), estadoParcela(j) == ListoParaCosechar] |
 
aux estadoParcela(int k) : EstadoCultivo = _estado.parcelas[k/_campo.dimensiones().largo][k % _campo.dimensiones().largo];
 
B: _campo.dimensiones().ancho * _campo.dimensiones().largo > i
 
fv: _campo.dimensiones().ancho * _campo.dimensiones().largo - i
 
cota: 0
 
I: 0 <= i <= _campo.dimensiones().ancho * _campo.dimensiones().largo ^ cantCosechables = | [ 1 | j <-- [0..i), estadoParcela(j) == ListoParaCosechar] |
 
Pc --> I:
la precondicion y el invariante estan divididos en tres y dos terminos "andeados" respectivamente:
los de Pc:
1) cantCosechables == 0
 
2) cantCultivos == (_campo.dimensiones().ancho * _campo.dimensiones().largo) -2
 
3) i == 0
 
los de I:
4) 0 <= i <= _campo.dimensiones().ancho * _campo.dimensiones().largo
 
5) cantCosechables = | [ 1 | j <-- [0..i), estadoParcela(j) == ListoParaCosechar] |
 
se justifican 4 y 5 a partir de 1, 2 y 3
 
3 ==> 4 //porque i == 0 cumple que 0 <= i
 
1 ^ 3 ==> 5 //porque 3 afirma que i == 0 entonces, en el invariante [0..i) es una lista vacia ==> cantCosechables == 0, que es lo que afirma 1. osea al entrar al ciclo se cumple que cantidad cosechables es 0 por que aun no se han observado parcelas
 
(I ^ ¬B) ==> Qc:
 
¬B:
6) _campo.dimensiones().ancho * _campo.dimensiones().largo <= i
 
Qc:
7)i == _campo.dimensiones().ancho * _campo.dimensiones().largo
 
8) cantCosechables = | [ 1 | j <-- [0..i), estadoParcela(j) == ListoParaCosechar] | //aca uso i para no volver a escribir todo el tamaño del campo, por logica de cortocircuito deberia poder usar 7 como premisa
 
con 4 5 y 6 se justifican 7 y 8
 
4 dice que i <= _campo.dimensiones().ancho * _campo.dimensiones().largo
6 dice que i >= _campo.dimensiones().ancho * _campo.dimensiones().largo
ambos implican
i == _campo.dimensiones().ancho * _campo.dimensiones().largo
y queda probado 7
 

 
