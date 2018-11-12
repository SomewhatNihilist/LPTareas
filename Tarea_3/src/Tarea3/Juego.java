package Tarea3;

import java.util.*;

public class Juego {

	public int lanzarDados(int dado) {

		Random rand = new Random();
		return rand.nextInt(dado) + 1;

	}

	public static void main(String[] args) {

		System.out.println("Bienvenido a Dunyons & Doragons");

		Jugador player_1 = new Jugador();

	}

}
