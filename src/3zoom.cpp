/**
 * @file 3zoom.cpp
 * @brief Fichero con la función zoom y su prueba
 * @author Fernando Luque (fl1562001@correo.ugr.es)
 * @date Octubre 2020
 * 
 * Para llamar al ejecutable correspondiente <ruta_ejecutable> <imagen_origen> <x_1> <y_1> <x_2> <y_2> <imagen_destino>
 */

#include "Imagen.h"
#include "imagenES.h"
#include <iostream>

using namespace std;

/**
 * @brief CoordPixel
 * 
 * Una instancia @e punto del tipo de dato abstracto @c CoordPixel es una estructura que representa
 * los dos índices de acceso a una matriz 2D 
 */
struct CoordPixel
{
    /**
     * @page repConjunto Rep del CoorPixel
     * @section invConjunto Invariante de la representacion
     * 
     * Para el uso que le vamos a dar, localizar un pixel de una imagen, el invariante
     * es \e x>=0 \e y>=0
     */
    int x;
    int y;
};

/**
 * @brief Zoom
 * @param original La imagen a la que se hará zoom
 * @param superior_izq El pixel (x_1, y_1)
 * @param inferior_dcha El pixel (x_2, y_2)
 * @pre superior_izq.x < inferior_dcha.x && superior_izq.y < inferior_dcha.y
 * @return El fragmento de imagen con un zoom x2
 * 
 * Función que devuelve un zoom de la imagen desde un pixel (x_1, y_2) hasta un pixel (x_2, y_2), ampliada x2
 */
Imagen Zoom(const Imagen &original, const CoordPixel &superior_izq, const CoordPixel &inferior_dcha);

/**
 * @brief Función que evalúa la media entre dos variables tipo byte
 * @param uno Un valor
 * @param otro El otro valor
 * @return (uno+otro)/2
 */
byte Media(const byte uno, const byte otro);

/**
 * @brief main de zoom
 * @param nargs El número de argumentos
 * @param args El array de cadenas de caracteres (argumentos)
 * @return 0 Si correcto -1 Si hay problema con la cantidad de argumentos
 * 
 * @see 1umbralizar.cpp
 * El procedimiento para la entrada salida es similar al seguido en el main de 1umbralizar.cpp.\n
 * Como especificaciones, he usado la clase Punto2D para representar los dos puntos de inicio y fin de la imagen ampliada
 * 
 */
int main(int nargs, char *args[])
{
    if (nargs != 7)
    {
        cerr << "Error: Numero incorrecto de parametros.\n";
        cerr << "Uso: bin/3zoom <FichImagenOriginal> <x_1> <y_1> <x_2> <y_2> <FichImagenDestino>\n";
        exit(1);
    }

    char* origen = args[1];
    char* destino = args[6];
    
    cout << endl;
    cout << "Fichero origen: " << origen << endl;
    cout << "Fichero resultado: " << destino << endl;

    int filas = 0, columnas = 0;
    byte *array = LeerImagenPGM(origen, filas, columnas);

    if (!array)
    {
        cerr << "Error: No pudo leerse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        exit(1);
    }

    Imagen original(filas, columnas, array);

    delete[] array;

    Imagen ampliada;

    CoordPixel superior_izq;
    superior_izq.x = atoi(args[2]);
    superior_izq.y = atoi(args[3]);
    CoordPixel inferior_dcha;
    inferior_dcha.x = atoi(args[4]);
    inferior_dcha.y = atoi(args[5]);

    ampliada = Zoom(original, superior_izq, inferior_dcha);

    array = new byte[ampliada.num_filas() * ampliada.num_columnas()];

    ampliada.convertir_a_Array(array);

    if (EscribirImagenPGM(destino, array, ampliada.num_filas(), ampliada.num_columnas()))
        cout << "La imagen se guardo en " << destino << endl;
    else
    {
        cerr << "Error: No pudo guardarse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        exit(2);
    }

    delete[] array;
}

Imagen Zoom(const Imagen &original, const CoordPixel &superior_izq, const CoordPixel &inferior_dcha)
{
    int filas_ampliada = 2 * (inferior_dcha.x - superior_izq.x) - 1;
    int cols_ampliada = 2 * (inferior_dcha.y - superior_izq.y) - 1;
    byte interpolado;

    int fila_lectura = superior_izq.x, col_lectura = superior_izq.y;

    Imagen ampliada(filas_ampliada, cols_ampliada);

    //Copiamos los elementos que no hay que interpolar (columna par y fila par)
    for (int i = 0; i < ampliada.num_filas(); i += 2)
    {
        for (int j = 0; j < ampliada.num_columnas(); j += 2)
        {
            ampliada.asigna_pixel(i, j, original.valor_pixel(fila_lectura, col_lectura));
            col_lectura++;
        }
        fila_lectura++;
        col_lectura = superior_izq.y;
    }
    //Interpolamos sobre las columnas en aquellas filas en las que ya haya elementos
    //(de los que no se han interpolado), es decir en las filas pares, columnas impares
    for (int i = 0; i < ampliada.num_filas(); i += 2)
    {
        for (int j = 1; j < ampliada.num_columnas(); j += 2)
        {
            interpolado = Media(ampliada.valor_pixel(i, j - 1), ampliada.valor_pixel(i, j + 1));
            ampliada.asigna_pixel(i, j, interpolado);
        }
    }

    //Una vez rellenas todas las filas pares, interpolamos todos los elementos de
    //todas las filas impares
    for (int i = 1; i < ampliada.num_filas(); i += 2)
    {
        for (int j = 0; j < ampliada.num_columnas(); j++)
        {
            interpolado = Media(ampliada.valor_pixel(i - 1, j), ampliada.valor_pixel(i + 1, j));
            ampliada.asigna_pixel(i, j, interpolado);
        }
    }

    return ampliada;
}

byte Media(const byte uno, const byte otro)
{
    return (uno + otro) / 2;
}
