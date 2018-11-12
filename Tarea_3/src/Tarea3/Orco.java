package Tarea3;

import java.util.*;

public class Orco extends Raza {

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
    setFuerza(2);
    setConstitucion(1);
  }

  public void habilidad() {
    habilidad = "Atacante";
  }

}
