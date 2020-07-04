#include <iostream>
using namespace std;

//Variaveis globais para contar o número de tipo de veiculos.
int global_carro = 0;
int global_caminhonete = 0;
int global_esportivo = 0;


struct cliente
{
    string placa = "";
    int hora_chegada = 0;
    string auto_tipo = ""; // para imprimir os dados do tipo de automovel.
    
};

void entrada_cliente(struct cliente *entrada_dados)
{
    // essa função serve para criar prencher as variaveis do array de tipo heterogeneo.
    int flag = 0;
    int flag2 = 0;
    int escolha = 0;

    while (flag == 0)
    {
        cout << "Qual o tipo de automovel.\n[1]Carro\n[2]Caminhonete\n[3]Esportivo" << endl;
        cin >> escolha;

        while (flag2==0){
            if ((escolha == 1) && (global_carro < 45)) //verificando se tem vagas suficientes
            {
                global_carro++;
                entrada_dados->auto_tipo = "Carro";
                flag2 = 1;
            }
            if ((escolha == 2) && (global_caminhonete< 60)) {
                global_caminhonete++;
                entrada_dados->auto_tipo = "Caminhonete";
                flag2 = 1;

            }
            if ((escolha == 3) && (global_esportivo < 15)) {
                global_esportivo++;
                entrada_dados->auto_tipo = "Carro esportivo";
                flag2 = 1;
            }
            if((escolha != 1) && (escolha != 2 ) && (escolha != 3)) // Antes estava como um else mas ele estava sendo ativado msm com a escolha sendo 1-3 e quantidade menor que o limite então para parar de bugar criei um if grande
            {
                cout << "Valor digitado incorreto ou estacionamento lotado na area desejada." << endl;
                cout << "[0]Tentar Novamente\n[1]Sair";
                cin >> flag;
            }
        }

        cout << "Digite a placa do carro: ";
        cin >> entrada_dados->placa;
        cout << "Digite o Horario de Chegada: ";
        cin >> entrada_dados->hora_chegada;

        cout << "Deseja refazer os dados ? \n[0]Refazer Dados\n[1]Sair " << endl;
        system("cls");


        flag = 1;
    }

}
int saida_cliente(struct cliente *saida,int time)
{   
    float lucro = 0;
    
    cout << "Tipo de Carro: " << saida->auto_tipo << endl;
    cout << "Horario de chegada: " << saida->hora_chegada << endl;
    cout << "Placa do carro: " << saida->placa << endl;
    
    //retirando o automovel das variaveis globais, retornando os valores para ir calculado o lucro total, e mostrando quanto o cliente pagou pelo tempo que ficou.
    if (saida->auto_tipo == "Carro")
    {
        global_carro--;
        return (time - saida->hora_chegada) * 5;
        cout << "O cliente pagaou: " << (time - saida->hora_chegada) * 5 << endl;
    }
    if (saida->auto_tipo == "Carro esportivo")
    {
        global_esportivo--;
        return (time - saida->hora_chegada) * 5;
        cout << "O cliente pagaou: " << (time - saida->hora_chegada) * 5 << endl;
    }
    if (saida->auto_tipo == "Caminhonete")
    {
        global_caminhonete--;
        return (time - saida->hora_chegada) * 7;
        cout << "O cliente pagaou: " << (time - saida->hora_chegada) * 7 << endl;
    }
    //anulandao a variavel para poder ser reutilizada.
    saida->auto_tipo = "";
    saida->hora_chegada = 0;
    saida->placa = "";

}

int main()
{
    struct cliente cliente_dados[120];
    int tempo = 4, flag = 0, escolha, total = 0,codigo = 0,temp_tempo=0;
    float lucro = 0;
    // O estacinamento abre as 4 é vai fechar as 24, quando fechado todos os dados vão ser anulados e sera reiniciado.

    while (flag == 0)
    {
        cout << "Digite oque deseja fazer.\n[1]Entrada de veiculo\n[2]Saida de veiculo\n[3]Administrador" << endl;
        cin >> escolha;

        switch (escolha)
        {
        case 1:
            if (total > 120)
            {
                entrada_cliente(&cliente_dados[total]);
                //Seria o papel que o cliente receberia.
                cout << "Tipo de Carro: " << cliente_dados[total].auto_tipo << endl;
                cout << "Horario de chegada: " << cliente_dados[total].hora_chegada << endl;
                cout << "Placa do carro: " << cliente_dados[total].placa << endl;
                cout << "Quantidade de carros: " << global_carro << endl;
                cout << "CODIGO PARA SAIDA DO CLIENTE: " << total << endl;
                //modificando o total de automoveis.
                total++;
                break;
            }
            else
            {
                cout << "Limite de automoveis atingidos." << endl;
            }

        case 2:
            cout << "Digite o codigo para se indetificar:  ";
            cin >> codigo;
            lucro += saida_cliente(&cliente_dados[codigo],tempo);
            total--;
            break;
        case 3:
            cout << "Oque deseja fazer\n[1]Modificar o tempo\n[2]Faturamento medio hora" << endl;
            cin >> escolha; // reutilizando variavel.
            if (escolha == 1)
            {
                // temp_tempo  é feito para comparar o tempo e assim impedir VOLTAR NO TEMPO :)  
                while (tempo < temp_tempo)
                {
                    temp_tempo = tempo;
                    cout << "Digite a hora atual: ";
                    cin >> tempo;
                    if (tempo < temp_tempo)
                        cout << "Tempo menor do que o atual. Viagems do tempo não é possivel AINDA." << endl;
                }
            }

            
            break;
        default:
            cout << "Escolha invalida tente novamente." << endl;
            break;
        }

    }
}
