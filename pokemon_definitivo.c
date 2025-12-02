#include <stdio.h>
#include <string.h>
#include <locale.h>

char *nomes[6] = {"Venusaur", "Charizard", "Blastoise", "Sceptile", "Blaziken", "Swampert"};
char *tipos_pokemon[6] = {"Grass", "Fire", "Water", "Grass", "Fire", "Water"};

int hp_base[6] = {80, 78, 79, 70, 80, 100};
int atk_base[6] = {82, 84, 83, 85, 120, 110};
int spa_base[6] = {100, 109, 85, 105, 110, 85};
int def_base[6] = {83, 78, 100, 65, 70, 90};
int spd_base[6] = {100, 85, 105, 85, 70, 90};

char *ataques_pokemon[6][4] = {
    {"Solar Beam", "Sludge Bomb", "Earthquake", "Giga Drain"},
    {"Flamethrower", "Dragon Claw", "Earthquake", "Air Slash"},
    {"Hydro Pump", "Ice Beam", "Earthquake", "Flash Cannon"},
    {"Leaf Blade", "Dragon Pulse", "Earthquake", "Energy Ball"},
    {"Blaze Kick", "Sky Uppercut", "Brave Bird", "Flamethrower"},
    {"Hydro Pump", "Earthquake", "Ice Beam", "Hammer Arm"}};

int poderes[24] = {
    120, 90, 100, 75,
    90, 80, 100, 75,
    110, 90, 100, 80,
    90, 85, 100, 120,
    85, 100, 120, 90,
    110, 100, 90, 100};

char *categorias_ataques[24] = {
    "Special", "Special", "Physical", "Special",
    "Special", "Physical", "Physical", "Special",
    "Special", "Special", "Physical", "Special",
    "Physical", "Special", "Physical", "Special",
    "Physical", "Physical", "Physical", "Special",
    "Special", "Physical", "Special", "Physical"};

char *tipos_ataques[24] = {
    "Grass", "Poison", "Ground", "Grass",
    "Fire", "Dragon", "Ground", "Flying",
    "Water", "Ice", "Ground", "Steel",
    "Grass", "Dragon", "Ground", "Grass",
    "Fire", "Fighting", "Flying", "Fire",
    "Water", "Ground", "Ice", "Fighting"};

float efetividade(char *ataque, char *tipo_defensor)
{
    float mult = 1.0;
    if (!strcmp(ataque, "Grass"))
    {
        if (!strcmp(tipo_defensor, "Water"))
            mult *= 2;
        if (!strcmp(tipo_defensor, "Fire"))
            mult *= 0.5;
    }
    if (!strcmp(ataque, "Fire"))
    {
        if (!strcmp(tipo_defensor, "Grass"))
            mult *= 2;
        if (!strcmp(tipo_defensor, "Water"))
            mult *= 0.5;
    }
    if (!strcmp(ataque, "Water"))
    {
        if (!strcmp(tipo_defensor, "Fire"))
            mult *= 2;
        if (!strcmp(tipo_defensor, "Grass"))
            mult *= 0.5;
    }
    if (!strcmp(ataque, "Ground"))
    {
        if (!strcmp(tipo_defensor, "Fire"))
            mult *= 2;
        if (!strcmp(tipo_defensor, "Grass"))
            mult *= 0.5;
    }
    return mult;
}

int calcularDano(int lvl, int power, int atk, int def, float stab, float eff)
{
    float dano = (((((2 * lvl) / 5.0 + 2) * power * atk / def) / 50) + 2);
    dano *= stab * eff;
    return (int)dano;
}

void exibir_time(int time[3], char *nome_time, int hp_atual[3])
{
    printf("\n--- %s ---\n", nome_time);
    for (int i = 0; i < 3; i++)
    {
        int idx = time[i];
        printf("%d. %s (%s) HP: %d/%d\n", i + 1, nomes[idx], tipos_pokemon[idx], hp_atual[i], hp_base[idx]);
    }
}

int escolher_ataque(int pokemon_idx)
{
    printf("Escolha um ataque para %s:\n", nomes[pokemon_idx]);
    for (int i = 0; i < 4; i++)
    {
        printf("%d - %s\n", i + 1, ataques_pokemon[pokemon_idx][i]);
    }
    int escolha;
    while (1)
    {
        scanf("%d", &escolha);
        if (escolha >= 1 && escolha <= 4)
            return escolha - 1;
        printf("Escolha invalida! Digite 1-4.\n");
    }
}

void batalha(int time1[3], int time2[3])
{
    int hp1[3], hp2[3];
    for (int i = 0; i < 3; i++)
    {
        hp1[i] = hp_base[time1[i]];
        hp2[i] = hp_base[time2[i]];
    }

    int atual1 = 0, atual2 = 0;

    while (1)
    {
        int vivo1 = 0, vivo2 = 0;
        for (int i = 0; i < 3; i++)
        {
            if (hp1[i] > 0)
                vivo1 = 1;
            if (hp2[i] > 0)
                vivo2 = 1;
        }
        if (!vivo1)
        {
            printf("Time 2 venceu!\n");
            break;
        }
        if (!vivo2)
        {
            printf("Time 1 venceu!\n");
            break;
        }

        while (hp1[atual1] <= 0)
            atual1++;
        while (hp2[atual2] <= 0)
            atual2++;

        printf("\n===== TURNO =====\n");
        printf("Pokemon 1: %s HP: %d\n", nomes[time1[atual1]], hp1[atual1]);
        int atk1 = escolher_ataque(time1[atual1]);

        printf("Pokemon 2: %s HP: %d\n", nomes[time2[atual2]], hp2[atual2]);
        int atk2 = escolher_ataque(time2[atual2]);

        int idx1 = time1[atual1] * 4 + atk1;
        int atkStat1 = (!strcmp(categorias_ataques[idx1], "Special")) ? spa_base[time1[atual1]] : atk_base[time1[atual1]];
        int defStat2 = (!strcmp(categorias_ataques[idx1], "Special")) ? spd_base[time2[atual2]] : def_base[time2[atual2]];
        float stab1 = (!strcmp(tipos_ataques[idx1], tipos_pokemon[time1[atual1]])) ? 1.5 : 1.0;
        float eff1 = efetividade(tipos_ataques[idx1], tipos_pokemon[time2[atual2]]);
        int dano1 = calcularDano(50, poderes[idx1], atkStat1, defStat2, stab1, eff1);

        hp2[atual2] -= dano1;
        if (hp2[atual2] < 0)
            hp2[atual2] = 0;
        printf("%s usou %s! Causou %d de dano (Efetividade %.1fx)\n", nomes[time1[atual1]], ataques_pokemon[time1[atual1]][atk1], dano1, eff1);

        if (hp2[atual2] == 0)
        {
            printf("%s desmaiou!\n", nomes[time2[atual2]]);
        }

        int idx2 = time2[atual2] * 4 + atk2;
        int atkStat2 = (!strcmp(categorias_ataques[idx2], "Special")) ? spa_base[time2[atual2]] : atk_base[time2[atual2]];
        int defStat1 = (!strcmp(categorias_ataques[idx2], "Special")) ? spd_base[time1[atual1]] : def_base[time1[atual1]];
        float stab2 = (!strcmp(tipos_ataques[idx2], tipos_pokemon[time2[atual2]])) ? 1.5 : 1.0;
        float eff2 = efetividade(tipos_ataques[idx2], tipos_pokemon[time1[atual1]]);
        int dano2 = calcularDano(50, poderes[idx2], atkStat2, defStat1, stab2, eff2);

        hp1[atual1] -= dano2;
        if (hp1[atual1] < 0)
            hp1[atual1] = 0;
        printf("%s usou %s! Causou %d de dano (Efetividade %.1fx)\n", nomes[time2[atual2]], ataques_pokemon[time2[atual2]][atk2], dano2, eff2);

        if (hp1[atual1] == 0)
        {
            printf("%s desmaiou!\n", nomes[time1[atual1]]);
        }
    }
}

int main()
{
    setlocale(LC_ALL, "portuguese");

    int time1[3] = {0, 1, 2};
    int time2[3] = {3, 4, 5};

    printf("=== BATALHA POKEMON 3x3 ===\n");
    batalha(time1, time2);

    return 0;
}