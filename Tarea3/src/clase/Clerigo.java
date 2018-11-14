package clase;

import juego.Juego;
import juego.Personaje;

public class Clerigo extends Clase {

	public Clerigo(juego.Personaje pers) {
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
			System.out.println(pers.getNombre() +" carga enegias divinas ofensivas, pero "+ 
								opp.getNombre() +" hace un gesto satanico para distraerlo! ("+ // Yeah, I know that's lame
								Integer.toString(roll) +", "+ Integer.toString(roll2) +")");
			roll = roll>roll2?roll:roll2;
		} else {
			// Normal
			System.out.println(pers.getNombre() +" carga enegias divinas ofensivas! (" + Integer.toString(roll) +")");
		}
		// Conclucion
		if(roll == 20) {
			System.out.println("Critico! "+ opp.getNombre() +" esquva completamente el pillar de luz producido por "+ 
								pers.getNombre() +"! (0 de daño)");
		} else if(roll + opp.getRaza().getCon() + opp.getRaza().habilidad(Juego.CTXT_BMDO) >= 13) {
			System.out.println(opp.getNombre() +" logra resistir lo peor del ataque mental por "+ pers.getNombre() +
								"! ("+ Integer.toString(dmg/2) +" de daño)");
			opp.setVida(opp.getVida() - dmg/2);
		} else {
			System.out.println(opp.getNombre() +" es calzinado por las flamas divinas de "+ pers.getNombre()+
								"! ("+ Integer.toString(dmg) +" de daño)");
			opp.setVida(opp.getVida() - dmg);
		}
	}
	public void defender() {
		System.out.println(pers.getNombre() + " reza por proteccion divina.");
		pers.setDef(true);
	}

	protected void crearClase() {
		ac = 15;
		nombreClase = "Clerigo";
	}
}
