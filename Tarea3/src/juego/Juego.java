package juego;
import java.util.*;

public class Juego {
	public static Scanner s = new Scanner(System.in);
	static Random rand = new Random();
	//Constantes para contexto de habilidad
	public static final int CTXT_ROLL = 1; //Roll
	public static final int CTXT_TURN = 2; //Comienza turno
	public static final int CTXT_BFAT = 3; //Bonus ataque fisico
	public static final int CTXT_BMDO = 4; //Bonus evadir magia
	//Constantes de NPCs
	private static final int[][] NPCS_RACL = {{3,1},{2,2},{1,4},{2,3},{4,1},{1,3}};//{Race,Class}
	private static final String[] NPCS_NAME = {"Klrak", "Adran", "Isaac", "Elysium", "Krrogh", "Jenkins"};
	//(Klrak,enba)(Adran,elpi)(Isaac,hucl)(Elysium,elma)(Krrogh,orba)(Jenkins,huma)



	public static void main(String[] args) {

		System.out.println("\nBienvenido a Dunyons & Doragons");
		System.out.println("\n Despues de ser capturado durante tu gran aventura para salvar el mundo, "+
							"eres vendido como gladiador a un 'noble' del malvado pueblo H'Taederus, "+
							"famoso por sus torneos a muerte.");
		System.out.println(" El 'noble' te promete la libertad... pero solo si logras vencer en el torneo!");
		do {
			System.out.println(" Tres batallas consecutivas, sin apenas un descanso, esto no sera facil.");
	
			Jugador player = new Jugador();
			List<Enemigo> enemies = new ArrayList<Enemigo>(3);
			generarEnemigos(enemies);
			int winner = 0;
			for(int i = 0; i < enemies.size() & winner == 0; i++) {
				System.out.println("Las compuertas al otro lado del coliseo se abren, " + enemies.get(i).getNombre() + " entra a la arena.");
				player.setDef(false);
				winner = fightLoop(player, enemies.get(i));
				if(winner == 0) {
					System.out.println( enemies.get(i).getNombre() + " cae al piso, vecido, y el publico te aplaude!");
				}
			}
			if(winner == 1) {
				System.out.println("Caes al piso, sangre brotando de tus heridas, y a medida que sientes mundo alrededor tuyo desaparecer, un ultimo pensamiento pasa por tu mente \n'Talvez debi haberme quedado en la granja...'");
			} else {
				System.out.println("Finalmente, has sovevivido esta osadia, tal como se te prometio, te devuelven tu libertad, y aunque estes cansado y herido, te sientes mas habil y experienciado mientras caminas por el degradado pueblo, una sonrisa plasmada en tu rostro listo para tu siguiente aventura, hasta que te das cuenta... Te han robado todo tu equipamiento!");
			}
			System.out.println("Deseas jugar denuevo? (0/1) ");
		} while(readIntRange(0, 1, "(Solo un valor entre 0 y 1) ") == 1);
	}

	/**Intera una pelea entre p1 y p2 hasta que uno llegue a 0 de vida.
	 * @param p0 Personaje numero 0 que peleara.
	 * @param p1 Personaje numero 1 que peleara.
	 * @return Numero 0 o 1 correspondiente al ganador.
	 */
	public static int fightLoop(Personaje p0,Personaje p1) {		
		// Alternamos turn entre [0,1] para elegir personaje activo
		// Esto da mas flexibilidad (ej. Combate entre NPCs)
		Personaje[] actores = {p0, p1};
		int turn;
		// Roll initiative
		if(p0.getRaza().habilidad(CTXT_ROLL) + p0.getRaza().getDex() <
			p1.getRaza().habilidad(CTXT_ROLL) + p1.getRaza().getDex()) {
			turn = 1;
		} else {
			turn = 0;
		}
		System.out.println(actores[turn].getNombre() + " toma la iniciativa!");

		for(; actores[turn].getVida() > 0; turn = 1 - turn) {
			actores[turn].turno(actores[1-turn]);
		}
		return 1 - turn;
	}


	/**Lanza un dado de <code>dado</code> caras.
	 * @param dado Numero de caras del dado a lanzar.
	 * @return Un valor entero entre 1 y <code>dado</code>, inclusivo.
	 */
	public static int lanzarDados(int dado) {
		return rand.nextInt(dado) + 1;
	}

	/**Pide el ingreso de enteros hasta que se entre uno en el rango valido.
	 * @param min Minimo valor ingresable, inclusivo.
	 * @param max Maximo valor ingresable, inclusivo.
	 * @param errMsg Mensaje que se imprime cuando se hace una entrada fuera de rango.
	 * @return Numero valido ingresado.
	 */
	public static int readIntRange(int min, int max, String errMsg) {
		//min & max inclusive
		int val;
		while(true) {
			try {
				val = s.nextInt();
				if(val <= max && val >= min) {
					return val;
				} else {
					System.out.println(errMsg);
				}
			}
			catch (InputMismatchException ex) {
				System.out.println(errMsg);
			}
			finally {
				s.nextLine();
			}
		}
	}

	/**Rellena e con 3 enemigos. Adicionalmente, hace que las repeticiones sean <i>ligeramente</i> mas distinguibles ;)
	 * @param e lista de <code>Enemigo</code> ya inicializada.
	 */
	private static void generarEnemigos(List<Enemigo> e) {
		int opp;
		int[] repeats = {0,0,0,0,0,0};
		String oppName;
		for(int i = 0; i < 3; i++) {
			opp = rand.nextInt(6);
			oppName = NPCS_NAME[opp];
			repeats[opp]++;
			if(repeats[opp] == 2) {
				oppName = "el hermano gemelo de " + oppName;
			} else if(repeats[opp] == 3) {
				oppName = "el pseudo-medio-hermano-gemelo perdido de " + oppName;
			}
			e.add(new Enemigo(NPCS_RACL[opp][0], NPCS_RACL[opp][1], oppName));
		}
	}
}
