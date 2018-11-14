package clase;
import juego.*;

public abstract class Clase {

	protected Personaje pers;
	protected int ac;
	protected String nombreClase;
	
	Clase(Personaje pers) {
		this.pers = pers;
	}
	protected abstract void crearClase();
	public abstract void ataque(Personaje opp);
	public abstract void defender();

	public int getAC() { return ac; }
	public void setAC(int num) { ac = num; }
	public String getNombreClase() { return nombreClase; }

}
