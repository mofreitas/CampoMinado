#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
//#include <windows.h>
#include <unistd.h>
#include <clocale>
#include <string>
#include <new>

#define RESET 8
#define BOMBA 9
#define FECHADO 10

using namespace std;

//Cores: branco, ciano, verde, amarelo, vermelho, magenta, magenta, magenta
string cores[11] = {"\033[37m", "\033[36m", "\033[32m", "\033[33m", "\033[31m", "\033[35m", "\033[35m", "\033[35m", "\033[0m", "\033[1m\033[30m", "\033[1m\033[37m"};

void imprimeCampo(int tm, int*** campoini, bool mostrarTudo)
{
    system("clear");
    for(int a = 0; a < (tm+1); a++)
    {
        if(a == 0)
        {
            cout << "    ";
        }
        if(a==1)
        {
            cout << endl;
        }
        if(a>0&&a<=10)
        {
            cout << (a-1) << "-  ";
        }
        if(a>10)
        {
            cout << (a-1) << "- ";
        }
        for(int b = 0; b < tm; b++)
        {
            if(a==0)
            {
                if(b<=9)
                {
                    cout << b << "  ";
                }
                else
                {
                    cout << b << " ";
                }
            }
            else
            {    
                if(campoini[a-1][b][0]==1 || mostrarTudo)
                {
                    if(campoini[a-1][b][1]==1)
                    {
                        cout << cores[BOMBA] << "@" << "  " << cores[RESET];
                    }
                    else
                    {                                
                        cout << cores[campoini[a-1][b][2]] << campoini[a-1][b][2] << "  " << cores[RESET];
                    }
                }
                else
                {
                    cout << cores[FECHADO] << "#" << "  " << cores[RESET];
                }
            }
        }
        cout<<endl;
    }
}

int main()
{
    srand(time(NULL));
    setlocale(LC_ALL, "pt_BR.UTF-8");
    //s=sim/qualquer outra coisa=n�o
    string contjog = "s";

    int escolha;
    cout<<"   _____                              __  __ _                 _       "<<endl;
    cout<<"  / ____|                            |  \\/  (_)               | |      "<<endl;
    cout<<" | |     __ _ _ __ ___  _ __   ___   | \\  / |_ _ __   __ _  __| | ___  "<<endl;
    cout<<" | |    / _` | '_ ` _ \\| '_ \\ / _ \\  | |\\/| | | '_ \\ / _` |/ _` |/ _ \\ "<<endl;
    cout<<" | |___| (_| | | | | | | |_) | (_) | | |  | | | | | | (_| | (_| | (_) |"<<endl;
    cout<<"  \\_____\\__,_|_| |_| |_| .__/ \\___/  |_|  |_|_|_| |_|\\__,_|\\__,_|\\___/ "<<endl;
    cout<<"                       | |                                             "<<endl;
    cout<<"                       |_|                                             "<<endl;
    cin.get(); //waits for character

    while(contjog=="s")
    {
        int tm = 0; //tamanho mina(lado do campo minado)
        int qb = 0; //qntd de bombas
        while(tm == 0)
        {
            //system("cls");
            system("clear");

            cout <<"Escolha a Opcao:" << endl;
            cout <<"1-Jogar"<<endl;
            cout <<"2-Regras do jogo"<<endl;
            cout <<"3-Sair"<<endl;
            cin >> escolha;

            switch(escolha)
            {
                case 1:
                {
                    //submenu-escolher dificuldade
                    while(tm == 0)
                    {
                        //system("cls");
                        system("clear");
                        cout <<"Escolha a dificuldade"<<endl;
                        cout <<"1-Iniciante"<<endl;
                        cout <<"2-Intermediario"<<endl;
                        cout <<"3-Avancado"<<endl;
                        cout <<"4-Voltar"<<endl;
                        cin >> escolha;
                        switch(escolha)
                        {
                            case 1:
                            {
                                tm = 9;
                                qb = 10;
                                break;
                            }
                            case 2:
                            {
                                tm = 16;
                                qb = 40;
                                break;
                            }
                            case 3:
                            {
                                tm = 22;
                                qb = 100;
                                break;
                            }
                            case 4:
                            {
                                tm = 1;
                                break;
                            }
                            default:
                            {
                                cout << "Escolha uma opcao valida" << endl;
                                sleep(2);
                                break;
                            }
                        }
                    }
                    //O if abaixo � para reiniciar o ciclo acima de escolher a op��o(jogar,regras e sair)
                    if(tm==1)
                    {
                        tm=0;
                    }
                    break;
                }
                case 2:
                {
                    //system("cls");
                    system("clear");

                    //REGRAS DO JOGO
                    cout << "Cada quadrado pode ser revelado selecionando sua linha e coluna. "<< endl ;
                    cout << "Se o quadrado escolhido contiver uma bomba, entao o jogo acaba e voce perde. " << endl;
                    cout << "Caso o quadrado nao contiver uma bomba, um numero aparece indicando a quantidade de quadrados adjacentes que contem bombas " << endl;
                    cout << "O jogo e ganho quando todos os quadrados que nao tem bombas sao revelados."<<endl << endl;
                    cin.ignore(); // ignores the newline
                    cin.get(); //waits for character
                    break;
                }
                case 3:
                {
                    tm = 1;
                    contjog = "n";
                    break;
                }
                default:
                {
                    cout << "Escolha uma opcao valida" << endl;
                    sleep(2);
                    break;
                }
            }
        }
        if(tm==1)
        {
            //Sair do While em que est� contido o jogo e finalizar jogo
            break;
        }

        //Inserindo dados na matriz 0=aberto-fechado/1=bomba-naobomba/2=numero de bombas ao lado;
        //varia��o de valores: bomba = 0(verdadeiro) ou 1(falso)/aberto= 1(verdadeiro) ou 0 (falso)/qnt de bombas= 0-8
        int ***campoini;
        for(int k = 0; k < tm; k++)
        {
            campoini = new int**[tm];
            for(int l = 0; l < tm; l++)
            {
                campoini[l] = new int*[tm];
                for(int m = 0; m < tm; m++)
                {                    
                    campoini[l][m] = new int[3];
                }
            }
        }
        for(int a = 0; a < tm; a++)
        {
            for(int b = 0; b<tm;b++)
            {
                campoini[a][b][0] = 0;
                campoini[a][b][1] = 0;
                campoini[a][b][2] = 0;
            }
        }

        //colocando aleatoriamente as bombas

        for(int a = 0; a < qb;a++)
        {
            while(true)
            {

                int poslbomba = rand() % tm;
                int poscbomba = rand() % tm;

                if(campoini[poslbomba][poscbomba][1]==0)
                {
                    campoini[poslbomba][poscbomba][1] = 1;
                    break;
                }
            }
        }


        int contbomb = 0;
        for(int a = 0; a < tm; a++)
        {
            for(int b = 0; b<tm;b++)
            {
                if(campoini[a][b][1]==0)//caso o quadrado for bomba, n�o ser� executado o bloco contido nesse if. Portanto o valor da 3� dimens�o ser� 0, conforme definido na montagem da matriz
                {
                    contbomb = 0;
                    //Verificanndo as tres posi��es acima da linha da bomba
                    if(a-1>=0)
                    {
                        if(b-1>=0 && campoini[a-1][b-1][1]==1)
                        {
                            contbomb++;
                        }
                        if(campoini[a-1][b][1]==1)
                        {
                            contbomb++;
                        }
                        if(b+1<tm && campoini[a-1][b+1][1]==1)
                        {
                            contbomb++;
                        }
                    }
                    //Verificanndo as tres posi��es abaixo da linha da bomba
                    if(a+1<tm)
                    {
                        if(b-1>=0 && campoini[a+1][b-1][1]==1)
                        {
                            contbomb++;
                        }
                        if(campoini[a+1][b][1]==1)
                        {
                            contbomb++;
                        }
                        if(b+1<tm && campoini[a+1][b+1][1]==1)
                        {
                            contbomb++;
                        }
                    }
                    //Verificanndo a casa do lado esquerdo
                    if(b-1>=0 && campoini[a][b-1][1]==1)
                    {
                        contbomb++;
                    }
                    //Verificanndo a casa do lado direito
                    if(b+1<tm && campoini[a][b+1][1]==1)
                    {
                        contbomb++;
                    }
                    campoini[a][b][2] = contbomb;
                }
            }
        }
        //system("cls");
        system("clear");
        //Mostrar campo pela primeira vez
        for(int a = 0; a < (tm+1); a++)
        {
            if(a == 0)
            {
                cout << "    ";
            }
            if(a==1)
            {
                cout << endl;
            }
            if(a>0&&a<=10)
            {
                cout << (a-1) << "-  ";
            }
            if(a>10)
            {
                cout << (a-1) << "- ";
            }
            for(int b = 0; b < tm; b++)
            {
                if(a==0)
                {
                    if(b<=9)
                    {
                        cout << b << "  ";
                    }
                    else
                    {
                        cout << b << " ";
                    }
                }
                else
                {
                    cout << "#" << "  ";
                }
            }     
                cout<<endl;
        }

        int contabertas = 0;
        while(true)
        {
            int lin;
            int col;
            cout<<endl;
            cout << "Digite numeros negativos caso queira reiniciar"<<endl;
            cout << "Numero da linha: ";
            cin >> lin;
            cout << "Numero da coluna: ";
            cin >> col;
            cout<<endl;

            if(lin<0&&col<0)
            {
                imprimeCampo(tm, campoini, true);
                cout<<endl<<"O jogo sera reiniciado"<<endl<<endl;
                cin.ignore(); // ignores the newline
                cin.get(); //waits for character
                break;
            }
            else if(lin>tm-1||col>tm-1)
            {
                cout << "Por favor, escolha valores dentro do intervalo de linhas e colunas" << endl <<endl;
                cin.ignore(); // ignores the newline
                cin.get(); //waits for character
                //system("cls");
                system("clear");

            }
            else if(campoini[lin][col][0] == 1)
            {
                cout << "Esse espaco ja foi aberto" << endl << endl;
                cin.ignore(); // ignores the newline
                cin.get(); //waits for character
                //system("cls");
                system("clear");
            }
            else if(campoini[lin][col][1] == 1)
            {
                imprimeCampo(tm, campoini, true);
                cout << endl << "Voce perdeu" << endl << endl << "Deseja reiniciar? (s ou n)" << endl;
                cin >> contjog;
                break;
            }
            else if(campoini[lin][col][2] > 0)//Se a casa aberta for um n�mero maior que 0, indicando que existem bombas ao lado
            {
                campoini[lin][col][0] = 1;
                contabertas++;
            }
            else//se a casa aberta for um 0
            {
                int listabrir[(tm*tm)-qb][2];//posi��es que o codigo deve abrir as casas ao redor
                int ciclo = 0; // quantidade de vezes que ele executou o codigo
                int contab = 0; // quantidade que deve ser executada
                listabrir[0][0] = lin;
                listabrir[0][1] = col;
                campoini[lin][col][0] = 1;
                contabertas++;

                while(ciclo<=contab)//abrir casas ao redor e registrar as que tbm devem ter as casas ao redor abertas
                {
                    if(lin-1>=0)
                    {
                        if(col-1>=0 && campoini[lin-1][col-1][0]==0)
                        {
                            contabertas++;
                            campoini[lin-1][col-1][0]=1;
                            if(campoini[lin-1][col-1][2]==0)
                            {
                                contab++;
                                listabrir[contab][0]=lin-1;
                                listabrir[contab][1]=col-1;
                            }
                        }
                        if(campoini[lin-1][col][0]==0)
                        {
                            contabertas++;
                            campoini[lin-1][col][0]=1;
                            if(campoini[lin-1][col][2]==0)
                            {
                                contab++;
                                listabrir[contab][0]=lin-1;
                                listabrir[contab][1]=col;
                            }
                        }
                        if(col+1<tm && campoini[lin-1][col+1][0]==0)
                        {
                            contabertas++;
                            campoini[lin-1][col+1][0]=1;
                            if(campoini[lin-1][col+1][2]==0)
                            {
                                contab++;
                                listabrir[contab][0]=lin-1;
                                listabrir[contab][1]=col+1;
                            }
                        }
                    }
                    if(lin+1<tm)
                    {
                        if(col-1>=0 && campoini[lin+1][col-1][0]==0)
                        {
                            contabertas++;
                            campoini[lin+1][col-1][0]=1;
                            if(campoini[lin+1][col-1][2]==0)
                            {
                                contab++;
                                listabrir[contab][0]=lin+1;
                                listabrir[contab][1]=col-1;
                            }
                        }
                        if(campoini[lin+1][col][0]==0)
                        {
                            contabertas++;
                            campoini[lin+1][col][0]=1;
                            if(campoini[lin+1][col][2]==0)
                            {
                                contab++;
                                listabrir[contab][0]=lin+1;
                                listabrir[contab][1]=col;
                            }
                        }
                        if(col+1<tm && campoini[lin+1][col+1][0]==0)
                        {
                            contabertas++;
                            campoini[lin+1][col+1][0]=1;
                            if(campoini[lin+1][col+1][2]==0)
                            {
                                contab++;
                                listabrir[contab][0]=lin+1;
                                listabrir[contab][1]=col+1;
                            }
                        }
                    }
                    if(col-1>=0 && campoini[lin][col-1][0]==0)
                    {
                        contabertas++;
                        campoini[lin][col-1][0]=1;
                        if(campoini[lin][col-1][2]==0)
                        {
                            contab++;
                            listabrir[contab][0]=lin;
                            listabrir[contab][1]=col-1;
                        }
                    }
                    if(col+1<tm && campoini[lin][col+1][0]==0)
                    {
                        contabertas++;
                        campoini[lin][col+1][0]=1;
                        if(campoini[lin][col+1][2]==0)
                        {
                            contab++;
                            listabrir[contab][0]=lin;
                            listabrir[contab][1]=col+1;
                        }
                    }

                    ciclo++;
                    lin = listabrir[ciclo][0];
                    col = listabrir[ciclo][1];
                }
            }
            if(contabertas==(tm*tm-qb))//Se o n�mero de casas abertas for igual a quantidade de casas - qntd de bombas na matriz
            {
                imprimeCampo(tm, campoini, true);
                cout << "Parabens, voce venceu!" << endl << endl << "Deseja reiniciar? (s ou n)" << endl;
                cin >> contjog;
                break;
            }
            //Revelar a matriz caso o jogo continue normalmente
            //system("cls");
            imprimeCampo(tm, campoini, false);

        }
        
        for(int k = 0; k < tm; k++)
        {
            for(int l = 0; l < tm; l++)
            {
                delete[] campoini[k][l];
            }
            delete[] campoini[k];
        }
        delete[] campoini;
    }

   //system("cls");
   system("clear");



    cout<<" ______ _                 _             _           "<<endl;
    cout<<"|  ____(_)               | |           | |                  "<<endl;
    cout<<"| |__   _ _ __ ___     __| | ___       | | ___   __ _  ___  "<<endl;
    cout<<"|  __| | | '_ ` _ \\   / _` |/ _ \\  _   | |/ _ \\ / _` |/ _ \\ "<<endl;
    cout<<"| |    | | | | | | | | (_| |  __/ | |__| | (_) | (_| | (_) |"<<endl;
    cout<<"|_|    |_|_| |_| |_|  \\__,_|\\___|  \\____/ \\___/ \\__, |\\___/ "<<endl;
    cout<<"                                                 __/ |    "<<endl;
    cout<<"                                                |___/    "<<endl;


}
