package clase;

import juego.Juego;
import juego.Personaje;

public class Picaro extends Clase {

	public Picaro(juego.Personaje pers) {
		super(pers);
		crearClase();
	}

	public void ataque(Personaje opp) {
		int roll = pers.getRaza().habilidad(Juego.CTXT_ROLL);
		int dmg = Juego.lanzarDados(8) + pers.getRaza().getDex();
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
			System.out.println(pers.getNombre() +" avansa rapidamente con sus dagas y " +
								"va a la ofensiva! ("+ Integer.toString(roll) +")");
		}
		// Conclucion
		if(roll == 20) {
			System.out.println("Critico!"+ pers.getNombre() +" corta a "+ opp.getNombre() +
								" con sus dagas en puntos vitales! ("+ Integer.toString(dmg*2) +" de daño)");
			opp.setVida(opp.getVida() - dmg * 2);
		} else if(roll + pers.getRaza().habilidad(Juego.CTXT_BFAT) >= opp.getClase().getAC()) {
			System.out.println(pers.getNombre() +" corta a "+ opp.getNombre() +" con sus dagas! ("+
								Integer.toString(dmg) +" de daño)");
			opp.setVida(opp.getVida() - dmg);
		} else {
			System.out.println(pers.getNombre() +" falla por completo!");
		}
	}
	public void defender() {
		System.out.println(pers.getNombre() + " se prepara para esquivar.");
		pers.setDef(true);
	}
	
	protected void crearClase() {
		ac = 10;
		nombreClase = "Picaro";
	}

}
