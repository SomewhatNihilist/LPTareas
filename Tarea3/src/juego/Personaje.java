package juego;

public interface Personaje {
	//Este se beneficiaria bastante de ser un abstract class
	public void asignarRaza(int raza);
	public void asignarClase(int clase);
	public void asignarVida();
	public void asignarNombre(String name);
	
	public void turno(Personaje opp);
	
	public void printStatus();

	public String getNombre();
	public raza.Raza getRaza();
	public clase.Clase getClase();
	public int getVida();
	public void setVida(int num);
	public Boolean getDef();
	public void setDef(Boolean bool);
}