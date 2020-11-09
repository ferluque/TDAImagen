/**
 * @file 1umbralizar.cpp
 * @brief Fichero con la función umbralizar y su prueba
 * @author Fernando Luque (fl1562001@correo.ugr.es)
 * @date Octubre 2020
 * 
 * Para llamar al ejecutable correspondiente <ruta_ejecutable> <imagen_origen> <umbral_min> <umbral_max> <imagen_destino>
 */

#include "Imagen.h"
#include "imagenES.h"
#include <iostream>

using namespace std;

/**
 * @brief Umbralizar
 * @param original La imagen a umbralizar
 * @param T_1 El umbral inferior (cualquier pixel por debajo se establece a 255)
 * @param T_2 El umbral superior (cualquier pixel por encima se establece a 255)
 * @return La imagen umbralizada
 * @pre T_1 < T_2
 * 
 * Función que establece los valores de los píxeles más extremos tanto inferior(por debajo del umbral
 * inferior), como superiormente (por encima del umbral superior) al nivel máximo de luminosidad (blanco)
 */
Imagen umbralizar(const Imagen &original, const byte T_1, const byte T_2);

/**
 * @brief main de umbralización
 * @param nargs El número de argumentos
 * @param args Un vector de cadenas de caracteres (argumentos)
 * 
 * En este main usamos la función LeerImagenPGM del módulo imagenES, y leemos la imagen indicada, usamos el constructor de la clase Imagen con el array generado
 * y usamos la función umbralizar sobre ese objeto de la clase Imagen. Posteriormente, usamos la función de la clase Imagen convertir_a_Array(byte*)
 * para transformarla en un tipo de dato válido para la función de imagenES EscribirImagenPGM(...), liberamos la memoria del array y el destructor de
 * la clase Imagen se encarga de liberar la memoria ocupadas por las imágenes creadas.
 */
int main(int nargs, char *args[])
{
    // Comprobar validez de la llamada (Gestión de errores tomada del fichero negativo.cpp)
    if (nargs != 5)
    {
        cerr << "Error: Numero incorrecto de parametros.\n";
        cerr << "Uso: bin/1umbralizar <FichImagenOriginal> <T_1> <T_2> <FichImagenDestino>\n";
        exit(1);
    }

    char* origen = args[1];
    char* destino = args[4];
    
    cout << endl;
    cout << "Fichero origen: " << args[1] << endl;
    cout << "Fichero resultado: " << args[4] << endl;

    // Leer la imagen del fichero de entrada
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

    Imagen umbralizada = umbralizar(original, atoi(args[2]), atoi(args[3]));

    array = new byte[umbralizada.num_columnas() * umbralizada.num_filas()];
    umbralizada.convertir_a_Array(array);

    if (EscribirImagenPGM(destino, array, umbralizada.num_filas(), umbralizada.num_columnas()))
        cout << "La imagen se guardo en " << destino << endl;
    else
    {
        cerr << "Error: No pudo guardarse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        exit(2);
    }
    delete[] array;

    return 0;
}

Imagen umbralizar(const Imagen &original, const byte T_1, const byte T_2)
{
    Imagen umbralizada(original);
    for (int i = 0; i < original.num_filas(); i++)
        for (int j = 0; j < original.num_columnas(); j++)
            if (original.valor_pixel(i, j) <= T_1 || original.valor_pixel(i, j) >= T_2)
                umbralizada.asigna_pixel(i, j, 255);

    return umbralizada;
}
