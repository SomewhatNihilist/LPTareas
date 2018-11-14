package raza;

import juego.Juego;
import juego.Personaje;

public class Orco extends Raza {

	public Orco(Personaje pers) {
		super(pers);
		crearRaza();
	}

	protected void crearRaza() {
		mods[0] = 2;
		mods[2] = 1;
		nombreRaza = "Orco";
	}

	public int habilidad(int context) {
		switch(context) {
			case Juego.CTXT_ROLL:
				return Juego.lanzarDados(20);
			case Juego.CTXT_BFAT:
				return 2;
			default: return 0;
		}
	}

}
