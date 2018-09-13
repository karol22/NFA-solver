//Karol Gutierrez A01024536
//NFA Solver

#include<bits/stdc++.h>
#include <fstream>
using namespace std;

set<string> states;//estados
set<string> alphabet;//alfabeto
set<string> finals;//estados finales
vector< tuple<string, string, string> > rules;//cada tupla especifica una regla de transicion
string initial;//estado inicial
string s;//string que ingresa el usuario
bool accepted;//variable global que indica que cadena fue aceptada

void solver(int pos, string current, set<tuple<int, string>> visited, string path){//funcion revursiva que resuelve el problema. pos es la posicion en s, visited es un
    //set que almacena los estados visitados hasta el momento y la posicion en la cadena en dicho momento y path es una cadena que describe las transiciones realizadas hasta ese momento

    visited.insert(make_tuple(pos, current));//se inserta la posicion y estado actual

    if(pos==s.length()&&finals.count(current)>0){//cuando recorrimos todo el string y estamos en un estado final quiere decir que hemos terminado
        accepted=true;
        cout<<"\""<<s<<"\""<<" is a valid string and the resulting transitions are: \n"<<path<<"\n";
        return;
    } else{//caso contrario
        for(int i=0; i<rules.size(); i++){//recorremos todas las transiciones
            if(get<0>(rules[i])==current){//que contengan el estado inicial y volvemos a llamar la funcion

                if(get<1>(rules[i])=="&"){//caso epsilon
                   if(visited.count(make_tuple(pos, get<2>(rules[i])))==0){//revisamos que no haya ciclos
                         solver(pos, get<2>(rules[i]), visited, path+" ---"+get<1>(rules[i])+"--> "+get<2>(rules[i]) );//llamada recursiva, se actualiza el recorrido
                   }
                }else if(get<1>(rules[i])[0]==s[pos]){//transicion distinta a epsilon
                    if(visited.count(make_tuple(pos+1, get<2>(rules[i])))==0){//revisamos que no haya ciclos
                         solver(pos+1, get<2>(rules[i]), visited, path+" ---"+get<1>(rules[i])+"--> "+get<2>(rules[i]) );//llamada recursiva, se actualiza el recorrido
                   }
                }
            }
        }
    }
}

int main(){

    string line;

    ifstream in ("nfa.txt");
        //aqui leemos como string todo y lo metemos a los sets
      if (in.is_open())
      {
        string entrada;
        //states
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

        //initial state
        getline(in,line);
        stringstream ss1(line);
        while( ss1.good() )
        {
            getline( ss1, entrada, ',' );//separa los strings usando la coma
            initial=entrada;
        }


        //final states
        getline(in,line);
        stringstream ss3(line);
        while( ss3.good() )
        {
            getline( ss3, entrada, ',' );//separa los strings usando la coma
            finals.insert(entrada);
        }

        //rules
        while(getline(in,line)){
            string s1, s2, s3;
            stringstream ss4(line);
            getline( ss4, entrada, ',' );//separa los strings usando la coma
            s1=entrada;
            getline( ss4, entrada, ':' );//separa los strings usando :
            s2=entrada;
            getline( ss4, entrada, ':' );//separa los strings usando :
            s3=entrada;
            rules.push_back(make_tuple(s1, s2, s3));
        }

        in.close();//cerramos in pues terminamos de leer el archivo
      }

        //menu
        cout<<"Project: NFA Solver\n";
        cout<<"  Team members:\n  -Karol Gutierrez A01024536\n";
        cout<<"Instructions:\nEnter a string consisting of characters from the alphabet given in the text file.\n";
        cout<<"\nType your string without spaces. Use \".\" to finish. Press Enter after your input.\n String:";
        //pedimos datos iniciales
        getline(cin, s);
        while(s!="."){
            set<tuple<int, string> > visited;//inicializamos los estados visitados como un conjunto vacio
            accepted=false;//la cadena no ha sido aceptada por lo que es false
            solver(0, initial, visited, initial);
            if(!accepted) cout<<"Invalid string.\n";//caso en el que no es valido

            cout<<"\nType your string without spaces. Use \".\" to finish. Press Enter after your input.\n String:";
            getline(cin, s);//pedimos nueva string
        }
}
