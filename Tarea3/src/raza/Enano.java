package raza;

import juego.Juego;
import juego.Personaje;

public class Enano extends Raza {

	public Enano(Personaje pers) {
		super(pers);
		crearRaza();
	}

	protected void crearRaza() {
		mods[0] = 1;
		mods[2] = 2;
		nombreRaza = "Enano";
	}

	public int habilidad(int context) {
		switch(context) {
			case Juego.CTXT_ROLL:
				return Juego.lanzarDados(20);
			case Juego.CTXT_TURN:
				return 1;
			default: return 0;
		}
	}

}
