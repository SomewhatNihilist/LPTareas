package raza;
import juego.*;

public abstract class Raza {

	protected Personaje pers;
	protected int[] mods = {0,0,0}; //{str,dex,con}
	protected String nombreRaza;

	Raza(Personaje pers) {
		this.pers = pers;
	}
	/**Rellena valores basicos de Raza */
	protected abstract void crearRaza();
	/**Activa la habilidad del personaje, si es que tiene en el contexto dado.
	 * @param context Valor que representa el contexto en el que se aplica la habilidad. Referir a las constantes Juego.CTXT_* .
	 * @return 0 si no tiene una habilidad en el contexto dado, o 1d20 si no tiene habilidad en el contexto CTXT_ROLL, sino, depende de la habilidad
	 */
	public abstract int habilidad(int context);

	public String getNombreRaza() { return nombreRaza; }
	public void setPers(Personaje personaje) { pers = personaje; }
	public Personaje getPers() { return pers; }
	public int[] getMods() { return mods; }
	public void setStr(int num) { mods[0] = num; }
	public int getStr() { return mods[0]; }
	public void setDex(int num) { mods[1] = num; }
	public int getDex() { return mods[1]; }
	public void setCon(int num) { mods[2] = num; }
	public int getCon() { return mods[2]; }

}
