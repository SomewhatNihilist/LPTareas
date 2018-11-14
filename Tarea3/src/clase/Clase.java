package clase;
import juego.*;

public abstract class Clase {

	protected Personaje pers;
	protected int ac;
	protected String nombreClase;

	Clase(Personaje pers) {
		this.pers = pers;
	}
	/**Rellena valores basicos de Clase */
	protected abstract void crearClase();
	/**Ejecuta un ataque contra el oponente opp.
	 * @param opp Oponente que es atacado */
	public abstract void ataque(Personaje opp);
	/**Entra en defensa, modificando a pers.
	 * Adicionalmente imprime un mensaje tematicamente adecuado a la clase*/
	public abstract void defender();

	public int getAC() { return ac; }
	public void setAC(int num) { ac = num; }
	public String getNombreClase() { return nombreClase; }

}
