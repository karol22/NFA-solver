//Karol Gutierrez A01024536
//Context Free Grammar & Pushdown Automata  Solver

#include<bits/stdc++.h>
#include <fstream>
using namespace std;

set<string> states;//estados
set<string> alphabet;//alfabeto
vector< tuple<string, string> > rules;//cada tupla especifica una regla de transicion
string initial;//estado inicial
string objective;//string que ingresa el usuario
bool accepted;//variable global que indica que cadena fue aceptada


void solver(set<string>visited, string current,string path){
    int cont=0; //numero de caracteres en current que son estados
    for(int i=0; i<current.length(); i++){
        if(states.count(current.substr(i, 1))>0) cont++;
    }
    if(cont==0&&current!=objective) return;

    if(accepted) return;
    if(current.length()>objective.length()+2) return;
    visited.insert(current);
    if(objective==current){
        cout<<"\nThe string is accepted. Transitions are the following: \n"<<path;
        accepted=true;
        return;
    }
    int k=0;
    while(states.count(current.substr(k, 1))==0){
        k++;
        if(k==current.length()){
            return;
        }
    }//k es la posicion de current donde hay un caracter de states
    string s1;
    string s2;
    s1=current.substr(0, k);
    s2=current.substr(k+1);
    for(int i=0; i<rules.size(); i++){

        if(get<0>(rules[i])==current.substr(k, 1)){
            string newcurrent;
            if(get<1>(rules[i])=="&"){
                newcurrent=s1+s2;
            }else{
                newcurrent=s1+get<1>(rules[i])+s2;
            }
            if(visited.count(newcurrent)==0){
                solver(visited, newcurrent, path+"\n-> "+newcurrent);
            }
        }
    }

}

int main(){

    string line;

    ifstream in ("cfg.txt");
        //aqui leemos como string todo y lo metemos a los sets
      if (in.is_open())
      {
        string entrada;
        //non terminal symbols
        getline(in,line);
        stringstream ss(line);
        while( ss.good() )
        {
            getline( ss, entrada, ',' );//separa los strings usando la coma
            states.insert(entrada);
        }

        //alphabet
        getline(in,line);
        stringstream ss2(line);
        while( ss2.good() )
        {
            getline( ss2, entrada, ',' );//separa los strings usando la coma
            alphabet.insert(entrada);
        }

        //initial non terminal symbol
        getline(in,line);
        stringstream ss1(line);
        while( ss1.good() )
        {
            getline( ss1, entrada, ',' );//separa los strings usando la coma
            initial=entrada;
        }

        //rules
        while(getline(in,line)){
            string s1, s2, s3;
            stringstream ss4(line);
            getline( ss4, entrada, '-' );//separa los strings usando el primer guion
            s1=entrada;
            getline( ss4, entrada, '-' );//separa los strings usando :
            s2=entrada.substr(1);

            rules.push_back(make_tuple(s1, s2));
        }

        in.close();//cerramos in pues terminamos de leer el archivo
      }


        //menu
        cout<<"Project: CFG and Push Down Automata Solver\n";
        cout<<"  Team members:\n  -Karol Gutierrez A01024536\n  -Mauricio Peon A01024162\n  -Pablo Teran A01421434\n";
                cout<<"States are: ";
      for(auto x:states){
        cout<<x<<" ";
      }
      cout<<endl;


      cout<<"Alphabet is: ";
      for(auto x:alphabet){
        cout<<x<<" ";
      }

      cout<<endl;
      cout<<"Initial state is: ";
      for(auto x:initial){
        cout<<x<<" ";
      }
      cout<<endl;
      cout<<"Transitions are: \n";
      for(auto x:rules){
        cout<< get<0>(x)<<" "<<get<1>(x);
        cout<<endl;
      }
        cout<<"Instructions:\nEnter a string consisting of characters from the alphabet given in the text file.\n";

        cout<<"\nType your string without spaces. Use \".\" to finish. Press Enter after your input.\n String:";
        //pedimos datos iniciales

        getline(cin, objective);
        while(objective!="."){
            accepted=false;//la cadena no ha sido aceptada por lo que es false
            bool caracteres=true;
            for(int i=0; i<objective.length(); i++){
                if(alphabet.count(objective.substr(i, 1))==0) caracteres=false;
            }

            if(caracteres){
                set<string> visited;//inicializamos los estados visitados como un conjunto vacio
                solver(visited, initial, "   "+initial);
                if(!accepted) cout<<"Invalid string.\n";//caso en el que no es valido
            } else cout<<"Invalid string. The characters don't belong to the alphabet.\n";


            cout<<"\nType your string without spaces. Use \".\" to finish. Press Enter after your input.\n String:";
            getline(cin, objective);//pedimos nueva string
        }
}
