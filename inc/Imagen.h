/**
 * @file Imagen.h
 * @brief Fichero de cabecera para la clase Imagen
 * @author Fernando Luque (fl1562001@correo.ugr.es)
 * 
 * Declara un TDA Imagen que nos permite representar imágenes en formato PGM
 */
#ifndef IMAGEN_H
#define IMAGEN_H

typedef unsigned char byte;

/**
 * @brief T.D.A Imagen
 * 
 * Una instancia @e i del tipo de dato abstracto @c Imagen es un objeto que representa una matriz de un tamaño nf x nc, donde se
 * reflejan los valores de luminosidad de una imagen en escala de grises (valores entre 0 y 255)
 * 
 * @author Fernando Luque (fl1562001@correo.ugr.es)
 * @date Octubre 2020
 */
class Imagen {
private:
    /**
     * @page repConjunto Rep del TDA Imagen
     * @section invConjunto Invariante de la representación
     * 
     * El invariante es \e nf>0 \e nc>0
     */
    int nf; /**< filas */
    int nc; /**< columnas */
    byte** casillas; /**< matriz */
    
public:
    /**
     * @brief Constructor sin parámetros
     * 
     * Inicializa una imagen de 0filasx0columnas
     */
    Imagen();
    /**
     * @brief Constructor de copia
     * @param J La imagen a copiar
     * 
     * Hace su respectiva reserva de memoria en función del tamaño del parámetro, y copia todos los elementos uno a uno
     */
    Imagen(const Imagen& J);
    /**
     * @brief Constructor con parámetros
     * @param filas El número de filas
     * @param cols El número de columnas
     * @pre filas > 0 && cols > 0
     * @post Los valores de las casillas no se inicializan
     * @warning NO se inicializan los valores de las casillas
     * 
     * Se hace la reserva dinámica de una matriz de tamaño filas x columnas
     */
    Imagen (int filas, int cols);
    /**
     * @brief Constructor a partir de los datos leídos por la función E/S
     * @param filas El número de filas de la imagen
     * @param cols El número de columnas de la imagen
     * @param array El vector con los datos
     * @post La imagen queda inicializada
     * 
     * Se inicializa una matriz a partir de los datos que recibimos de la función del módulo imagenES, filas, columnas y un array
     * unidimensional con los valores de luminosidad
     */
    Imagen (int filas, int cols, byte* array);
    /**
     * @brief Destructor
     * 
     * Se libera la memoria dinámica ocupada por la imagen
     */
    ~Imagen();
    /**
     * @brief Operador de asignación
     * @param otra La imagen a asignar
     * @return La imagen asignada por referencia para asignaciones encadenadas
     * 
     * Se libera previamente la memoria que tuviera ocupada la imagen y se hace una copia en memoria de la imagen pasada como parámetro
     */
    Imagen& operator=(const Imagen& otra);
    /**
     * @brief Método consultor número de filas
     * @return nf
     */
    inline int num_filas () const {return nf;};
    /**
     * @brief Método consultor número de columnas
     * @return nc
     */
    inline int num_columnas () const {return nc;};
    /**
     * @brief Set casillas[fila][col] = valor
     * @param fila La fila del elemento
     * @param col La columna del elemento
     * @param valor El valor a establecer
     * @pre 0<=fila<num_filas() && 0<=col<num_columnas() && 0<=valor<=255
     */
    inline void asigna_pixel (int fila, int col, byte valor) {casillas[fila][col] = valor;};
    /**
     * @brief Consultor casillas[fila][col]
     * @param fila La fila del elemento a consultar
     * @param col La columna del elemento a consultar
     * @return casillas[fila][col]
     * @pre 0<=fila<num_filas() && 0<=col<num_columnas()
     */
    inline byte valor_pixel (int fila, int col) const {return casillas[fila][col];};
    /**
     * @brief Función que introduce la imagen que invoca el método en el array
     * @param array El array donde se introducirán los datos
     * @pre Se espera un puntero nulo 
    */
    void convertir_a_Array (byte* array);
private:
    /**
     * @brief Método auxiliar de copia (no libera memoria)
     * @param J La imagen a copiar
     * @warning NO hace la reserva y liberación de memoria del objeto llamante
     */
    void copiar (const Imagen& J);
    /**
     * @brief Método de reserva de memoria para una matriz
     * @param filas El número de filas
     * @param columnas El número de columnas
     * @pre filas > 0 && columnas > 0
     * @warning NO libera la memoria previamente ocupada
     */
    void allocate (int filas, int columnas);
    /**
     * @brief Método auxiliar de liberación de memoria
     */
    void deallocate ();
};


#endif /* IMAGEN_H */

