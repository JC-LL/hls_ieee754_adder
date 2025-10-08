# 💡 Synthèse HLS d'un Additionneur Flottant IEEE 754 (Simple Précision) à partir d'une description C++

## 🎯 Aperçu du Projet

Ce dépôt contient l'implémentation C++ d'un **algorithme d'addition de deux nombres à virgule flottante** au format **IEEE 754 sur 32 bits** (simple précision).

L'objectif principal de cette implémentation est sa **compatibilité avec la Synthèse de Haut Niveau (HLS)**, permettant la génération directe d'un **Additionneur Flottant IEEE** en tant que circuit matériel (Hardware) à partir de cette description logicielle !

## 🛠️ Composants Clés

* **Algorithme C++**: Développé par **Norbert Juffa**.
* **Adaptation HLS**: Le code est adapté à la Synthèse de Haut Niveau, sans modification !
* **Testbench**: Modifié et mis à jour par **Jean-Christophe Le Lann** pour exercer et valider l'algorithme.

## 🚀 Comment exécuter le projet ?

### 1. Exécution en Mode Logiciel (Pure Software)

Vous pouvez tester l'algorithme directement sur votre machine comme un programme C++ standard.

```bash
make run
```

### 2. Synthèse de Haut Niveau (HLS)
Pour générer le cœur IP de l'Additionneur Flottant pour votre FPGA ou ASIC (via Vitis HLS), utilisez la commande suivante :
```bash
vitis_hls -f run_hls.tcl
```

## 📊 Résultats et Validation

Les tests initiaux menés avec le **testbench modifié** ont confirmé l'exactitude de l'algorithme C++ de Norbert Juffa.

- 41 tests créés de toute pièce
- 1 000 000 de tests créés de manière random.

L'implémentation gère correctement l'addition de divers cas flottants, incluant les valeurs normales, les zéros, les dénormalisés et les cas d'overflow/underflow, en respectant la spécification **IEEE 754 simple précision**.

Notez qu'une **co-simulation C++-RTL** est réalisée afin de vérifier ce caractère correct du circuit généré au regard du banc de test logiciel : cette partie est la plus longue (quelques minutes). Patience.

```bash
INFO: [COSIM 212-316] Starting C post checking ...
=============================================
Testing patterns from file add.dat
=============================================
- From  41 tests, 41 PASSED 0 FAILED.
=============================================
Testing random patterns
=============================================
- From  1000000 tests, 1000000 PASSED 0 FAILED.
INFO: [COSIM 212-1000] *** C/RTL co-simulation finished: PASS ***
```

L'étape suivante de la validation est la confirmation des performances et de la faisabilité matérielle via la Synthèse de Haut Niveau (HLS).

## 📈 Performance HLS

* 14 cycles @ 130 Mhz
* 998 DFF (~0% of Artix in NexysA7)
* 6% of LUT available in NexysA7
* non-Pipelined

```bash

+---------+---------+----------+----------+-----+-----+---------+
|  Latency (cycles) |  Latency (absolute) |  Interval | Pipeline|
|   min   |   max   |    min   |    max   | min | max |   Type  |
+---------+---------+----------+----------+-----+-----+---------+
|       13|       13|  0.130 us|  0.130 us|   14|   14|     none|
+---------+---------+----------+----------+-----+-----+---------+

+-----------------+---------+-----+--------+-------+-----+
|       Name      | BRAM_18K| DSP |   FF   |  LUT  | URAM|
+-----------------+---------+-----+--------+-------+-----+
|DSP              |        -|    -|       -|      -|    -|
|Expression       |        -|    -|       0|   3825|    -|
|FIFO             |        -|    -|       -|      -|    -|
|Instance         |        -|    -|       -|      -|    -|
|Memory           |        -|    -|       -|      -|    -|
|Multiplexer      |        -|    -|       -|     61|    -|
|Register         |        -|    -|     998|      -|    -|
+-----------------+---------+-----+--------+-------+-----+
|Total            |        0|    0|     998|   3886|    0|
+-----------------+---------+-----+--------+-------+-----+
|Available        |      270|  240|  126800|  63400|    0|
+-----------------+---------+-----+--------+-------+-----+
|Utilization (%)  |        0|    0|      ~0|      6|    0|
+-----------------+---------+-----+--------+-------+-----+
```

## 🧩 RTL Interface

```bash
================================================================
== Interface
================================================================
* Summary:
+-----------+-----+-----+------------+--------------+--------------+
| RTL Ports | Dir | Bits|  Protocol  | Source Object|    C Type    |
+-----------+-----+-----+------------+--------------+--------------+
|ap_clk     |   in|    1|  ap_ctrl_hs|      fp32_add|  return value|
|ap_rst     |   in|    1|  ap_ctrl_hs|      fp32_add|  return value|
|ap_start   |   in|    1|  ap_ctrl_hs|      fp32_add|  return value|
|ap_done    |  out|    1|  ap_ctrl_hs|      fp32_add|  return value|
|ap_idle    |  out|    1|  ap_ctrl_hs|      fp32_add|  return value|
|ap_ready   |  out|    1|  ap_ctrl_hs|      fp32_add|  return value|
|ap_return  |  out|   32|  ap_ctrl_hs|      fp32_add|  return value|
|a          |   in|   32|     ap_none|             a|        scalar|
|b          |   in|   32|     ap_none|             b|        scalar|
+-----------+-----+-----+------------+--------------+--------------+
```
