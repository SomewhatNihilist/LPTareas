package clase;

import juego.Juego;
import juego.Personaje;

public class Barbaro extends Clase {

	public Barbaro(juego.Personaje pers) {
		super(pers);
		crearClase();
	}

	public void ataque(Personaje opp) {
		int roll = pers.getRaza().habilidad(Juego.CTXT_ROLL);
		int dmg = Juego.lanzarDados(8) + pers.getRaza().getStr();
		// Ataque
		if(opp.getDef()) {
			// Desventaja
			int roll2 = pers.getRaza().habilidad(Juego.CTXT_ROLL);
			System.out.println(pers.getNombre() +" va a la ofensiva, pero "+ 
								opp.getNombre() +" trata de esquivarlo! ("+ 
								Integer.toString(roll) +", "+ Integer.toString(roll2) +")");
			roll = roll<roll2?roll:roll2;
		} else {
			// Normal
			System.out.println(pers.getNombre() +" levanta su masiva hacha y " +
								"va a la ofensiva! ("+ Integer.toString(roll) +")");
		}
		// Conclucion
		if(roll == 20) {
			System.out.println("Critico!"+ pers.getNombre() +" corta a "+ opp.getNombre() +
								" con su masiva hacha! ("+ Integer.toString(dmg*2) +" de daño)");
			opp.setVida(opp.getVida() - dmg * 2);
		} else if(roll + pers.getRaza().habilidad(Juego.CTXT_BFAT) >= opp.getClase().getAC()) {
			System.out.println(pers.getNombre() +" corta a "+ opp.getNombre() +" con su hacha! ("+
								Integer.toString(dmg) +" de daño)");
			opp.setVida(opp.getVida() - dmg);
		} else {
			System.out.println(pers.getNombre() +" falla por completo!");
		}
	}
	public void defender() {
		System.out.println(pers.getNombre() + " flexiona sus musculos en forma defensiva.");
		pers.setDef(true);
	}

	protected void crearClase() {
		/**Me imagino que se supone que uno usase esto para asignar variables de ac y
		 * otras relacionadas sobre un Personaje, pero eso es malo para la encapsulacion de valores y
		 * la extensibilidad del juego, aunque supongo que ya tiene bastantes cosas que 
		 * no hacen sentido (Personaje es una interfaz!) si se estuviese creando un juego de verdad...
		*/
		ac = 15;
		nombreClase = "Barbaro";
	}

}
