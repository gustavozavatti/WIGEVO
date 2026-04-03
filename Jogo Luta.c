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

void criacaoPersonagem(struct personagem *p)
{
    printf("Digite o nome do lutador: ");
    scanf("%s", p->nomePersonagem);

    do
    {
        printf("Digite a vida(Numero terminado em 0): ");
        scanf("%d", &p->lifePersonagem);
    } while (p->lifePersonagem % 10 != 0);

    printf("Digite o ataque: ");
    scanf("%d", &p->atkPersonagem);
    printf("Digite a defesa: ");
    scanf("%d", &p->defPersonagem);
}

int damageCalculator(struct personagem *p1, struct personagem *p2)
{
    int dano = p1->atkPersonagem - p2->defPersonagem;
    if (dano < 0)
    {
        dano = 0;
    }
    return dano;
}

void regeneracaoVida(int atual, int vidaOriginal)
{
    if (atual != vidaOriginal)
    {
        atual += 10;

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
        break;
    }

    struct personagem *personagensBatalha = (struct personagem *)malloc(2 * sizeof(struct personagem));

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
        printf("\n===== STATUS ATUAL =====\n");
        printf("%s -> Vida: %d\n", personagensBatalha[0].nomePersonagem, personagensBatalha[0].lifePersonagem);
        printf("%s -> Vida: %d\n", personagensBatalha[1].nomePersonagem, personagensBatalha[1].lifePersonagem);

        printf("\nJogador 1: \n");
        printf("Digite 1 para atacar!\n");
        printf("Digite 2 para curar!\n");
        printf("Digite 3 para aumentar o ataque!\n");
        if (personagensBatalha[0].lifePersonagem <= 20 && flagRegeneracao1 == 0)
        {
            printf("Digite 4 para recarga de vida especial!\n");
        }
        scanf("%d", &acaoLuta);
        switch (acaoLuta)
        {
        case 1:
            personagensBatalha[1].lifePersonagem -= damageCalculator(&personagensBatalha[0], &personagensBatalha[1]);
            break;
        case 2:
            personagensBatalha[0].lifePersonagem += 10;
            if (personagensBatalha[0].lifePersonagem > guardaVidaP1)
            {
                personagensBatalha[0].lifePersonagem = guardaVidaP1;
                printf("Limite de vida atingido!\n");
            }
            break;
        case 3:
            personagensBatalha[0].atkPersonagem += 10;
            break;
        case 4:
            if (personagensBatalha[0].lifePersonagem <= 20 && flagRegeneracao1 == 0)
            {
                regeneracaoVida(personagensBatalha[0].lifePersonagem, guardaVidaP1);
                personagensBatalha[0].lifePersonagem = guardaVidaP1;
                flagRegeneracao1++;
            }
            else
            {
                printf("Recarga especial não disponivel!\n");
            }
            break;
        default:
            printf("Acao invalida!\n");
             break;
        }

        printf("\n===== STATUS ATUAL =====\n");
        printf("%s -> Vida: %d\n", personagensBatalha[0].nomePersonagem, personagensBatalha[0].lifePersonagem);
        printf("%s -> Vida: %d\n", personagensBatalha[1].nomePersonagem, personagensBatalha[1].lifePersonagem);

        if (personagensBatalha[1].lifePersonagem <= 0)
        {
            personagensBatalha[1].lifePersonagem = 0;
            break;
        }

        printf("\nJogador 2: \n");
        printf("Digite 1 para atacar!\n");
        printf("Digite 2 para curar!\n");
        printf("Digite 3 para aumentar o ataque!\n");
        if (personagensBatalha[1].lifePersonagem <= 20 && flagRegeneracao2 == 0)
        {
            printf("Digite 4 para recarga de vida especial!\n");
        }
        scanf("%d", &acaoLuta);
        switch (acaoLuta)
        {
        case 1:
            personagensBatalha[0].lifePersonagem -= damageCalculator(&personagensBatalha[1], &personagensBatalha[0]);
            break;
        case 2:
            personagensBatalha[1].lifePersonagem += 10;
            if (personagensBatalha[1].lifePersonagem > guardaVidaP2)
            {
                personagensBatalha[1].lifePersonagem = guardaVidaP2;
                printf("Limite de vida atingido!\n");
            }
            break;
        case 3:
            personagensBatalha[1].atkPersonagem += 10;
            break;
        case 4:
            if (personagensBatalha[1].lifePersonagem <= 20 && flagRegeneracao2 == 0)
            {
                regeneracaoVida(personagensBatalha[1].lifePersonagem, guardaVidaP2);
                personagensBatalha[1].lifePersonagem = guardaVidaP2;
                flagRegeneracao2++;
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

        if (personagensBatalha[0].lifePersonagem <= 0)
        {
            personagensBatalha[0].lifePersonagem = 0;
            break;
        }

    } while (personagensBatalha[0].lifePersonagem > 0 && personagensBatalha[1].lifePersonagem > 0);

    if (personagensBatalha[0].lifePersonagem <= 0)
    {
        printf("\n%s ganhou!", personagensBatalha[1].nomePersonagem);
    }
    else
    {
        printf("\n%s ganhou!", personagensBatalha[0].nomePersonagem);
    }

    free(personagensBatalha);

    return 0;
}
