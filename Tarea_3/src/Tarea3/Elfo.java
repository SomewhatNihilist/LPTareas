package Tarea3;

import java.util.*;

public class Elfo extends Raza {

  private int Destreza;
  private int Constitucion;
  public String habilidad;

  public int getDestreza() {
    return this.Destreza;
  }
  public int getConstitucion() {
    return this.Constitucion;
  }
  public void setDestreza(int num) {
    this.Destreza = num;
  }
  public void setConstitucion(int num) {
    this.Constitucion = num;
  }

  public void crearRaza() {
    setDestreza(2);
    setConstitucion(1);
  }

  public void habilidad() {
    habilidad = "Evasion";
  }

}
