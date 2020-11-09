/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: ferluque
 *
 * Created on 19 de octubre de 2020, 18:32
 */

#include <cstdlib>
#include "imagenES.h"
#include "Imagen.h"

using namespace std;

/**
 * @brief Añade un marco negro de un píxel a la imagen 
 * @param I La imagen a la que añadir un marco 
 */
void enmarca_imagen(Imagen& I);

/*
 * 
 */
int main(int argc, char** argv) {
    int nf = 10, nc = 10;

    Imagen I(nf, nc);

    for (int f = 0; f < I.num_filas(); f++)
        for (int c = 0; c < I.num_columnas(); c++)
            I.asigna_pixel(f, c, 255);
    
    
    return 0;
}

void enmarca_imagen(Imagen& I) {
    int f, c, nf = I.num_filas(), nc = I.num_columnas();
    for (f = 0; f < nf; f++)
        I.asigna_pixel(f, 0, 0);
    for (f = 0; f < nf; f++)
        I.asigna_pixel(f, nc - 1, 0);
    for (c = 0; c < nc; c++)
        I.asigna_pixel(0, c, 0);
    for (c = 0; c < nc; c++)
        I.asigna_pixel(nf - 1, c, 0);
}


