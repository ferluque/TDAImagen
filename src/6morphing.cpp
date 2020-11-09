/**
 * @file 6morphing.cpp
 * @brief Fichero con la función morphing y su prueba
 * @author Fernando Luque (fl1562001@correo.ugr.es)
 * @date Octubre 2020
 * 
 * Para llamar al ejecutable correspondiente <ruta_ejecutable> <imagen_origen> <imagen_destino> [<imágenes intermedias>].
 * Con el objetivo de "automatizar" la generación de los nombres de ficheros de las imágenes intermedias que generará el morhping, he realizado un
 * pequeño "script" en ruby, "generador_argumentos.rb", el cual al ejecutarlo en la terminal de la siguiente manera:\n
 * > ruby generador_argumentos.rb > argumentos.txt\n
 * nos incluirá en el archivo argumentos.txt una lista con todas las rutas de las imágenes intermedias que pasaremos como parámetros al
 * correspondiente ejecutable (bin/6morphing)
 */

#include "Imagen.h"
#include "imagenES.h"
#include <iostream>

using namespace std;

/**
 * @brief Función morphing entre dos imágenes
 * @param origen La imagen inicial
 * @param destino La imagen a la que llegará el morphing
 * @param i El índice de imagen intermedia que vamos a generar
 * @return La i-ésima imagen generada por el proceso de morphing
 * 
 * Esta función genera la i-ésima imagen intermedia entre otras dos, asignando a cada píxel el siguiente valor:\n
 * alpha_i*O(x,y) + (1-alpha_i)*D(x,y)\n
 * donde alpha_i es un valor entre 0 y 1, que valdrá alpha_i = i/pasos, siendo pasos el número de imágenes intermedias que generamos
 */
Imagen Morphing (const Imagen& origen, const Imagen& destino, const float alpha_i);

/**
 * @brief main de morphing
 * @param nargs La cantidad de argumentos
 * @param args Los argumentos
 * 
 * @see 1umbralizar.cpp El procedimiento para la entrada y salida es similar al seguido en el main de 1umbralizar.cpp
 * 
 * Tal y como he orientado este ejercicio, la función morphing me genera la i-ésima Imagen intermedia entre una de origen y una de final, es por
 * eso que incluyo esta función en un bucle, en el que se sacan las pasos (pasos=cantidad de imágenes intermedias =nargs-3) imágenes con la función
 * EscribirImagenPGM(...) del módulo imagenES
 */
int main (int nargs, char *args[]) {
    if (nargs < 4)
    {
        cerr << "Error: Numero incorrecto de parametros.\n";
        cerr << "Uso: bin/6morphing <FichImagenOriginal> <FichImagenDestino> [<Ficheros_intermedios>] \n";
        exit(1);
    }

    char* origen = args[1];
    char* destino = args[2];

    cout << endl;
    cout << "Fichero origen: " << origen << endl;
    cout << "Fichero resultado: " << destino << endl;

    //Imagen de origen
    int filas = 0, columnas = 0;
    byte* array = LeerImagenPGM(origen, filas, columnas);
    Imagen original (filas, columnas, array);
    delete [] array;

    //Imagen de destino
    filas = columnas = 0;
    array = LeerImagenPGM(destino, filas, columnas);
    Imagen final (filas, columnas, array);
    delete [] array;
    
    //Se hacen tantos morphings como imágenes intermedias haya (o hasta que la imagen 
    //generada sea igual que la de destino)
    int pasos = nargs-3;
    for (int i=0; i<pasos; i++) {
        Imagen nueva = Morphing(original, final, static_cast<float>(i)/pasos);
        array = new byte [nueva.num_filas()*nueva.num_columnas()];
        nueva.convertir_a_Array(array);
        if (!EscribirImagenPGM(args[3+i], array, nueva.num_filas(), nueva.num_columnas())) {
            cerr << "Error: no pudo guardarse la imagen " << args[3+i] << endl;
            cerr << "Terminando la ejecución del programa. " << endl;
            exit(2);
        }
        delete [] array;
    }

}

Imagen Morphing (const Imagen& origen, const Imagen& destino, const float alpha_i) {
    Imagen intermedia (origen);
    float primer_sumando, segundo_sumando;
    for (int i=0; i<intermedia.num_filas(); i++) {
        for (int j=0; j<intermedia.num_columnas(); j++) {
            primer_sumando = alpha_i*origen.valor_pixel(i, j);
            segundo_sumando = (1.0-alpha_i)*destino.valor_pixel(i,j);
            intermedia.asigna_pixel(i, j,primer_sumando+segundo_sumando);
        }
    }
    return intermedia;
}