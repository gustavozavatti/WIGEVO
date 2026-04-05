#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct personagem
{
    char nomePersonagem[20];
    int lifePersonagem;
    int atkPersonagem;
    int defPersonagem;
};

void criacaoPersonagem(struct personagem *personagem)
{
    printf("Digite o nome do lutador: ");
    scanf("%s", personagem->nomePersonagem);

    do
    {
        printf("Digite a vida(Numero terminado em 0): ");
        scanf("%d", &personagem->lifePersonagem);
    } while (personagem->lifePersonagem % 10 != 0);

    printf("Digite o ataque: ");
    scanf("%d", &personagem->atkPersonagem);
    printf("Digite a defesa: ");
    scanf("%d", &personagem->defPersonagem);
}

int damageCalculator(struct personagem *personagem1, struct personagem *personagem2)
{
    int dano = personagem1->atkPersonagem - personagem2->defPersonagem;
    if (dano < 0)
    {
        dano = 0;
    }
    return dano;
}

void regeneracaoVida(int atual, int vidaOriginal)
{
    if (atual < vidaOriginal)
    {
        atual += 10;

        if (atual > vidaOriginal)
        {
            atual = vidaOriginal;
        }

        printf("Curando... Vida atual: %d\n", atual);
        regeneracaoVida(atual, vidaOriginal);
    }
    else
    {
        printf("Vida restaurada: %d!\n", atual);
    }
}

int buscaPersonagemPronto(struct personagem lista[], int tamanho, int escolha, struct personagem *destino)
{
    for (int i = 0; i < tamanho; i++)
    {
        if (i == (escolha - 1))
        {
            strcpy(destino->nomePersonagem, lista[i].nomePersonagem);
            destino->lifePersonagem = lista[i].lifePersonagem;
            destino->atkPersonagem = lista[i].atkPersonagem;
            destino->defPersonagem = lista[i].defPersonagem;
            return 0;
        }
    }
    return 1;
}

void StatusAtual(struct personagem *personagem1, struct personagem *personagem2)
{
    printf("\n===== STATUS ATUAL =====\n");
    printf("%s -> Vida: %d\n", personagem1->nomePersonagem, personagem1->lifePersonagem);
    printf("%s -> Vida: %d\n", personagem2->nomePersonagem, personagem2->lifePersonagem);
}

void menuAcoes(struct personagem *personagem1, int flagRegeneracao1, int jogador)
{
    printf("\nJogador %d: \n", jogador);
    printf("\nDigite 1 para atacar!\n");
    printf("Digite 2 para curar!\n");
    printf("Digite 3 para aumentar o ataque!\n");
    if (personagem1->lifePersonagem <= 20 && flagRegeneracao1 == 0)
    {
        printf("Digite 4 para recarga de vida especial!\n");
    }
}

void acoesLuta(struct personagem *personagem1, struct personagem *personagem2, int acaoLuta, int *flagRegeneracao1)
{
    switch (acaoLuta)
    {
    case 1:
        personagem2->lifePersonagem -= damageCalculator(personagem1, personagem2);
        break;
    case 2:
        personagem1->lifePersonagem += 10;
        break;
    case 3:
        personagem1->atkPersonagem += 10;
        break;
    case 4:
        if (personagem1->lifePersonagem <= 20 && *flagRegeneracao1 == 0)
        {
            regeneracaoVida(personagem1->lifePersonagem, personagem1->lifePersonagem);
            *flagRegeneracao1 = 1;
        }
        else
        {
            printf("Recarga especial nao disponivel!\n");
        }
        break;
    default:
        printf("Acao invalida!\n");
        break;
    }
}

int verificacaoGanhador(struct personagem *personagem1, struct personagem *personagem2)
{
    if (personagem1->lifePersonagem <= 0)
    {
        printf("\n%s ganhou!", personagem2->nomePersonagem);
        return 1;
    }
    else if (personagem2->lifePersonagem <= 0)
    {
        printf("\n%s ganhou!", personagem1->nomePersonagem);
        return 2;
    }
    else
    {
        return 0;
    }
}

void verificacaoVida(struct personagem *personagem)
{
    if (personagem->lifePersonagem < 0)
    {
        personagem->lifePersonagem = 0;
    }
}

int main()
{

    // AÇÕES //
    int acaoLuta = 0, escolhaMenu = 0, flagRegeneracao1 = 0, flagRegeneracao2 = 0, escolhaCriacaoPersonagem = 0, escolhaPersonagemPronto = 0;

    // GUARDA VIDA //
    int guardaVidaP1 = 0, guardaVidaP2 = 0;

    printf("\n===== WIGEVO =====\n");
    printf("Digite 1 para comecar!\n");
    printf("Digite 2 para sair!\n");
    printf("\nPress: ");
    scanf("%d", &escolhaMenu);
    printf("\n");

    // ENTRAR OU SAIR DO JOGO //

    switch (escolhaMenu)
    {
    case 1:
        break;
    case 2:
        return 0;
    default:
        printf("Opcao invalida!\n");
        return 0;
    }

    struct personagem *personagensBatalha = (struct personagem *)malloc(2 * sizeof(struct personagem));

    if (personagensBatalha == NULL)
    {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    struct personagem prontos[3];
    strcpy(prontos[0].nomePersonagem, "Ragnar");
    prontos[0].lifePersonagem = 120;
    prontos[0].atkPersonagem = 50;
    prontos[0].defPersonagem = 30;

    strcpy(prontos[1].nomePersonagem, "Darius");
    prontos[1].lifePersonagem = 100;
    prontos[1].atkPersonagem = 60;
    prontos[1].defPersonagem = 20;

    strcpy(prontos[2].nomePersonagem, "Kade");
    prontos[2].lifePersonagem = 110;
    prontos[2].atkPersonagem = 70;
    prontos[2].defPersonagem = 10;

    printf("\n===== Escolha de personagens =====\n");
    printf("Digite 1 selecionar lutadores prontos!\n");
    printf("Digite 2 para criar lutador!\n");
    printf("\nPress: ");
    scanf("%d", &escolhaCriacaoPersonagem);

    if (escolhaCriacaoPersonagem == 1)
    {
        printf("\nEscolha: \n\n");
        printf("1)Ragnar - Vida: 120 Atk: 50 Def: 30\n");
        printf("2)Darius - Vida: 100 Atk: 60 Def: 20\n");
        printf("3)Kade - Vida: 110 Atk: 70 Def: 10\n");
        printf("\nPress: ");
        scanf("%d", &escolhaPersonagemPronto);

        if (buscaPersonagemPronto(prontos, 3, escolhaPersonagemPronto, &personagensBatalha[0]))
        {
            printf("Lutador nao encontrado!\n");
            return 0;
        }

        printf("\nJogador 2, escolha seu lutador:\n");
        scanf("%d", &escolhaPersonagemPronto);

        if (buscaPersonagemPronto(prontos, 3, escolhaPersonagemPronto, &personagensBatalha[1]))
        {
            printf("Lutador nao encontrado!\n");
            return 0;
        }

        printf("\nJogador 1 escolheu: %s\n", personagensBatalha[0].nomePersonagem);
        printf("Jogador 2 escolheu: %s\n", personagensBatalha[1].nomePersonagem);
    }
    else
    {
        for (int i = 0; i < 2; i++)
        {

            printf("\nDigite os status do lutador jogador %d: \n", i + 1);
            criacaoPersonagem(&personagensBatalha[i]);
        }
    }

    guardaVidaP1 = personagensBatalha[0].lifePersonagem;
    guardaVidaP2 = personagensBatalha[1].lifePersonagem;

    do
    {
        StatusAtual(&personagensBatalha[0], &personagensBatalha[1]);
        menuAcoes(&personagensBatalha[0], flagRegeneracao1, 1);
        scanf("%d", &acaoLuta);

        acoesLuta(&personagensBatalha[0], &personagensBatalha[1], acaoLuta, &flagRegeneracao1);

        StatusAtual(&personagensBatalha[0], &personagensBatalha[1]);

        verificacaoVida(&personagensBatalha[1]);

        menuAcoes(&personagensBatalha[1], flagRegeneracao2, 2);
        scanf("%d", &acaoLuta);

        acoesLuta(&personagensBatalha[1], &personagensBatalha[0], acaoLuta, &flagRegeneracao2);

        verificacaoVida(&personagensBatalha[0]);

    } while (personagensBatalha[0].lifePersonagem > 0 && personagensBatalha[1].lifePersonagem > 0);

    verificacaoGanhador(&personagensBatalha[0], &personagensBatalha[1]);

    free(personagensBatalha);

    return 0;
}
