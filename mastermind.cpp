/*

Auteur		: Vincent Trudel
Description	: TP8
Version		: 1.0

*/

#include <iostream>  // pour le cout
#include <conio.h>   // pour le _getch()
#include <iomanip>   // pour le cadrage
#include <string>    // pour les strings
#include "cvm.h"

using namespace std;

void main()
{
	// CONSTANTES

	const char marqueurX = 'X';
	const char ESPACE = ' ';
	const char couleursValides[7] = { 'R', 'V', 'B', 'J', 'M', 'C', 'G' };

	const int xZoneTitre = 32;
	const int xZoneReglages = 29;
	const int xZoneInteraction = 1; // Cette zone est utilisée avec gotoxy() tant pour l'affichage de QUESTIONEVALUER que VICTOIRE ou DÉFAITE, qui sont au même endroit
	const int xAffichageCodeSecret = 55;
	const int xDebutTableau = 8;
	const int xOptions = 8;
	const int xDifficultés = 16;
	const int xColonneEssais = 13;
	const int xColonneBienPlacés = 33;
	const int xColonneMalPlacés = 50;
	const int yTitreDifficulté = 11;
	const int yZoneTitre = 1;
	const int yAvantDébutTableau = 9;
	const int yZoneReglages = 4;
	const int yQuestionDegogage = 7;
	const int yDébutant = 14;
	const int yIntermédiaire = 16;
	const int yExpert = 18;
	const int yChoixDifficulté = 21;
	const int yZoneInteraction = 23;
	const int yAffichageCodeSecret = 24;
	const int yEnsembleCouleurs = 5;
	const int yTitresColonnes = 8;
	
	const string QUESTIONDEBOGAGE = "Activer le mode en d\202bogage ? (O/N) : ";
	const string REGLAGES = "R\220GLAGES DE LA PARTIE";
	const string TITREJEUCOULEURS = "JEU DES COULEURS";
	const string QUESTIONEVALUER = "\220valuer ? (O/N) : ";
	const string CODESECRET = "Code Secret : ";
	const string COULEURSDÉBUTANT = "(R)ouge , (V)ert , (B)leu , (J)aune , (M)auve";
	const string COULEURSINTERMÉDIAIRE = "(R)ouge , (V)ert , (B)leu , (J)aune , (M)auve , (C)yan";
	const string COULEURSEXPERT = "(R)ouge , (V)ert , (B)leu , (J)aune , (M)auve , (C)yan , (G)ris";
	const string DÉFAITE = "Vous avez perdu !  :(";
	const string VICTOIRE = "Bravo, vous avez gagn\202 !   :) ";
	const string TITRESCOLONNES = "#    Essais        Bien plac\202e(s)    Mal plac\202e(s)";
	const string PADDINGNUM = ")";
	const string CHOIXDIFFICULTÉ = "Choisir le niveau de difficult\202         ( Code, Couleurs, Essais )";
	const string DÉBUTANT = "(D)\202butant                      ( 3 , 5 , 8  )";
	const string INTERMÉDIAIRE = "(I)nterm\202diaire                 ( 4 , 6 , 10 )";
	const string EXPERT = "(E)xpert                        ( 5 , 7 , 12 )";
	const string QUESTIONCHOIX = "Choix = ";

	// VARIABLES

	char *couleursMalPlacées;
	char *codeSecretReste;
	char *codeSecret;
	char *codeEssai;

	bool victoire = false;
	bool charValide;

	char couleurChar;
	char reponseDebogage;
	char reponseEvaluer;
	char reponseDifficulté;
	char charTapé;

	int position;
	int yAvantTableau;
	int yEssaiEnCours;
	int xAffichageNumEssai = xDebutTableau - 1;
	int couleurInt;
	int numEssai;
	int bienPlacée;
	int malPlacée;
	int longueurEspaceEffacer;
	int nbCouleurs;
	int longueurCode;
	int essaisMax;

	string ensembleCouleur;

	srand(time(NULL));

	// TRAITEMENT

	gotoxy(xZoneTitre, yZoneTitre);
	cout << TITREJEUCOULEURS; // Affichage des titres "JEU DES COULEURS" et "RÉGLAGES DE LA PARTIE"
	gotoxy(xZoneReglages, yZoneReglages);
	cout << REGLAGES; // Affichage de "R\220GLAGES DE LA PARTIE"
	gotoxy(xDebutTableau, yQuestionDegogage);
	cout << QUESTIONDEBOGAGE; // Affichage de la question "Activer le mode en d\202bogage ? ( O/N ) : "

	do
	{
		reponseDebogage = _getch();
		reponseDebogage = toupper(reponseDebogage);
	} while (reponseDebogage != 'O' && reponseDebogage != 'N'); // Pour que l'utilisateur ne puisse taper que "o" ou "n" seulement

	gotoxy(xOptions, yTitreDifficulté);
	cout << CHOIXDIFFICULTÉ;
	gotoxy(xDifficultés, yDébutant);
	cout << DÉBUTANT;
	gotoxy(xDifficultés, yIntermédiaire);
	cout << INTERMÉDIAIRE;
	gotoxy(xDifficultés, yExpert);
	cout << EXPERT;
	gotoxy(xDifficultés, yChoixDifficulté);
	cout << QUESTIONCHOIX;

	do
	{
		reponseDifficulté = _getch();
		reponseDifficulté = toupper(reponseDifficulté);
	} while (reponseDifficulté != 'D' && reponseDifficulté != 'I' && reponseDifficulté != 'E');// Pour que l'utilisateur ne puisse taper que "d", "i" ou "e" seulement

	cout << reponseDifficulté;

	clrscr();

	switch (reponseDifficulté)
	{
	case 'D': 
		longueurCode = 3; // Pour chacune des difficultés, on met chaque paramètre requis dans une variable
		nbCouleurs = 5;
		essaisMax = 8;
		ensembleCouleur = COULEURSDÉBUTANT;
		break;
	case 'I':
		longueurCode = 4;
		nbCouleurs = 6;
		essaisMax = 10;
		ensembleCouleur = COULEURSINTERMÉDIAIRE;
		break;
	case 'E':
		longueurCode = 5;
		nbCouleurs = 7;
		essaisMax = 12;
		ensembleCouleur = COULEURSEXPERT;
		break;
	}

	
	couleursMalPlacées = new char[longueurCode]; // Ce tableau contient les couleurs qui n'ont pas été bien placées par le joueur;
	codeSecret = new char[longueurCode]; // Ce tableau contient le code secret pour gagner la partie
	codeSecretReste = new char[longueurCode]; // Ce tableau contiendra les couleurs du code secret qui restent après que les couleurs bien blacées aient été identifiées
	codeEssai = new char[longueurCode]; // Ce tableau contiendra les couleurs entrées à chaque essai

	for (int pos = 0; pos < longueurCode; pos++)
	{
		couleurInt = rand() % nbCouleurs; // Les couleurs du codeSecret sont générées aléatoirement; on attribue la 
										  // première lettre de chaque couleur possible à un chiffre, donc de 0 à nbCouleurs (-1, puisque l'on commence à 0, mais le rand fait la job tout seul).

		couleurChar = couleursValides[couleurInt]; // On assigne à la variable couleurChar la valeur de la couleur à l'index couleurInt (0-nbCouleurs) des couleursValides
												   // donc si couleurInt est 1, couleurChar='V', puisque couleursValide[1] = 'V'
		codeSecret[pos] = couleurChar;			// On assigne la valeur de couleurChar générée aléatoirement au tableau codeSecret
		codeSecretReste[pos] = couleurChar; // On met cette même valeur dans un 2e tableau identique ( qui ne sera pas affiché ), 
	}										// il sert à savoir quelles couleurs sont mal placées plus loin dans le programme

	gotoxy(xZoneTitre, yZoneTitre);
	cout << TITREJEUCOULEURS;
	gotoxy(xDebutTableau, yEnsembleCouleurs);
	cout << ensembleCouleur;
	gotoxy(xDebutTableau, yTitresColonnes);
	cout << TITRESCOLONNES;
	
	for (int numEssai = 1; numEssai <= essaisMax; numEssai++) // Dans cette version, il faut afficher le numéro des essais avant la boucle for princiale
	{
		if (numEssai < 10)
			gotoxy(xAffichageNumEssai, yAvantDébutTableau + numEssai);
		else
			gotoxy(xAffichageNumEssai - 1, yAvantDébutTableau + numEssai);// On tient compte que 10, 11,12,etc, sont un char plus
																		  // long que 9 et - et gotoxy() est ajusté en conséquence.
		cout << numEssai << PADDINGNUM;
	}

	if (reponseDebogage == 'O') // Si la réponse est 'O', afficher le code secret
	{
		gotoxy(xAffichageCodeSecret, yAffichageCodeSecret);
		cout << CODESECRET;
		for (int pos = 0; pos < longueurCode; pos++)
			cout << codeSecret[pos] << " ";
	}

	numEssai = 1;

	while (numEssai <= essaisMax)
	{
		if (victoire) break;


		if (numEssai > 1)
			for (int pos = 0; pos < longueurCode; pos++)
				codeSecretReste[pos] = codeSecret[pos]; // On remet les valeurs du tableau codeSecretReste à celles de codeSecret si on a déjà fait un essai et
														// qu'il y a des valeurs dans le tableau codeSecretReste, pour pas que les couleurs des essais d'avant n'interfèrent.


		gotoxy(xColonneEssais, yAvantDébutTableau + numEssai);
		yAvantTableau = yTitresColonnes + 1; // yAvantTableau sert à afficher le numéro de l'essai sur sa ligne respective,
		yEssaiEnCours = yAvantTableau + numEssai; // en faisant gotoxy(x, yAvantTableau + numEssai)

		position = 0;

		while (position < longueurCode )
		{
			do 
			{
				charTapé = _getch();
				charTapé = toupper(charTapé);
				charValide = false;
				for (int i = 0; i < nbCouleurs; i++)
				{										// Ici, on vérifie si le charactère tapé est une des couleurs possible ou un retour en arrière ('\b'),
					if (charTapé == couleursValides[i]) // et un do-while empêche l'utilisateur de continuer tant qu'un de ces charactères n'est pas tapé
						charValide = true;				// Si le char tapé est dans couleursValides, alors charValide devient true et le programme continue
				}
				if (charTapé == '\b')
					charValide = true;
			} while (!charValide);

			if (charTapé == '\b') // Si le char tapé est un retour en arrière
			{
				if (position > 0) // Et qu'on n'est pas à la position zéro (pour éviter que l'utilisateur puisse reculer plus loin que la première lettre),
				{			// on affiche deux retours en arrière (l'espace, puis la lettre), un espace qui remplace la lettre et un retour arrière qui nous ramène
					cout << "\b\b \b"; // où la lettre qu'on vient d'effacer était
					codeEssai[position - 1] = '0'; // On remet la valeur de la lettre dans l'essai à autre chose qu'une lettre valide, puisque sinon la saisie de la lettre
					position--;					  // serait sautée, puisqu'elle serait déjà là et valide, et on revient en arrière dans la boucle, puisqu'on recommence à la position de la lettre qu'on vient d'effacer
				}
			}

			else // si la lettre est valide et pas '\b'
			{
				codeEssai[position] = charTapé; // on affecte la lettre tapée et au tableau codeEssai à l'index correspondant à sa position
				cout << codeEssai[position] << " "; // et on l'affiche
				position++; // Comme la lettre est affichée, nous sommes une position plus loin
			}
		}

		gotoxy(xZoneInteraction, yZoneInteraction);
		cout << QUESTIONEVALUER << " \b"; // le cout ici sert à effacer la lettre présente après "Choix: " si on répond non après l'essai, de sorte que 
											// la prochaine fois que la question sera affichée, la lettre de la réponse d'avant ne soit pas encore là.
		do {
			reponseEvaluer = _getch();
			reponseEvaluer = toupper(reponseEvaluer);
		} while (reponseEvaluer != 'O' && reponseEvaluer != 'N');

		cout << reponseEvaluer;

		bienPlacée = 0; // On initialise les variables bienPlacée et malPlacée ici, puisqu'on leur attribue une valeur dans la boucle qui suit
		malPlacée = 0;

		longueurEspaceEffacer = longueurCode * 2; // Cette variable sert à effacer les charactères de l'essai lorsque le joueur veut annuler son essai en répondant 'N' à
												  // la question de l'évaluation de sa réponse. Il faut faire longueurCode*2 parce qu'on affiche un espace après chaque couleur de l'essai, ce qui double la longueur du code.
		if (reponseEvaluer == 'O')
		{
			for (int i = 0; i < longueurCode; i++) // Pour qu'une couleur de l'essai soit bien placée, il faut que la couleur pour une certaine position soit identique à celle du codeSecret
			{
				if (codeEssai[i] == codeSecret[i]) // pour la même position. On compare donc chaque lettre de l'essai avec celles du code pour chaque lettre du code
				{
					bienPlacée++;
					couleursMalPlacées[i] = marqueurX; // Nous avons besoin de savoir quelles couleurs restent dans le code secret et celles qui ont été trouvées, pour
					codeSecretReste[i] = marqueurX; // ensuite voir si ces couleurs restantes sont dans l'essai, mais mal placées. Donc j'ai marqué les couleurs utilisées par un 'X'
				} // dans codeSecretReste, celles bien placées par un 'X' aussi dans couleursMalPlacées.
				else
					couleursMalPlacées[i] = codeEssai[i]; // Et si la couleur n'a pas été bien placée, on la note aussi, dans couleursMalPlacées, par sa lettre cette fois ('J', 'B', etc)
			}
			for (int i = 0; i < longueurCode; i++) 
			{
				if (couleursMalPlacées[i] != marqueurX) // Il reste a savoir quelles couleurs parmi les mal placées sont dans le code secret, donc pour chaque couleur
					for (int j = 0; j <= longueurCode; j++)// mal placée, si la couleur n'est pas 'X' (qui signifie bien placée, voir ligne 275)
						if (codeSecretReste[j] == couleursMalPlacées[i]) // Si cette couleur est dans le reste du codeSecret,
						{
							malPlacée += 1;  // La couleur est bonne donc elle a mal été placée
							codeSecretReste[j] = marqueurX; // Et on doit l'enlever du reste du Code secret pour pas qu'elle ne soit comptée deux fois dans le même essai.
							break;
						}
			}
			gotoxy(xColonneBienPlacés, yEssaiEnCours); 
			cout << bienPlacée;
			gotoxy(xColonneMalPlacés, yEssaiEnCours);
			cout << malPlacée;

			if (bienPlacée == longueurCode)
				victoire = true;
			else
				numEssai++; // Si le joueur fait évaluer sa réponse et qu'elle est mauvaise, il perd un essai, on passe donc, par exemple, de l'essai un à l'essai deux, d'ou numEssai++
		}
		else // Si réponseEvaluer est 'N', il faut aller avant la première lettre de l'essai affiché et afficher 
		{	// une boite de la longueur du code (dépendant du mode choisi et définie ligne 268)
			gotoxy(xColonneEssais, yEssaiEnCours);
			cout << setw(longueurEspaceEffacer) << ESPACE; // On remplit cette boite avec un char vide '' pour effacer l'essai annulé
			gotoxy(xColonneEssais, yEssaiEnCours);
		}
	}

	delete couleursMalPlacées; // Il faut ici détruire tous les espaces mémoires utilisés par les tableaux créés de façon dynamique, sinon cela ne va se faire
	delete codeSecret;			// qu'à la fin du programme, ce qui cause des leaks de mémoire.
	delete codeSecretReste;
	delete codeEssai;

	gotoxy(xZoneInteraction, yZoneInteraction);

	if (victoire)
		cout << VICTOIRE; // self-explanatory, mais on peut souligner que le programme sortira de la boucle un jour ou l'autre, soit en dépassant le nombre d'essais alloué, cas auquel victoire sera égal à false
	else
		cout << DÉFAITE;

	_getch();

}