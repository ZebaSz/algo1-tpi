# Algorítmos y Estructuras de Datos I - TP Implementación

## Cómo compilar

En la raiz del repositorio hay un archivo Makefile. El mismo toma las fuentes de la carpeta `src`, crea los objetos en la carpeta `obj` y linkea todo al archivo `bin/main`.

Es decir, pueden hacer `make` y ya está.

Dentro de `src` está el Makefile original que vino con el template del TP. Tengan cuidado al compilar usando este Makefile o cualquier IDE que no organice los archivos así (ver Consideraciones).

## Consideraciones

- Si compilan a mano/sin usar `make`, tratar que los ejecutables estén en una carpeta `bin`, o tengan extensión `.exe`,  `.out` o  `.app`. De la misma manera, los objetos no linkeados deben ser `.obj`, `.o` o estar en una carpeta `obj`. Si no, hay que agregar la extensión (o carpeta) al `.gitignore`. NO PUSHEAR COMPILADOS.

- No pushear archivos relacionados con IDEs dentro de lo posible. Agregarlos al `.gitignore`. Sí se pueden pushear Makefiles, pero tratemos de usar uno solo. Si hace falta algo, modifiquen y/o avisen.

- No borré los archivos de Vector de Carlos.

### ¡Qué lindo readme!

Gracias. Lo hice con Markdown. Si no te parece lindo, no lo estás mirando en GitHub.