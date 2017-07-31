# Algorítmos y Estructuras de Datos I - TP Implementación

## Cómo compilar

En la raiz del repositorio hay un archivo Makefile. El mismo toma las fuentes de la carpeta `src`, crea los objetos en la carpeta `obj` y linkea todo al archivo `bin/main`.

Es decir, pueden hacer `make` y ya está.

Dentro de `src` está el Makefile original que vino con el template del TP. Tengan cuidado al compilar usando este Makefile o cualquier IDE que no organice los archivos así (ver Consideraciones).

Se puede ejecutar ese `bin/main`, pero ya no hace falta porque ¡tests!

## Cómo correr los tests

Hay dos maneras: la geek y la cool.

### La geek

1. `mkdir build && cd build`
2. `cmake ..`
3. `make`
4. `./tests/correrTests`

Para volver a compilar, simplemente correr `make` de nuevo.

En caso de que no funcione correctamente la compilación, pueden borrar 
el directorio `build` y volver a realizar los 4 pasos.

### La cool

CLion reconoce los tests. Entre las configuraciones de ejecución (arriba a la derecha) debería figurar "correrTests". Elíjanlo, denle correr y disfruten la manera visual linda de ver los resultados.

### ¿CLion? Yo tenía un proyecto de CLion

Los profes nos dieron su propio  `CMakeLists.txt`. Pros: tests en CLion lindos. Cons: chau configuraciones viejas. Igual lo vale, ya no hace falta usar main.

## Las demostraciones

Para compilar los LaTeX a PDF en Linux sin usar TeXMaker, pueden correr (dentro de la carpeta de demostraciones) `pdflatex resolucion.pdf`. Eso produce muchísimo output y es bastante feo. Si tienen TeXMaker instalado, deberían tener un script que lo hace más lindo: `texfot pdflatex resolucion.pdf`. El output que queda son mayormente errores que estaría piola corregir.

O pueden usar el script que dejé hecho que hace exactamente eso. Y además abre el PDF inmediatamente después.

## Consideraciones

- Si compilan a mano/sin usar `make`, tratar que los ejecutables estén en una carpeta `bin`, o tengan extensión `.exe`,  `.out` o  `.app`. De la misma manera, los objetos no linkeados deben ser `.obj`, `.o` o estar en una carpeta `obj`. Si no, hay que agregar la extensión (o carpeta) al `.gitignore`. NO PUSHEAR COMPILADOS.

- No pushear archivos relacionados con IDEs dentro de lo posible. Agregarlos al `.gitignore`. Sí se pueden pushear Makefiles, pero tratemos de usar uno solo. Si hace falta algo, modifiquen y/o avisen.

- No borré los archivos de Vector de Carlos.

### ¡Qué lindo readme!

Gracias. Lo hice con Markdown. Si no te parece lindo, no lo estás mirando en GitHub.