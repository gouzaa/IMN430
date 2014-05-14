//
//  abr.h
//  Arbre
//
//  Jean Goulet on 13-03-03.
//

//Nous avons utiliser un avl qui provient d'une implantation d'ift-339 session 2

#ifndef Arbre_abr_h
#define Arbre_abr_h

#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>
using namespace std;


////////////////////////////////////////////////////////
//
// Pour faire une autre sorte d'arbre, creer une class
// noeud avec sa propre representation, qui doit inclure
// les champs PARENT, CONTENU, GAUCHE, DROITE
// et tout autre champ d'interet 
//
// Seules les fonctions generatrices ont besoin d'etre
// specifiees, les autres demeurant les memes
//
// Ensuite, pour creer un arbre avec les noeudAVL,
//
//  template<typename TYPE>
//  class AVL: public abr<TYPE,noeudAVL>{};
//
////////////////////////////////////////////////////////

template <typename TYPE>
class noeud;

template <typename TYPE,typename N=noeud<TYPE> >
class abr;

template <typename TYPE>
class arbre: public abr<TYPE,noeud<TYPE> >{
public:
    using abr<TYPE,noeud<TYPE> >::operator=;
};

template <typename TYPE>
class noeudAVL;

template <typename TYPE>
class AVL: public abr<TYPE,noeudAVL<TYPE> >{

public:
    using abr<TYPE,noeudAVL<TYPE> >::operator=;
	
};


////////////////////////////////////////////////////////
// Noeud de base sans aucun equilibre
// la class specialisee: arbre<TYPE>
////////////////////////////////////////////////////////


////---------------------------------Noeuds AVL
template <typename TYPE>
class noeudAVL{
    friend class abr<TYPE,noeudAVL>;
    noeudAVL *PARENT;
    TYPE* CONTENU;
	int intINDICE;
    noeudAVL *GAUCHE,*DROITE;
	noeudAVL(noeudAVL* P=0,TYPE* C=0,int I=0,noeudAVL* G=0, noeudAVL* D=0);


    static bool insert(const TYPE&,noeudAVL<TYPE>*&,bool&);
	static bool ajouteGauche(const TYPE&, noeudAVL<TYPE>*&, bool&);
	static bool ajouteDroite(const TYPE&, noeudAVL<TYPE>*&, bool&);
	static void rotationGaucheDroite(noeudAVL<TYPE>*&);
	static void rotationDroiteGauche(noeudAVL<TYPE>*&);
    static bool erase(const TYPE&,bool&,noeudAVL<TYPE>*&);
	//static bool erase(const TYPE&,bool&,noeudAVL<TYPE>*&,noeudAVL<TYPE>*&);
	static bool enleveGauche(const TYPE&,noeudAVL<TYPE>*&, bool& );
	static bool enleveDroite(const TYPE&,noeudAVL<TYPE>*&, bool& );
	static TYPE MAX(noeudAVL<TYPE>*&);
	static TYPE MIN(noeudAVL<TYPE>*&);
    void afficher()const;
};

template <typename TYPE>
noeudAVL<TYPE>::noeudAVL(noeudAVL* P,TYPE* C,int I,noeudAVL* G, noeudAVL* D):
PARENT(P),CONTENU(C),intINDICE(I),GAUCHE(G),DROITE(D){}


template <typename TYPE>
bool noeudAVL<TYPE>::insert(const TYPE& c,noeudAVL<TYPE>*& p, bool& DEJA){
	 if(c==*p->CONTENU){return false;}
	
	//if(c==*p->CONTENU){return false;}

    if(c < *p->CONTENU){

		if(p->GAUCHE==0){
            p->GAUCHE=new noeudAVL(p,new TYPE(c));
			DEJA = false;
			ajouteGauche(c,p,DEJA);
			return true;}
        else if(p->GAUCHE->CONTENU==0){
            p->GAUCHE=p->GAUCHE->PARENT=new noeudAVL(p,new TYPE(c),0,p->GAUCHE);
			DEJA = false;
			ajouteGauche(c,p,DEJA);
			return true;}
        else{
			DEJA = true;
			ajouteGauche(c,p,DEJA);}

    }
    else{  // c > *p->CONTENU

        if(p->DROITE==0){
            p->DROITE=new noeudAVL(p,new TYPE(c));
			DEJA = false;
			ajouteDroite(c,p,DEJA);
			return true;}
        else if(p->DROITE->CONTENU==0){
            p->DROITE=p->DROITE->PARENT=new noeudAVL(p,new TYPE(c),0,p->DROITE);
			DEJA = false;
			ajouteDroite(c,p,DEJA);
			return true;}
        else{
			DEJA = true;
			ajouteDroite(c,p,DEJA);}
    }

}

template <typename TYPE>
TYPE noeudAVL<TYPE>::MAX(noeudAVL<TYPE>*& ndAvl)
{
	while(ndAvl->DROITE != 0)
	{
		ndAvl = ndAvl->DROITE;
	}

	return *ndAvl->PARENT->CONTENU;
}

template <typename TYPE>
TYPE noeudAVL<TYPE>::MIN(noeudAVL<TYPE>*& ndAvl)
{
	
	while(ndAvl->GAUCHE!=0)
	{
		ndAvl = ndAvl->GAUCHE;
	}
	return *ndAvl->PARENT->CONTENU;
}

template <typename TYPE>
void noeudAVL<TYPE>::afficher()const{
    //cout<<this<<":["<<PARENT<<","<<CONTENU<<","<<GAUCHE<<","<<DROITE<<", "<< intINDICE <<"] ";
	if(CONTENU!=0)cout<<*CONTENU<<" "<<intINDICE;
}

template <typename TYPE>
bool noeudAVL<TYPE>::ajouteGauche(const TYPE& c, noeudAVL<TYPE>*& p, bool& DEJA)
{
	if(insert(c,p->GAUCHE,DEJA))
	{
		if(++(p->intINDICE)==2)
		{
			if(p->GAUCHE->intINDICE==-1)rotationDroiteGauche(p->GAUCHE);
			rotationGaucheDroite(p);
		}
		return p->intINDICE!=0;
	}
	else
	{
		return false;
	}
}


template <typename TYPE>
bool noeudAVL<TYPE>::ajouteDroite(const TYPE& c, noeudAVL<TYPE>*& p, bool& DEJA)
{

	if(insert(c,p->DROITE,DEJA))
	{
		if(--(p->intINDICE)==-2)
		{
			if(p->DROITE->intINDICE==1)rotationGaucheDroite(p->DROITE);
			rotationDroiteGauche(p);
		}
		return p->intINDICE!=0;
	}
	else
	{
		return false;
	}
}


template <typename TYPE>
void noeudAVL<TYPE>::rotationGaucheDroite(noeudAVL<TYPE>*& p)
{
	noeudAVL<TYPE> *temp = p->GAUCHE;

	

	int ia = temp->intINDICE;
	int ib = p->intINDICE;
	int nib = -ia-max(0,-ia)-1+ib;
	int nia = ia-max(0,-nib)-1;
	temp->intINDICE = nib;
	p->intINDICE = nia;
	p->GAUCHE = temp->DROITE;

	temp->PARENT = p->PARENT;
	p->PARENT = temp;

	if(temp->DROITE)
	temp->DROITE->PARENT = p;

	temp->DROITE = p;
	p=temp;
	
}



template <typename TYPE>
void noeudAVL<TYPE>::rotationDroiteGauche(noeudAVL<TYPE>*& p)
{
	noeudAVL<TYPE> *temp = p->DROITE;
	int nib = temp->intINDICE;
	int nia = p->intINDICE;
	int ia = nia+max(0,-nib)+1;
	int ib = nib+ia+max(0,-ia)+1;
	temp->intINDICE = ib;
	p->intINDICE = ia;
	p->DROITE = temp->GAUCHE;

	temp->PARENT = p->PARENT;
	p->PARENT = temp;

	if(temp->GAUCHE)
	temp->GAUCHE->PARENT = p;

	temp->GAUCHE = p;
	p=temp;

}

template <typename TYPE>
bool noeudAVL<TYPE>::erase(const TYPE& c,bool& ABSENT,noeudAVL<TYPE>*& p){

	if(p==0 || p->CONTENU==0){return false;}

	if(c<*p->CONTENU)
		return enleveGauche(c,p,ABSENT);

	if(c>*p->CONTENU)
		return enleveDroite(c,p,ABSENT);

	if(p->GAUCHE!=0 && p->GAUCHE->CONTENU!=0)
	{
		*p->CONTENU = MAX(p->GAUCHE);
		p->GAUCHE->PARENT = p;
		ABSENT = false;
		return(enleveGauche(*p->CONTENU,p,ABSENT));
	}

	
	if(p->DROITE!=0 && p->DROITE->CONTENU!=0)
	{
		*p->CONTENU = MIN(p->DROITE);
		p->DROITE->PARENT = p;
		ABSENT = false;
		return(enleveDroite(*p->CONTENU,p,ABSENT));
	}

	delete p;
	p=0;
	ABSENT = false;
	return true;
   
    }



template <typename TYPE>
bool noeudAVL<TYPE>::enleveGauche(const TYPE& c,noeudAVL<TYPE>*& p, bool& ABSENT)
{
	if(erase(c,ABSENT,p->GAUCHE))
	{
		if(--(p->intINDICE)==-2)
		{
			if(p->DROITE->intINDICE==1)rotationGaucheDroite(p->DROITE);
			rotationDroiteGauche(p);
		}
		return(p->intINDICE==0);
	}
	return false;
}


template <typename TYPE>
bool noeudAVL<TYPE>::enleveDroite(const TYPE& c ,noeudAVL<TYPE>*& p, bool& ABSENT)
{
	if(erase(c,ABSENT,p->DROITE))
	{
		if(++(p->intINDICE)==2)
		{
			if(p->GAUCHE->intINDICE==-1)rotationDroiteGauche(p->GAUCHE);
			rotationGaucheDroite(p);
		}
		return(p->intINDICE==0);
	}
	return false;
}


// -------------------------------Noeud---------------------------

template <typename TYPE>
class noeud{
    friend class abr<TYPE,noeud>;
    noeud *PARENT;
    TYPE* CONTENU;
    noeud *GAUCHE,*DROITE;
    noeud(noeud* P=0,TYPE* C=0,noeud* G=0, noeud* D=0);
    static void insert(const TYPE&,noeud*&,bool&);
    static void erase(const TYPE&,bool&,noeud*& p);
    static void erase(const TYPE&,bool&,noeud*& p,noeud*& aR);
    void afficher()const;
};


template <typename TYPE>
noeud<TYPE>::noeud(noeud* P,TYPE* C,noeud* G, noeud* D):
PARENT(P),CONTENU(C),GAUCHE(G),DROITE(D){}



template <typename TYPE>
void noeud<TYPE>::insert(const TYPE& c,noeud*& p,bool& DEJA){
    if(c==*p->CONTENU){DEJA=true;return;}
    if(c < *p->CONTENU){
        if(p->GAUCHE==0)
            p->GAUCHE=new noeud(p,new TYPE(c));
        else if(p->GAUCHE->CONTENU==0)
            p->GAUCHE=p->GAUCHE->PARENT=new noeud(p,new TYPE(c),p->GAUCHE);
        else
            insert(c,p->GAUCHE,DEJA);
    }
    else{  // c > *p->CONTENU
        if(p->DROITE==0)
            p->DROITE=new noeud(p,new TYPE(c));
        else if(p->DROITE->CONTENU==0)
            p->DROITE=p->DROITE->PARENT=new noeud(p,new TYPE(c),0,p->DROITE);
        else
            insert(c,p->DROITE,DEJA);
    }
}

template <typename TYPE>
void noeud<TYPE>::erase(const TYPE& c,bool& ABSENT,noeud*& p){
    noeud<TYPE>* aRemplacer=0;
    erase(c,ABSENT,p,aRemplacer);
    }

template <typename TYPE>
void noeud<TYPE>::erase(const TYPE& c,bool& ABSENT,noeud*& p,noeud*& aRemplacer){
    //cout<<"erase("<<c<<","<<ABSENT<<","<<p<<","<<aRemplacer<<")"<<endl;
    
    if(p==0 || p->CONTENU==0)return;
    if(c==*p->CONTENU){
        delete p->CONTENU;
        aRemplacer=p;
        ABSENT=false;
        if(p->DROITE==0 || p->DROITE->CONTENU==0)
            erase(c,ABSENT,p->GAUCHE,aRemplacer);
        else
            erase(c,ABSENT,p->DROITE,aRemplacer);
        }
    else if(c<*p->CONTENU)
        erase(c,ABSENT,p->GAUCHE,aRemplacer);
    else
        erase(c,ABSENT,p->DROITE,aRemplacer);
    
    if(aRemplacer!=0){
        aRemplacer->CONTENU=p->CONTENU;
        aRemplacer=p;
        if(p->GAUCHE==0)p=p->DROITE;
        else p=p->GAUCHE;
        if(p!=0)p->PARENT=aRemplacer->PARENT;
        delete aRemplacer;
        aRemplacer=0;
        }            
}

template <typename TYPE>
void noeud<TYPE>::afficher()const{
    cout<<this<<":["<<PARENT<<","<<CONTENU<<","<<GAUCHE<<","<<DROITE<<"] ";
    if(CONTENU!=0)cout<<*CONTENU;
}



////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
//
// class abr  dont le fonctionnement
// depend de la class noeud passee
// comme deuxieme parametre
//
// Pour creer une nouvelle sorte d'arbre
// il n'y a normalement aucune modification
// a faire a cette classe
//
////////////////////////////////////////////////////////


template <typename TYPE,typename noeud >
class abr{
private:
    
    int SIZE;
    noeud* RACINE;
    mutable noeud AVANT,APRES;
    
    /////////////////////////////////////////////////
    //fonctions privees
    void clear(noeud*);
    void hauteur(noeud*,int,int&,int&)const;
    static void avancer(noeud*&);
    static void reculer(noeud*&);
    /////////////////////////////////////////////////
public:
    abr();
    ~abr();
    abr(const abr&);
    abr& operator=(const abr&);    
    
    class iterator{
    friend class abr<TYPE,noeud>;
    private:
        noeud* REP;
     public:
        iterator(noeud* =0);
        const TYPE& operator*()const;
        const iterator& operator++();   //++i
        const iterator& operator--();   //--i
        iterator operator++(int);       //i++
        iterator operator--(int);       //i--
        bool operator==(const iterator&)const;
        bool operator!=(const iterator&)const;
    };
    
    void insert(const TYPE&);
    void erase(const TYPE&);
    void erase(iterator);
    void clear();
    
    int size()const;
    bool empty()const;
    
    iterator begin()const;
    iterator end()const;
    iterator find(const TYPE&)const;
    
    //void afficher(noeud* =0,int=0)const;
	void afficher()const;
	void afficher_barres(vector<string>& barres,int n)const;
	void afficher(noeud* p,int niveau,vector<string>& barres)const;
    void hauteur()const;
};


/////////////////////////////////////////////////
//fonctions privees de la class abr

template <typename TYPE,typename noeud>
void abr<TYPE,noeud>::clear(noeud* p){
    if(p==0 || p->CONTENU==0)return;
    clear(p->GAUCHE);
    clear(p->DROITE);
    delete p;
    }

template <typename TYPE,typename noeud>
void abr<TYPE,noeud>::hauteur(noeud* p,int hauteur_noeud,int& nb_noeuds,int& total_hauteur)const{
    if(p==0 || p->CONTENU==0)return;
    ++nb_noeuds;
    total_hauteur+=hauteur_noeud;
    hauteur(p->GAUCHE,hauteur_noeud+1,nb_noeuds,total_hauteur);
    hauteur(p->DROITE,hauteur_noeud+1,nb_noeuds,total_hauteur);
}

template <typename TYPE,typename noeud>
void abr<TYPE,noeud>::avancer(noeud*& REP){
    //cout<<"avancer de "<<REP<<" a ";
    noeud* ENFANT;
    if(REP->DROITE!=0){
        REP=REP->DROITE;
        while(REP->GAUCHE!=0)REP=REP->GAUCHE;
    }
    else
        do{
            ENFANT=REP;
            REP=REP->PARENT;
        }while(REP->GAUCHE!=ENFANT);
    //cout<<REP<<endl;
}

template <typename TYPE,typename noeud>
void abr<TYPE,noeud>::reculer(noeud*& REP){
    //cout<<"reculer de "<<REP<<" ";
    noeud* ENFANT;
    if(REP->GAUCHE!=0){
        REP=REP->GAUCHE;
        while(REP->DROITE!=0)REP=REP->DROITE;
    }
    else
        do{
            ENFANT=REP;
            REP=REP->PARENT;
        }while(REP->DROITE!=ENFANT);
    //cout<<" a "<<REP<<endl;
}


/////////////////////////////////////////////////
// fonctions de base de la class abr

template <typename TYPE,typename noeud>
abr<TYPE,noeud>::abr():SIZE(0),RACINE(0){
    clear();
}

template <typename TYPE,typename noeud>
abr<TYPE,noeud>::~abr(){
    clear();
}

template <typename TYPE,typename noeud>
abr<TYPE,noeud>::abr(const abr& source):SIZE(0),RACINE(0){
    clear();
    *this=source;
}

template <typename TYPE,typename noeud>
abr<TYPE,noeud>& abr<TYPE,noeud>::operator=(const abr& source){
    iterator id,is;
    int i;
    while(SIZE>source.SIZE)erase(begin());
    for(i=0,id=begin(),is=source.begin();i<SIZE;++i,id++)
        *id.REP->CONTENU=*is++;
    for(;i<source.SIZE;++i)insert(*is++);
    return *this;
}



/////////////////////////////////////////////////
//class iterator


template <typename TYPE,typename noeud>
abr<TYPE,noeud>::iterator::iterator(noeud* p):REP(p){}


template <typename TYPE,typename noeud>
const TYPE& abr<TYPE,noeud>::iterator::operator*()const{
    return *REP->CONTENU;
    }

template <typename TYPE,typename noeud>
const typename abr<TYPE,noeud>::iterator& abr<TYPE,noeud>::iterator::operator++(){   //++i
    avancer(REP);
    return *this;
    }

template <typename TYPE,typename noeud>
const typename abr<TYPE,noeud>::iterator& abr<TYPE,noeud>::iterator::operator--(){   //--i
    reculer(REP);
    return *this;
    }

template <typename TYPE,typename noeud>
typename abr<TYPE,noeud>::iterator abr<TYPE,noeud>::iterator::operator++(int){       //i++
    iterator copie(*this);
    avancer(REP);
    return copie;
    }

template <typename TYPE,typename noeud>
typename abr<TYPE,noeud>::iterator abr<TYPE,noeud>::iterator::operator--(int){       //i--
    iterator copie(*this);
    reculer(REP);
    return copie;
    }

template <typename TYPE,typename noeud>
bool abr<TYPE,noeud>::iterator::operator==(const iterator& droite)const{
    return REP==droite.REP;
}

template <typename TYPE,typename noeud>
bool abr<TYPE,noeud>::iterator::operator!=(const iterator& droite)const{
    return REP!=droite.REP;
}

/////////////////////////////////////////////////


template <typename TYPE,typename noeud>
void abr<TYPE,noeud>::insert(const TYPE& c){
    bool DEJA=false;
    if(SIZE==0){

        RACINE=new noeud(0,new TYPE(c),0,&AVANT,&APRES);	
        AVANT.PARENT=APRES.PARENT=RACINE;
        }
    else
        noeud::insert(c,RACINE,DEJA);
    if(!DEJA)++SIZE;
    }

template <typename TYPE,typename noeud>
void abr<TYPE,noeud>::erase(const TYPE& c){
    bool ABSENT=true;
    if(SIZE==0)return;
    if(SIZE==1 && *RACINE->CONTENU==c)clear();
    else noeud::erase(c,ABSENT,RACINE);
    if(!ABSENT)--SIZE;
}

template <typename TYPE,typename noeud>
void abr<TYPE,noeud>::erase(iterator i){
    erase(*i);
}



template <typename TYPE,typename noeud>
void abr<TYPE,noeud>::clear(){
    clear(RACINE);
    RACINE=0;
    SIZE=0;
    AVANT.PARENT=&APRES;
    APRES.PARENT=&AVANT;
    }
    

template <typename TYPE,typename noeud>
int abr<TYPE,noeud>::size()const{
    return SIZE;
}

template <typename TYPE,typename noeud>
bool abr<TYPE,noeud>::empty()const{
    return SIZE==0;
}

template <typename TYPE,typename noeud>
typename abr<TYPE,noeud>::iterator abr<TYPE,noeud>::begin()const{
    //cout<<"begin():"<<AVANT.PARENT<<endl;
    return iterator(AVANT.PARENT);
    }

template <typename TYPE,typename noeud>
typename abr<TYPE,noeud>::iterator abr<TYPE,noeud>::end()const{
    //cout<<"end():"<<&APRES<<endl;
    return iterator(&APRES);
}

template <typename TYPE,typename noeud>
typename abr<TYPE,noeud>::iterator abr<TYPE,noeud>::find(const TYPE& c)const{
    noeud* p=RACINE;
    for(;;){
        if(p==0 || p->CONTENU==0)return end();
        else if(c == *p->CONTENU)break;
        else if(c < *p->CONTENU)p=p->GAUCHE;
        else p=p->DROITE;
        }
    return iterator(p);
}


//template <typename TYPE,typename noeud>
//class AVL{
//
//    noeud *PARENT;
//    TYPE* CONTENU;
//	TYPE* intIndice;
//    noeud *GAUCHE,*DROITE;
////   noeud(noeud* P=0,TYPE* C=0,noeud* G=0, noeud* D=0);
//   // static void insert(const TYPE&,noeud*&,bool&);
//    //static void erase(const TYPE&,bool&,noeud*& p);
//	void calculIndice();
//	void hauteur()const;
// //   static void erase(const TYPE&,bool&,noeud*& p,noeud*& aR);
// //   void afficher()const;
//}
//
//template <typename TYPE>
//void AVL<TYPE>::calculIndice(){
//
//
//	}
//
//template <typename TYPE,typename noeud>
//void AVL<TYPE>::hauteur()const{
//
//
//}


///////////////////////////////////////////////
//fonction utilitaires

//template <typename TYPE,typename noeud>
//void abr<TYPE,noeud>::afficher(noeud* p,int niveau)const{
//    if(niveau==0){
//        cout<<endl<<SIZE<<" elements"<<endl;
//        cout<<"APRES: ";APRES.afficher();cout<<endl;
//        p=RACINE;
//        }
//    if(p==0 || p->CONTENU==0)return;
//    afficher(p->DROITE,niveau+1);
//    for(int i=0;i<niveau;++i)cout<<"    ";
//    cout<<"--> ";p->afficher();cout<<endl;
//    afficher(p->GAUCHE,niveau+1);
//    if(niveau==0){
//        cout<<"AVANT: ";AVANT.afficher();cout<<endl;
//        cout<<endl;
//        }
//}

template <typename TYPE,typename noeud>
void abr<TYPE,noeud>::hauteur()const{
    int nb_noeuds=0,total_hauteur=0;
    if(SIZE!=0)hauteur(RACINE,1,nb_noeuds,total_hauteur);
    cout<<nb_noeuds<<" noeuds  ";
    double LOG=log10(nb_noeuds)/log10(2.);
    cout<<LOG<<" log(noeuds)  ";
    double total=total_hauteur;
    if(nb_noeuds!=0)total/=nb_noeuds;
    cout<<total<<" hauteur moyenne des noeuds"<<endl;
    }

                        
////////////////////////////////////////////////////////

////fonction utilitaires
////
template <typename TYPE,typename noeud>
void abr<TYPE,noeud>::afficher()const{
    vector<string> barres;
    //for(int i=0;i<20;++i)
    barres.push_back("    ");
    afficher(RACINE,1,barres);
}


template <typename TYPE,typename noeud>
void abr<TYPE,noeud>::afficher(noeud* p,int niveau,vector<string>& barres)const{
    if(niveau==1){
        cout<<endl<<SIZE<<" elements"<<endl;
        cout<<"APRES: ";APRES.afficher();cout<<endl;
    }
    if(p==0 || p->CONTENU==0)return;
    
    if(niveau>=barres.size())barres.push_back("    ");
    
    afficher(p->DROITE,niveau+1,barres);
    
    //si on est un enfant de gauche arreter les barres a ce niveau
    if(p->PARENT!=0 && p->PARENT->GAUCHE==p)barres[niveau-1]="    ";
    
    //cout<<niveau;
    afficher_barres(barres,niveau);
    cout<<"--->";p->afficher();cout<<endl;
    
    //si on est un enfant de droite barre a mon niveau
    if(p->PARENT!=0 && p->PARENT->DROITE==p)barres[niveau-1]="   |";
    
    //si on a un enfant a gauche mettre des barres apres
    if(p->GAUCHE!=0 && p->GAUCHE->CONTENU!=0)barres[niveau]="   |";
    else barres[niveau]="    ";
    
    //cout<<niveau;
    afficher_barres(barres,niveau+1);
    cout<<endl;
    
    
    afficher(p->GAUCHE,niveau+1,barres);
    
    if(niveau==1){
        cout<<"AVANT: ";AVANT.afficher();cout<<endl;
        cout<<endl;
    }
    
}

template <typename TYPE,typename noeud>
void abr<TYPE,noeud>::afficher_barres(vector<string>& barres,int n)const{
    for(int i=0;i<n;++i)
		cout<<barres[i];
}

#endif
