package raza;
import juego.*;

public abstract class Raza {
	
	protected Personaje pers;
	protected int[] mods = {0,0,0}; //{str,dex,con}
	protected String nombreRaza;
	
	Raza(Personaje pers) {
		this.pers = pers;
	}
	protected abstract void crearRaza();
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
