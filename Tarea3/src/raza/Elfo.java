package raza;

import juego.Juego;
import juego.Personaje;

public class Elfo extends Raza {

	public Elfo(Personaje pers) {
		super(pers);
		crearRaza();
	}

	protected void crearRaza() {
		mods[1] = 2;
		mods[2] = 1;
		nombreRaza = "Elfo";
	}

	public int habilidad(int context) {
		switch(context) {
			case Juego.CTXT_ROLL:
				return Juego.lanzarDados(20);
			case Juego.CTXT_BMDO:
				return 2;
			default: return 0;
		}
	}

}
