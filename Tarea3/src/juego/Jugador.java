package juego;

public class Jugador implements Personaje {

	private String nombre;
	private raza.Raza rz;
	private clase.Clase cl;
	private int vida;
	private Boolean def; //Esta defendiendo esta ronda?

	public Jugador() {
		System.out.println("De que raza eres?\n1.-Humano:1/1/1,Suerte\n2.-Elfo:0/2/1,Evacion\n3.-Enano:1/0/2,Resistencia\n4.-Orco:2/0/1,Atacante\n(1-4) ");
		asignarRaza(Juego.readIntRange(1, 4, "(Solo un valor del 1 al 4) "));
		System.out.println("Cual es tu profesion?\n1.-Barbaro: Fisico/Fuerza, AC 15\n2.-Picaro: Fisico/Destreza, AC 10\n3.-Mago: Magico/Destreza, AC 10\n4.-Clerigo: Magico/Constitucion, AC 15\n(1-4) ");
		asignarClase(Juego.readIntRange(1, 4, "(Solo un valor del 1 al 4) "));
		System.out.println("Cual es tu nombre? ");
		asignarNombre(Juego.s.nextLine());
		asignarVida();
		def = false;
	}

	public void asignarRaza(int raza) {
		switch(raza) {
			case 1: rz = new raza.Humano(this); break;
			case 2: rz = new raza.Elfo(this); break;
			case 3: rz = new raza.Enano(this); break;
			case 4: rz = new raza.Orco(this); break;
		}
	}

	public void asignarClase(int clase) {
		switch(clase) {
			case 1: cl = new clase.Barbaro(this); break;
			case 2: cl = new clase.Picaro(this); break;
			case 3: cl = new clase.Mago(this); break;
			case 4: cl = new clase.Clerigo(this); break;
		}
	}

	public void asignarVida() {
		vida = 10 + rz.getCon();
	}

	public void asignarNombre(String name) {
		nombre = name;
	}
	
	public void printStatus() {
		System.out.println(nombre +", "+ rz.getNombreRaza() +" "+ cl.getNombreClase() +".");
		System.out.println("Tienes "+ Integer.toString(vida) +" de vida.");
	}
	
	public String getNombre() { return nombre; }
	public raza.Raza getRaza() { return rz; }
	public clase.Clase getClase() { return cl; }
	public int getVida() { return vida; }
	public void setVida(int num) { vida = num; }
	public Boolean getDef() { return def; }
	public void setDef(Boolean bool) { def = bool; }

	public void turno(Personaje opp) {
		setDef(false);
		vida += rz.habilidad(Juego.CTXT_TURN);
		System.out.println("Elige tu accion:\n1.-Atacar\n2.-Defender\n3.-Observar\n4.-Contemplar ");
		int inp;
		do {
			inp = Juego.readIntRange(1, 4, "(Solo un valor entre 1, 2, 3 y 4) ");
			if(inp == 1) {
				cl.ataque(opp);
			} else if(inp == 2) {
				cl.defender();
			} else if(inp == 3) {
				System.out.println("Consideras la situacion:");
				System.out.println("  Te observas a ti mismo: ");
				printStatus();
				System.out.println("  Observas tu oponente: ");
				opp.printStatus();
			} else {
				String[] junk = {"el cielo.", "el numero 42.", "la vida.",
						"la compleja cadena de eventos que ha llevado hasta este momento.",
						"el hecho de que te has detenido en mitad de combate.",
						"las motivaciones del tus captores.", "si realmente deberias salvar el mundo.",
						"la moralidad de matar a otros para salvarte a ti mismo.", 
						"la inmortalidad del cangrejo.", "que dia es hoy.", 
						"que estabas respirando inconcientemente hasta que pensaste en ello.",
						"nada."};
				System.out.println("Decides detenerte por exactamente 6 segundos a contemplar " + junk[Juego.rand.nextInt(12)]);
			}
		} while(inp == 3);
	}

}
