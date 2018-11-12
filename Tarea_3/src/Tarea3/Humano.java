package Tarea3;

import java.util.*;

public class Humano extends Raza {

  private int Fuerza;
  private int Destreza;
  private int Constitucion;
  public String habilidad;

  public int getFuerza() {
    return this.Fuerza;
  }
  public int getDestreza() {
    return this.Destreza;
  }
  public int getConstitucion() {
    return this.Constitucion;
  }
  public void setFuerza(int num) {
    this.Fuerza = num;
  }
  public void setDestreza(int num) {
    this.Destreza = num;
  }
  public void setConstitucion(int num) {
    this.Constitucion = num;
  }

  public void crearRaza() {
    setFuerza(1);
    setDestreza(1);
    setConstitucion(1);
  }

  public void habilidad() {
    habilidad = "Suerte";
  }

}
