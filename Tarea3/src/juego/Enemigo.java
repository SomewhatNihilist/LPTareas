package juego;

public class Enemigo implements Personaje {

	String nombre;
	raza.Raza rz;
	clase.Clase cl;
	int vida;
	Boolean def; //Esta defendiendo esta ronda?

	public Enemigo(int raza, int clase, String nombre) {
		asignarRaza(raza);
		asignarClase(clase);
		asignarNombre(nombre);
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
		vida = 8 + rz.getCon();
	}

	public void asignarNombre(String name) {
		nombre = name;
	}

	public void printStatus() {
		System.out.println(nombre +", "+ rz.getNombreRaza() +" "+ cl.getNombreClase() +".");
		System.out.println("Tiene "+ Integer.toString(vida) +" de vida.");
	}

	public String getNombre() { return nombre; }
	public raza.Raza getRaza() { return rz; }
	public clase.Clase getClase() { return cl; }
	public int getVida() { return vida; }
	public void setVida(int num) { vida = num; }
	public Boolean getDef() { return def; }
	public void setDef(Boolean bool) { def = bool; }

	/**Ejecuta el turno del Enemigo. Hace una seleccion semi-aleatoria entre atacar o defender.
	 * @param opp Referencia al oponente con el que se enfrenta. */
	public void turno(Personaje opp) {
		setDef(false);
		vida += rz.habilidad(Juego.CTXT_TURN);
		// Si ataca o defiende, es aleatorio, con una tendencia mayor a defensa si tien poca vida.
		// Los NPCs forsaran la ofensiva cuando estan muy cerca de morir,
		//  excepto por el Enano, que puede regenerar su vida
		if(Juego.lanzarDados(vida) > 3 | (vida < 4 & !(rz instanceof raza.Enano))) {
			cl.ataque(opp);
		} else {
			cl.defender();
		}
	}
}
