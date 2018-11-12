package Tarea3;

import java.util.*;

public class Enano extends Raza {

  private int Fuerza;
  private int Constitucion;
  public String habilidad;

  public int getFuerza() {
    return this.Fuerza;
  }
  public int getConstitucion() {
    return this.Constitucion;
  }
  public void setFuerza(int num) {
    this.Fuerza = num;
  }
  public void setConstitucion(int num) {
    this.Constitucion = num;
  }

  public void crearRaza() {
    setFuerza(1);
    setConstitucion(2);
  }

  public void habilidad() {
    habilidad = "Resistencia";
  }

}
