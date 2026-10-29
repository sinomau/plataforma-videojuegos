#include <string>
#include <iostream>
#include <ctime>
#include "Fecha.h"
#include "Utils.h"

int Fecha::toInt() {
    return _anio * 10000 + _mes * 100 + _dia;
}


void Fecha::establecerFechaPorDefecto(){
   _dia = 1;
   _mes = 1;
   _anio = 1900;
}

bool Fecha::esBisiesto(int anio){
    if ((anio % 4 == 0 && anio % 100 != 0) || anio % 400 == 0){
      return true;
    }
    return false;
}

bool Fecha::esValida(int dia, int mes, int anio){
   if (anio <= 0 || mes < 1 || mes > 12 || dia < 1){
      return false;
   }

   int dias[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
   if (esBisiesto(anio)){
      dias[1]++;
   }

   return dia <= dias[mes-1];
}

void Fecha::agregarDia(){
   int dias[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
   if (esBisiesto(_anio)){
      dias[1]++;
   }

   _dia++;
   if (_dia > dias[_mes-1]){
      _dia = 1;
      _mes++;
      if (_mes > 12){
         _mes = 1;
         _anio++;
      }
   }
}

void Fecha::agregarDias(int cantidadDias){

   if (cantidadDias > 0){
      for(int i=0; i<cantidadDias; i++){
         agregarDia();
      }
   }

}

Fecha::Fecha(){
   establecerFechaPorDefecto();
}

Fecha::Fecha(int dia, int mes, int anio){
   if (esValida(dia, mes, anio)){
      _dia = dia;
      _mes = mes;
      _anio = anio;
   }
   else{
      establecerFechaPorDefecto();
   }
}

int Fecha::getDia(){
   return _dia;
}
int Fecha::getMes(){
   return _mes;
}
int Fecha::getAnio(){
   return _anio;
}

bool Fecha::setDia(int dia){
    if (!esValida(dia, _mes, _anio)){
        return false;
    }
    _dia = dia;
    return true;
}

bool Fecha::setMes(int mes){
    if (!esValida(_dia, mes, _anio)){
        return false;
    }
    _mes = mes;
    return true;
}

bool Fecha::setAnio(int anio){
    if (!esValida(_dia, _mes, anio)){
        return false;
    }
    _anio = anio;
    return true;
}

void Fecha::cargar(){
   int dia, mes, anio;

   do {
      std::cout << "Dia: ";
      dia = leerEntero();
      std::cout << "Mes: ";
      mes = leerEntero();
      std::cout << "Anio: ";
      anio = leerEntero();

      if (!esValida(dia, mes, anio)){
         std::cout << "Fecha invalida. Intente nuevamente." << std::endl;
      }
   } while (!esValida(dia, mes, anio));

   _dia = dia;
   _mes = mes;
   _anio = anio;
}

void Fecha::mostrar(){
   std::cout << toString() << std::endl;
}

void Fecha::setFechaActual(){
   std::time_t ahora = std::time(0);
   std::tm* local = std::localtime(&ahora);

   _dia = local->tm_mday;
   _mes = local->tm_mon + 1;
   _anio = local->tm_year + 1900;
}

int Fecha::getAnioActual() {
    std::time_t ahora = std::time(nullptr);
    std::tm* local = std::localtime(&ahora);

    _anio = local->tm_year + 1900;

    return _anio;
}


std::string Fecha::toString(std::string formatoFecha){
   std::string fechaFormateada = "";

   std::string DD = std::to_string(_dia);
   std::string MM = std::to_string(_mes);
   std::string YYYY = std::to_string(_anio);
   // DD/MM/YYYY
   if (_dia < 10){
      DD = "0" + std::to_string(_dia);
   }
   if (_mes < 10){
      MM = "0" + std::to_string(_mes);
   }

   if (formatoFecha == "DD/MM/YYYY"){
      fechaFormateada = DD + "/" + MM + "/" + YYYY;
   }
   else if (formatoFecha == "YYYY/MM/DD"){
      fechaFormateada = YYYY + "/" + MM + "/" + DD;
   }
   else{
      fechaFormateada = DD + "/" + MM + "/" + YYYY;
   }

   return fechaFormateada;
}

