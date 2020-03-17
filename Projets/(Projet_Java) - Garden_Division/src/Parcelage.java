package src;
import api_jardin.Parcelle;
import api_jardin.Orientation;
import api_jardin.FamilleLegume;
import api_jardin.ActionLegumeType;
import api_jardin.ActionSolType;
import javax.swing.*;
import javax.swing.JComboBox;
import javax.swing.border.*;
import java.awt.*;
import java.time.LocalDate;
import java.time.Month;

/** 
* La classe <code>Parcelage</code> permet d'effectuer,
* tout type d'actions sur une parcelle.
*/
public class Parcelage extends JPanel{
	private final JPanel container;
	private Parcelle first;
	JButton plan = new JButton("Planter");

	/** 
	* @see Parcelage#Parcelage(Parcelle parcelle)
	* est la m&eacute;thode prenant en param&egrave;tre
	* @param parcelle de type Parcelle,
	* est d&eacute;finissant les actions &agrave; appliquer sur celle-ci.
	*/
	public Parcelage(Parcelle parcelle){
		setLayout(new BorderLayout(0, 0));
		/* Chaque parcelle sur laquelle on agit est la première */
		first = parcelle;
		/* Représente l'espace d'édition des parcelles */
		container = new JPanel();
		container.setBackground(new Color(30,30,30));

		JPanel menu_1 = new JPanel(), menu_2 = new JPanel(), 
		terrain = new JPanel();
		terrain.setBackground(new Color(80,80,80));

		JButton absc = new JButton("Horizontal"), ordo  = new JButton("Vertical"),
		supp = new JButton("X"), zoom = new JButton("D\u00e9tail");
		/* Couleur de textes et de fonds des boutons */
		supp.setBackground(new Color(90,30,30)); 
		supp.setForeground(Color.WHITE);

		/* Menu comportant la possibilité de supprimer,
		ou d'afficher en détail une parcelle */
		menu_1.setBackground(new Color(60,60,60));
		menu_1.add(zoom); menu_1.add(supp);

		terrain.add(ordo); terrain.add(plan); terrain.add(absc);

		/* Controler d'action lors d'un clique sur bouton */
		Controler ctrl = new Controler(first, terrain);
		Controler ctrl2 = new Controler(first, menu_1);
		Controler ctrl3 = new Controler(first, container);

		supp.addActionListener(ctrl);
		zoom.addActionListener(ctrl3);

		absc.addActionListener(ctrl2);
		plan.addActionListener(ctrl);
		ordo.addActionListener(ctrl2);
		/* Menu comportant les sens de division, 
		et le fait de planter des légumes */
		menu_2.setLayout(new GridLayout(1,1));
		menu_2.add(terrain); 

		add(menu_2, BorderLayout.NORTH); 
		add(container, BorderLayout.CENTER);
	}

	/**
	* @see Parcelage#active()
	* est la m&eacute;thode permettant de d&eacute;finir une parcelle m&egrave;re,
	* le sens de division de celle-ci en parcelles filles par la m&eacute;thode :
	* @see ParcelleJ#SplitParcelle(Orientation o)
	* et la posistion de chacune avec les m&eacute;thode :
	* @see ParcelleJ#getFirst()
	* @see ParcelleJ#getSecond()
	* @see ParcelleJ#getSplit()
	*/
	public void active(){
		/* Rafraichissement sur la création de différentes parcelle */
		container.removeAll(); container.revalidate();
		/* Si le sens de division de la parcelle mère est vertical */
		if (first.getSplit() == Orientation.HORIZONTAL) {
			Parcelage sp1 = new Parcelage((Parcelle)first.getFirst()), 
			sp2 = new Parcelage((Parcelle)first.getSecond());
			/* Récursivité de l'action pour pouvoir l'appliquer,
			sur les sous-parcelles */
			sp1.active(); sp2.active();
			/* Ajustement visuel vertical */
			container.setLayout(new GridLayout(2,1));
			container.add(new JScrollPane(sp1));
			container.add(new JScrollPane(sp2));		
		/* Si le sens de division de la parcelle mère est horizontal */
		} else if (first.getSplit() == Orientation.VERTICAL){
			Parcelage sp1 = new Parcelage((Parcelle)first.getFirst()),
			sp2 = new Parcelage((Parcelle)first.getSecond());
			/* Récursivité de l'action pour pouvoir l'appliquer,
			sur les sous-parcelles */
			sp1.active(); sp2.active();
			/* Ajustement visuel horizontal */
			container.setLayout(new GridLayout(1,2));
			container.add(new JScrollPane(sp1));
			container.add(new JScrollPane(sp2));
		}
		revalidate();
		repaint();
	}

	/* Variables globales pour les récupérer les éléments de culture,
	sur une parcelle. */
	String nomLegume;
	Object familleLegume, semis, recolte, typeRecolte, culture;

	/** 
    * @see View#planter()
    * est la m&eacute;thode permettant l'action de travailler le sol,
    * pour une parcelle, et y planter des l&eacute;gumes.
	*/
	public void planter(){ 
		final JTextField no = new JTextField(); /* nom du légume */
		final JComboBox<FamilleLegume> tl = new JComboBox<>(FamilleLegume.values());
		final JComboBox<Month> se = new JComboBox<>(Month.values());
		final JComboBox<Month> re = new JComboBox<>(Month.values());
		final JComboBox<ActionSolType> so = new JComboBox<>(ActionSolType.values());
		final JComboBox<ActionLegumeType> tr = new JComboBox<>(ActionLegumeType.values());

		JPanel res = new JPanel();
		/* Caractéristique du légume à planter et actions sur le sol */
		res.add(new JLabel("* Date de modification : " + LocalDate.now() + " *"));
		res.add(new JLabel("Nom du l\u00e9gume")); res.add(no);
		res.add(new JLabel("Famille du l\u00e9gume")); res.add(tl);
		res.add(new JLabel("Semis du l\u00e9gume")); res.add(se);
		res.add(new JLabel("R\u00e9colte du l\u00e9gume")); res.add(re);
		res.add(new JLabel("Type de r\u00e9colte")); res.add(tr);
		res.add(new JLabel("Culture du sol")); res.add(so);
		/* Légume déjà planté sur la parcelle convernée */
		res.add(new JLabel("*** Plantation sur cette parcelle ***"));
		res.add(new JLabel("- Nom du l\u00e9gume : " + nomLegume));
		res.add(new JLabel("- Famille du l\u00e9gume : " + familleLegume));
		res.add(new JLabel("- Sem\u00e9 en : " + semis));
		res.add(new JLabel("- R\u00e9colte pr\u00e9vu pour : " + recolte));
		res.add(new JLabel("- Type de r\u00e9colte : " + typeRecolte));
		res.add(new JLabel("- Culture du sol : " + culture)); 
		res.setLayout(new GridLayout(20,1));

		/* Récupération des arguments */
		int message = JOptionPane.showConfirmDialog(null, res,
			"Plantation des cultures", JOptionPane.OK_CANCEL_OPTION);
		if((message == JOptionPane.OK_OPTION)){
			nomLegume = no.getText(); 
			familleLegume = tl.getSelectedItem(); 
			semis = se.getSelectedItem(); 
			recolte = re.getSelectedItem(); 
			typeRecolte = tr.getSelectedItem(); 
			culture = so.getSelectedItem();

			/* Evite de créer une chaine de caractère avec que des espaces. */
			String[] tab = nomLegume.split(" ");
			String verification = "";
			for (int i=0; i<tab.length; i++) {
				if(!tab[i].equals("")){ verification += tab[i]; }
			}
			verification = verification.trim();
			nomLegume = verification;

			/* S'il n'y a pas de contenu dans la chaine de caractère */
			if(nomLegume.length()==0){ nomLegume = "Aucun"; }
			
			/* Aspect de validation des paramètres donnés */
			else{
				plan.setBackground(new Color(50,100,50)); 
				plan.setForeground(Color.WHITE);
			}
		}
	}
}