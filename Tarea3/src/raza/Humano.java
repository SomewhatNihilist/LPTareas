package raza;

import juego.Juego;
import juego.Personaje;

public class Humano extends Raza {

	public Humano(Personaje pers) {
		super(pers);
		crearRaza();
	}

	protected void crearRaza() {
		mods[0] = 1;
		mods[1] = 1;
		mods[2] = 1;
		nombreRaza = "Humano";
	}

	public int habilidad(int context) {
		int roll;
		switch(context) {
			case Juego.CTXT_ROLL:
				do {
					roll = Juego.lanzarDados(20);
				} while(roll == 1);
				return roll;
			default: return 0;
		}
	}

}
