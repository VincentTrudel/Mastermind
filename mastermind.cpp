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
	const int xZoneInteraction = 1; // Cette zone est utilis�e avec gotoxy() tant pour l'affichage de QUESTIONEVALUER que VICTOIRE ou D�FAITE, qui sont au m�me endroit
	const int xAffichageCodeSecret = 55;
	const int xDebutTableau = 8;
	const int xOptions = 8;
	const int xDifficult�s = 16;
	const int xColonneEssais = 13;
	const int xColonneBienPlac�s = 33;
	const int xColonneMalPlac�s = 50;
	const int yTitreDifficult� = 11;
	const int yZoneTitre = 1;
	const int yAvantD�butTableau = 9;
	const int yZoneReglages = 4;
	const int yQuestionDegogage = 7;
	const int yD�butant = 14;
	const int yInterm�diaire = 16;
	const int yExpert = 18;
	const int yChoixDifficult� = 21;
	const int yZoneInteraction = 23;
	const int yAffichageCodeSecret = 24;
	const int yEnsembleCouleurs = 5;
	const int yTitresColonnes = 8;
	
	const string QUESTIONDEBOGAGE = "Activer le mode en d\202bogage ? (O/N) : ";
	const string REGLAGES = "R\220GLAGES DE LA PARTIE";
	const string TITREJEUCOULEURS = "JEU DES COULEURS";
	const string QUESTIONEVALUER = "\220valuer ? (O/N) : ";
	const string CODESECRET = "Code Secret : ";
	const string COULEURSD�BUTANT = "(R)ouge , (V)ert , (B)leu , (J)aune , (M)auve";
	const string COULEURSINTERM�DIAIRE = "(R)ouge , (V)ert , (B)leu , (J)aune , (M)auve , (C)yan";
	const string COULEURSEXPERT = "(R)ouge , (V)ert , (B)leu , (J)aune , (M)auve , (C)yan , (G)ris";
	const string D�FAITE = "Vous avez perdu !  :(";
	const string VICTOIRE = "Bravo, vous avez gagn\202 !   :) ";
	const string TITRESCOLONNES = "#    Essais        Bien plac\202e(s)    Mal plac\202e(s)";
	const string PADDINGNUM = ")";
	const string CHOIXDIFFICULT� = "Choisir le niveau de difficult\202         ( Code, Couleurs, Essais )";
	const string D�BUTANT = "(D)\202butant                      ( 3 , 5 , 8  )";
	const string INTERM�DIAIRE = "(I)nterm\202diaire                 ( 4 , 6 , 10 )";
	const string EXPERT = "(E)xpert                        ( 5 , 7 , 12 )";
	const string QUESTIONCHOIX = "Choix = ";

	// VARIABLES

	char *couleursMalPlac�es;
	char *codeSecretReste;
	char *codeSecret;
	char *codeEssai;

	bool victoire = false;
	bool charValide;

	char couleurChar;
	char reponseDebogage;
	char reponseEvaluer;
	char reponseDifficult�;
	char charTap�;

	int position;
	int yAvantTableau;
	int yEssaiEnCours;
	int xAffichageNumEssai = xDebutTableau - 1;
	int couleurInt;
	int numEssai;
	int bienPlac�e;
	int malPlac�e;
	int longueurEspaceEffacer;
	int nbCouleurs;
	int longueurCode;
	int essaisMax;

	string ensembleCouleur;

	srand(time(NULL));

	// TRAITEMENT

	gotoxy(xZoneTitre, yZoneTitre);
	cout << TITREJEUCOULEURS; // Affichage des titres "JEU DES COULEURS" et "R�GLAGES DE LA PARTIE"
	gotoxy(xZoneReglages, yZoneReglages);
	cout << REGLAGES; // Affichage de "R\220GLAGES DE LA PARTIE"
	gotoxy(xDebutTableau, yQuestionDegogage);
	cout << QUESTIONDEBOGAGE; // Affichage de la question "Activer le mode en d\202bogage ? ( O/N ) : "

	do
	{
		reponseDebogage = _getch();
		reponseDebogage = toupper(reponseDebogage);
	} while (reponseDebogage != 'O' && reponseDebogage != 'N'); // Pour que l'utilisateur ne puisse taper que "o" ou "n" seulement

	gotoxy(xOptions, yTitreDifficult�);
	cout << CHOIXDIFFICULT�;
	gotoxy(xDifficult�s, yD�butant);
	cout << D�BUTANT;
	gotoxy(xDifficult�s, yInterm�diaire);
	cout << INTERM�DIAIRE;
	gotoxy(xDifficult�s, yExpert);
	cout << EXPERT;
	gotoxy(xDifficult�s, yChoixDifficult�);
	cout << QUESTIONCHOIX;

	do
	{
		reponseDifficult� = _getch();
		reponseDifficult� = toupper(reponseDifficult�);
	} while (reponseDifficult� != 'D' && reponseDifficult� != 'I' && reponseDifficult� != 'E');// Pour que l'utilisateur ne puisse taper que "d", "i" ou "e" seulement

	cout << reponseDifficult�;

	clrscr();

	switch (reponseDifficult�)
	{
	case 'D': 
		longueurCode = 3; // Pour chacune des difficult�s, on met chaque param�tre requis dans une variable
		nbCouleurs = 5;
		essaisMax = 8;
		ensembleCouleur = COULEURSD�BUTANT;
		break;
	case 'I':
		longueurCode = 4;
		nbCouleurs = 6;
		essaisMax = 10;
		ensembleCouleur = COULEURSINTERM�DIAIRE;
		break;
	case 'E':
		longueurCode = 5;
		nbCouleurs = 7;
		essaisMax = 12;
		ensembleCouleur = COULEURSEXPERT;
		break;
	}

	
	couleursMalPlac�es = new char[longueurCode]; // Ce tableau contient les couleurs qui n'ont pas �t� bien plac�es par le joueur;
	codeSecret = new char[longueurCode]; // Ce tableau contient le code secret pour gagner la partie
	codeSecretReste = new char[longueurCode]; // Ce tableau contiendra les couleurs du code secret qui restent apr�s que les couleurs bien blac�es aient �t� identifi�es
	codeEssai = new char[longueurCode]; // Ce tableau contiendra les couleurs entr�es � chaque essai

	for (int pos = 0; pos < longueurCode; pos++)
	{
		couleurInt = rand() % nbCouleurs; // Les couleurs du codeSecret sont g�n�r�es al�atoirement; on attribue la 
										  // premi�re lettre de chaque couleur possible � un chiffre, donc de 0 � nbCouleurs (-1, puisque l'on commence � 0, mais le rand fait la job tout seul).

		couleurChar = couleursValides[couleurInt]; // On assigne � la variable couleurChar la valeur de la couleur � l'index couleurInt (0-nbCouleurs) des couleursValides
												   // donc si couleurInt est 1, couleurChar='V', puisque couleursValide[1] = 'V'
		codeSecret[pos] = couleurChar;			// On assigne la valeur de couleurChar g�n�r�e al�atoirement au tableau codeSecret
		codeSecretReste[pos] = couleurChar; // On met cette m�me valeur dans un 2e tableau identique ( qui ne sera pas affich� ), 
	}										// il sert � savoir quelles couleurs sont mal plac�es plus loin dans le programme

	gotoxy(xZoneTitre, yZoneTitre);
	cout << TITREJEUCOULEURS;
	gotoxy(xDebutTableau, yEnsembleCouleurs);
	cout << ensembleCouleur;
	gotoxy(xDebutTableau, yTitresColonnes);
	cout << TITRESCOLONNES;
	
	for (int numEssai = 1; numEssai <= essaisMax; numEssai++) // Dans cette version, il faut afficher le num�ro des essais avant la boucle for princiale
	{
		if (numEssai < 10)
			gotoxy(xAffichageNumEssai, yAvantD�butTableau + numEssai);
		else
			gotoxy(xAffichageNumEssai - 1, yAvantD�butTableau + numEssai);// On tient compte que 10, 11,12,etc, sont un char plus
																		  // long que 9 et - et gotoxy() est ajust� en cons�quence.
		cout << numEssai << PADDINGNUM;
	}

	if (reponseDebogage == 'O') // Si la r�ponse est 'O', afficher le code secret
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
				codeSecretReste[pos] = codeSecret[pos]; // On remet les valeurs du tableau codeSecretReste � celles de codeSecret si on a d�j� fait un essai et
														// qu'il y a des valeurs dans le tableau codeSecretReste, pour pas que les couleurs des essais d'avant n'interf�rent.


		gotoxy(xColonneEssais, yAvantD�butTableau + numEssai);
		yAvantTableau = yTitresColonnes + 1; // yAvantTableau sert � afficher le num�ro de l'essai sur sa ligne respective,
		yEssaiEnCours = yAvantTableau + numEssai; // en faisant gotoxy(x, yAvantTableau + numEssai)

		position = 0;

		while (position < longueurCode )
		{
			do 
			{
				charTap� = _getch();
				charTap� = toupper(charTap�);
				charValide = false;
				for (int i = 0; i < nbCouleurs; i++)
				{										// Ici, on v�rifie si le charact�re tap� est une des couleurs possible ou un retour en arri�re ('\b'),
					if (charTap� == couleursValides[i]) // et un do-while emp�che l'utilisateur de continuer tant qu'un de ces charact�res n'est pas tap�
						charValide = true;				// Si le char tap� est dans couleursValides, alors charValide devient true et le programme continue
				}
				if (charTap� == '\b')
					charValide = true;
			} while (!charValide);

			if (charTap� == '\b') // Si le char tap� est un retour en arri�re
			{
				if (position > 0) // Et qu'on n'est pas � la position z�ro (pour �viter que l'utilisateur puisse reculer plus loin que la premi�re lettre),
				{			// on affiche deux retours en arri�re (l'espace, puis la lettre), un espace qui remplace la lettre et un retour arri�re qui nous ram�ne
					cout << "\b\b \b"; // o� la lettre qu'on vient d'effacer �tait
					codeEssai[position - 1] = '0'; // On remet la valeur de la lettre dans l'essai � autre chose qu'une lettre valide, puisque sinon la saisie de la lettre
					position--;					  // serait saut�e, puisqu'elle serait d�j� l� et valide, et on revient en arri�re dans la boucle, puisqu'on recommence � la position de la lettre qu'on vient d'effacer
				}
			}

			else // si la lettre est valide et pas '\b'
			{
				codeEssai[position] = charTap�; // on affecte la lettre tap�e et au tableau codeEssai � l'index correspondant � sa position
				cout << codeEssai[position] << " "; // et on l'affiche
				position++; // Comme la lettre est affich�e, nous sommes une position plus loin
			}
		}

		gotoxy(xZoneInteraction, yZoneInteraction);
		cout << QUESTIONEVALUER << " \b"; // le cout ici sert � effacer la lettre pr�sente apr�s "Choix: " si on r�pond non apr�s l'essai, de sorte que 
											// la prochaine fois que la question sera affich�e, la lettre de la r�ponse d'avant ne soit pas encore l�.
		do {
			reponseEvaluer = _getch();
			reponseEvaluer = toupper(reponseEvaluer);
		} while (reponseEvaluer != 'O' && reponseEvaluer != 'N');

		cout << reponseEvaluer;

		bienPlac�e = 0; // On initialise les variables bienPlac�e et malPlac�e ici, puisqu'on leur attribue une valeur dans la boucle qui suit
		malPlac�e = 0;

		longueurEspaceEffacer = longueurCode * 2; // Cette variable sert � effacer les charact�res de l'essai lorsque le joueur veut annuler son essai en r�pondant 'N' �
												  // la question de l'�valuation de sa r�ponse. Il faut faire longueurCode*2 parce qu'on affiche un espace apr�s chaque couleur de l'essai, ce qui double la longueur du code.
		if (reponseEvaluer == 'O')
		{
			for (int i = 0; i < longueurCode; i++) // Pour qu'une couleur de l'essai soit bien plac�e, il faut que la couleur pour une certaine position soit identique � celle du codeSecret
			{
				if (codeEssai[i] == codeSecret[i]) // pour la m�me position. On compare donc chaque lettre de l'essai avec celles du code pour chaque lettre du code
				{
					bienPlac�e++;
					couleursMalPlac�es[i] = marqueurX; // Nous avons besoin de savoir quelles couleurs restent dans le code secret et celles qui ont �t� trouv�es, pour
					codeSecretReste[i] = marqueurX; // ensuite voir si ces couleurs restantes sont dans l'essai, mais mal plac�es. Donc j'ai marqu� les couleurs utilis�es par un 'X'
				} // dans codeSecretReste, celles bien plac�es par un 'X' aussi dans couleursMalPlac�es.
				else
					couleursMalPlac�es[i] = codeEssai[i]; // Et si la couleur n'a pas �t� bien plac�e, on la note aussi, dans couleursMalPlac�es, par sa lettre cette fois ('J', 'B', etc)
			}
			for (int i = 0; i < longueurCode; i++) 
			{
				if (couleursMalPlac�es[i] != marqueurX) // Il reste a savoir quelles couleurs parmi les mal plac�es sont dans le code secret, donc pour chaque couleur
					for (int j = 0; j <= longueurCode; j++)// mal plac�e, si la couleur n'est pas 'X' (qui signifie bien plac�e, voir ligne 275)
						if (codeSecretReste[j] == couleursMalPlac�es[i]) // Si cette couleur est dans le reste du codeSecret,
						{
							malPlac�e += 1;  // La couleur est bonne donc elle a mal �t� plac�e
							codeSecretReste[j] = marqueurX; // Et on doit l'enlever du reste du Code secret pour pas qu'elle ne soit compt�e deux fois dans le m�me essai.
							break;
						}
			}
			gotoxy(xColonneBienPlac�s, yEssaiEnCours); 
			cout << bienPlac�e;
			gotoxy(xColonneMalPlac�s, yEssaiEnCours);
			cout << malPlac�e;

			if (bienPlac�e == longueurCode)
				victoire = true;
			else
				numEssai++; // Si le joueur fait �valuer sa r�ponse et qu'elle est mauvaise, il perd un essai, on passe donc, par exemple, de l'essai un � l'essai deux, d'ou numEssai++
		}
		else // Si r�ponseEvaluer est 'N', il faut aller avant la premi�re lettre de l'essai affich� et afficher 
		{	// une boite de la longueur du code (d�pendant du mode choisi et d�finie ligne 268)
			gotoxy(xColonneEssais, yEssaiEnCours);
			cout << setw(longueurEspaceEffacer) << ESPACE; // On remplit cette boite avec un char vide '' pour effacer l'essai annul�
			gotoxy(xColonneEssais, yEssaiEnCours);
		}
	}

	delete couleursMalPlac�es; // Il faut ici d�truire tous les espaces m�moires utilis�s par les tableaux cr��s de fa�on dynamique, sinon cela ne va se faire
	delete codeSecret;			// qu'� la fin du programme, ce qui cause des leaks de m�moire.
	delete codeSecretReste;
	delete codeEssai;

	gotoxy(xZoneInteraction, yZoneInteraction);

	if (victoire)
		cout << VICTOIRE; // self-explanatory, mais on peut souligner que le programme sortira de la boucle un jour ou l'autre, soit en d�passant le nombre d'essais allou�, cas auquel victoire sera �gal � false
	else
		cout << D�FAITE;

	_getch();

}