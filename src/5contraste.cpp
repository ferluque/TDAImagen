/**
 * @file 5contraste.cpp
 * @brief Fichero con la función contraste y su prueba
 * @author Fernando Luque (fl1562001@correo.ugr.es)
 * @date Octubre 2020
 * 
 * Para llamar al ejecutable correspondiente <ruta_ejecutable> <imagen_origen> <minimo> <maximo> <imagen_destino>
 */


#include "Imagen.h"
#include "imagenES.h"
#include <iostream>

using namespace std;

/**
 * @brief Función contraste
 * @param original La imagen a la que aplicar el contraste
 * @param min El valor mínimo de luminosidad indicado en la llamada al ejecutable
 * @param max El valor máximo de luminosidad indicado en la llamada al ejecutable
 * @return La imagen resultante de aplicar el filtro de contraste indicado a la imagen original
 * 
 * Esta función asigna a cada pixel el siguiente valor:\n
 * min + [((max – min) / (b – a)) * (z – a)]\n
 * donde min y max son los parámetros indicados por el usuario en la llamada al ejecutable, b el valor máximo de luminosidad en la imagen original,
 * a el mínimo, y z el valor de cada píxel.
 */
Imagen Contraste(const Imagen& original, const byte min, const byte max);

/**
 * @brief Función mínimo en Imagen
 * @param imagen La imagen de la cual encontraremos el mínimo valor de luminosidad
 * @return El mínimo valor de luminosidad en la imagen
 */
byte minimo(const Imagen& imagen);

/**
 * @brief Función máximo en Imagen
 * @param imagen La imagen de la cual encontraremos el máximo valor de luminosidad
 * @return El máximo valor de luminosidad en la imagen
 */
byte maximo(const Imagen& imagen);

/**
 * @brief main de contraste
 * @param nargs El número de argumentos
 * @param args El array de cadenas de caracteres (argumentos)
 * @return 0 Si correcto -1 Si hay problema con la cantidad de argumentos
 * 
 * @see 1umbralizar.cpp
 * El procedimiento para la entrada salida es similar al seguido en el main de 1umbralizar.cpp.\n
 */
int main(int nargs, char* args[]) {
    if (nargs != 5)
    {
        cerr << "Error: Numero incorrecto de parametros.\n";
        cerr << "Uso: bin/5contraste <FichImagenOriginal> <min> <max> <FichImagenDestino>\n";
        exit(1);
    }

    char* origen = args[1];
    char* destino = args[6];
    
    cout << endl;
    cout << "Fichero origen: " << origen << endl;
    cout << "Fichero resultado: " << destino << endl;

    int filas = 0, columnas = 0;
    byte* array = LeerImagenPGM(args[1], filas, columnas);

    if (!array)
    {
        cerr << "Error: No pudo leerse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        exit(1);
    }

    Imagen original(filas, columnas, array);

    delete [] array;

    Imagen contrastada;
    contrastada = Contraste(original, atoi(args[2]), atoi(args[3]));
    
    array = new byte [contrastada.num_filas()*contrastada.num_columnas()];
    contrastada.convertir_a_Array(array);

    if (EscribirImagenPGM(destino, array, contrastada.num_filas(), contrastada.num_columnas()))
        cout << "La imagen se guardo en " << destino << endl;
    else
    {
        cerr << "Error: No pudo guardarse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        exit(2);
    }

    delete [] array;

    return 0;
}

Imagen Contraste(const Imagen& original, const byte min, const byte max) {
    Imagen contrastada(original);
    byte valor = 0, a = minimo(original), b = maximo(original), diferencia_pixel_minimo_foto;
    const double razon_amplitudes = static_cast<double>(max-min)/(b-a); double producto = 0.0;
    
    for (int i = 0; i < contrastada.num_filas(); i++) {
        for (int j = 0; j < contrastada.num_columnas(); j++) {
            diferencia_pixel_minimo_foto = original.valor_pixel(i, j) -a;
            producto = diferencia_pixel_minimo_foto*razon_amplitudes;
            valor = min + producto;
            contrastada.asigna_pixel(i, j, valor);
        }
    }
    return contrastada;
}

byte minimo(const Imagen& imagen) {
    byte minimo = imagen.valor_pixel(0, 0);
    for (int i = 0; i < imagen.num_filas(); i++)
        for (int j = 0; j < imagen.num_columnas(); j++)
            if (imagen.valor_pixel(i, j) < minimo)
                minimo = imagen.valor_pixel(i, j);
    return minimo;
}

byte maximo(const Imagen& imagen) {
    byte maximo = imagen.valor_pixel(0, 0);
    for (int i = 0; i < imagen.num_filas(); i++)
        for (int j = 0; j < imagen.num_columnas(); j++)
            if (imagen.valor_pixel(i, j) > maximo)
                maximo = imagen.valor_pixel(i, j);
    return maximo;
}