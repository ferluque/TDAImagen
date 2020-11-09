/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Imagen.h"

void Imagen::deallocate()
{
    for (int i = 0; i < num_filas(); i++)
        delete[] casillas[i];
    delete[] casillas;
    casillas = nullptr;
    nc = nf = 0;
}

void Imagen::allocate(int filas, int columnas)
{
    nf = filas;
    nc = columnas;
    casillas = new byte *[num_filas()];
    for (int i = 0; i < num_filas(); i++)
        casillas[i] = new byte[num_columnas()];
}

void Imagen::copiar(const Imagen &J)
{
    for (int i = 0; i < num_filas(); i++)
        for (int j = 0; j < num_columnas(); j++)
            asigna_pixel(i, j, J.valor_pixel(i, j));
}

Imagen::Imagen()
{
    casillas = nullptr;
    nf = nc = 0;
}

Imagen::Imagen(const Imagen &J)
{
    casillas = nullptr;
    nf = nc = 0;
    allocate(J.num_filas(), J.num_columnas());
    copiar(J);
}

Imagen::Imagen(int filas, int cols)
{
    allocate(filas, cols);
}

Imagen::~Imagen()
{
    deallocate();
}

Imagen::Imagen(int filas, int cols, byte *array)
{
    allocate(filas, cols);
    for (int i = 0; i < filas; i++)
        for (int j = 0; j < cols; j++)
            asigna_pixel(i, j, array[i * cols + j]);
}

Imagen& Imagen::operator=(const Imagen& otra) {
    if (this != &otra) {
        deallocate();
        allocate(otra.num_filas(), otra.num_columnas());
        copiar(otra);
    }
}

void Imagen::convertir_a_Array (byte* array) {
    for (int i=0; i<num_filas(); i++)
        for (int j=0; j<num_columnas(); j++)
            array[i*num_columnas() + j] = valor_pixel(i,j);
}
