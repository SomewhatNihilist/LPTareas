package Tarea3;

abstract class Clase {

  protected int Armadura;

  public int getArmadura() {
    return this.Armadura;
  }
  public void setArmadura(int num) {
    this.Armadura = num;
  }

  abstract void crearClase();
  abstract void ataque();
  abstract void defender();

}
