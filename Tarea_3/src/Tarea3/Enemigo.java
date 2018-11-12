package Tarea3;

import java.util.*;

public class Enemigo implements Personaje {

  static int vida;
  static String nombre;

  public void setVida(int num) {
    this.vida = num;
  }
  public int getVida() {
    return this.vida;
  }
  public void setNombre(String nombre) {
    this.nombre = nombre;
  }
  public String getNombre() {
    return this.nombre;
  }
  public void asignarRaza(int mi_raza) {
    if(mi_raza == 0){
      Humano raza = new Humano();
      raza.crearRaza();
    } else if(mi_raza == 1){
      Elfo raza = new Elfo();
      raza.crearRaza();
    } else if(mi_raza == 2){
      Enano raza = new Enano();
      raza.crearRaza();
    } else if(mi_raza == 3){
      Orco raza = new Orco();
      raza.crearRaza();
    }
  }
  public void asignarClase(int mi_clase) {
    if(mi_clase == 0){
        Barbaro clase = new Barbaro();
        clase.crearClase();
    } else if(mi_clase == 1){
        Picaro clase = new Picaro();
        clase.crearClase();
    } else if(mi_clase == 2){
        Mago clase = new Mago();
        clase.crearClase();
    } else if(mi_clase == 3){
        Clerigo clase = new Clerigo();
        clase.crearClase();
    }
  }
  public void asignarVida(int num) {
    setVida(num);
  }
  public void asignarNombre(String name) {
    setNombre(name);
  }

}
