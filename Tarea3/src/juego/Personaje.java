package juego;

public interface Personaje {
	//Este se beneficiaria bastante de ser un abstract class

	/**Inicializa la raza del Personaje.
	 * @param raza Raza del personaje a inicializar. (1:Humano, 2:Elfo, 3:Enano, 4:Orco)*/
	public void asignarRaza(int raza);
	/**Inicializa la clase del Personaje.
	 * @param clase Clase del personaje a inicializar. (1:Barbaro, 2:Picaro, 3:Mago, 4:Clerigo)*/
	public void asignarClase(int clase);
	/**Inicializa la vida del Personaje.
	 * tiene que usarse DESPUES de haber inicializado la raza */
	public void asignarVida();
	/**Inicializa el nombre del Personaje.
	 * @param name Nombre del personaje. */
	public void asignarNombre(String name);


	/**Ejecuta el turno del Personaje.
	 * @param opp Referencia al oponente con el que se enfrenta. */
	public void turno(Personaje opp);

	/**Imprime el nombre, raza, clase y vida del Personaje. */
	public void printStatus();

	public String getNombre();
	public raza.Raza getRaza();
	public clase.Clase getClase();
	public int getVida();
	public void setVida(int num);
	public Boolean getDef();
	public void setDef(Boolean bool);
}
