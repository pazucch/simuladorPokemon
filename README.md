# 🔥 Simulador de Batalha Pokémon (C)

Este projeto é um **simulador de batalhas Pokémon 3x3** escrito em linguagem C.  
O programa permite que dois times com três Pokémons cada se enfrentem em turnos, utilizando ataques reais dos tipos _Fire_, _Water_, _Grass_, _Fighting_, _Ground_, _Ice_ e outros.

A batalha segue regras básicas inspiradas nos jogos originais:

- Tipos com efetividade (super efetivo / pouco efetivo)
- STAB (Same Type Attack Bonus)
- Ataques físicos e especiais
- Stats base (HP, Atk, Def, SpAtk, SpDef)
- Turnos alternados e desmaio

---

## 🎮 Como funciona

Cada Pokémon possui:

- Nome
- Tipo
- Lista com 4 ataques
- Stats base (HP, Ataque, Defesa, etc.)

Durante o turno:

1. O jogador escolhe um ataque para o Pokémon ativo.
2. O programa calcula o dano considerando:
   - Poder do golpe
   - Tipo do ataque
   - Tipo do Pokémon defensor
   - Categoria (_Physical_ ou _Special_)
   - STAB
   - Efetividade (x2, x0.5, etc.)
3. O Pokémon perde HP.
4. Se chegar a 0, ele desmaia e é substituído pelo próximo.

Vence o time que derrotar os três Pokémons inimigos.

---

## 🧠 Principais Mecânicas Implementadas

- ✔️ **Efetividade por tipo**
- ✔️ **STAB**
- ✔️ **Ataques físicos e especiais**
- ✔️ **Cálculo de dano baseado na 3ª geração**
- ✔️ **Troca automática após desmaio**
- ✔️ **Sistema simples de turnos**

---

## 📂 Estrutura do Código

- Dados dos Pokémons
- Dados dos ataques
- Funções principais:
  - `efetividade()`
  - `calcularDano()`
  - `escolher_ataque()`
  - `exibir_time()`
  - `batalha()`

O arquivo principal é:

simuladorpokemon.c

yaml
Copiar código

---

## 🛠️ Como compilar

### GCC

Windows:

```bash
gcc simuladorpokemon.c -o simuladorpokemon.exe -std=c99 -Wall -Wextra
```

Linux:

```bash
gcc simuladorpokemon.c -o simuladorpokemon -std=c99 -Wall -Wextra
```
 
▶️ Como executar

Windows:
```bash
./simuladorpokemon.exe
```

Linux:
```bash
./simuladorpokemon
```

---

## 🚀 Possíveis melhorias futuras
 IA para escolha de golpes

 Interface gráfica

 Sistema de velocidade para definir ordem de turnos

 Mais tipos e Pokémons

⚙️ Técnicas

 Modularizar o projeto em múltiplos arquivos

 Implementar carregamento de Pokémons via arquivo externo (.txt ou .json)

🎮 Gameplay

 Sistema de crítico

 PP para ataques

💻 Interface

 HP com barra visual e cores (ANSI)

 Sprites ASCII para cada Pokémon
