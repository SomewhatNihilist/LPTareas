package clase;

import juego.Juego;
import juego.Personaje;

public class Mago extends Clase {

	public Mago(juego.Personaje pers) {
		super(pers);
		crearClase();
	}

	public void ataque(Personaje opp) {
		int roll = opp.getRaza().habilidad(Juego.CTXT_ROLL);
		int dmg = Juego.lanzarDados(6);
		// Ataque
		if(opp.getDef()) {
			// Desventaja
			int roll2 = opp.getRaza().habilidad(Juego.CTXT_ROLL);
			System.out.println(pers.getNombre() +" carga un hechizo ofensivo, pero "+ 
								opp.getNombre() +" trata de evadirlo! ("+ 
								Integer.toString(roll) +", "+ Integer.toString(roll2) +")");
			roll = roll>roll2?roll:roll2;
		} else {
			// Normal
			System.out.println(pers.getNombre() +" carga un hechizo ofensivo! (" + Integer.toString(roll) +")");
		}
		// Conclucion
		if(roll == 20) {
			System.out.println("Critico! "+ opp.getNombre() +" esquva completamente el firebolt de "+ 
								pers.getNombre() +"! (0 de daño)");
		} else if(roll + opp.getRaza().getDex() + opp.getRaza().habilidad(Juego.CTXT_BMDO) >= 13) {
			System.out.println(opp.getNombre() +" logra evitar lo peor del thunderwave de "+ pers.getNombre() +
								"! ("+ Integer.toString(dmg/2) +" de daño)");
			opp.setVida(opp.getVida() - dmg/2);
		} else {
			System.out.println(opp.getNombre() +" tropieza y es calzinado por el fireball de "+ pers.getNombre()+
								"! ("+ Integer.toString(dmg) +" de daño)");
			opp.setVida(opp.getVida() - dmg);
		}
	}
	public void defender() {
		System.out.println(pers.getNombre() + " prepara un hechizo defensivo.");
		pers.setDef(true);
	}
	
	protected void crearClase() {
		ac = 10;
		nombreClase = "Mago";
	}

}
