# =================================================================
# Fichier: run_hls.tcl
# Description: Script Tcl pour la synthèse Vitis HLS de l'additionneur FP32.
# =================================================================

#==================================================
# 1. Configuration du projet
#==================================================
set project_name "fp32_adder_project"
set solution_name "solution1"
set top_function "fp32_add"

# Cible NexysA7 :
set part_name "xc7a100tcsg324-1"

# Periode d'horloge cible en ns (100 MHz)
set clock_period 10

#==================================================
# 2. Création du projet et de la solution
#==================================================
open_project $project_name -reset
open_solution $solution_name -flow_target vivado -reset
set_part $part_name

# Définition de la période d'horloge
create_clock -period $clock_period -name default

# Ajout des fichiers sources de conception
add_files "add.cpp"
add_files "conversions.cpp"

# Ajout des fichiers d'en-tête (nécessaire si non dans le répertoire de travail)
# Si les headers sont dans le même répertoire que les sources, ce n'est pas toujours nécessaire,
# mais c'est une bonne pratique pour les répertoires inclus.
# On suppose ici qu'ils sont dans le répertoire courant ou dans le chemin par défaut.

# Ajout des fichiers de test
add_files -tb "tb_add.cpp"
add_files -tb "add.dat"

# Définir la fonction top-level pour la synthèse
set_top $top_function

#==================================================
# 3. Exécution du flot de travail HLS
#==================================================

# 3.1. Simulation C
# Vérifie la correction fonctionnelle du code C/C++ (Doit être exécuté avec succès avant la synthèse)
csim_design

# 3.2. Synthèse C (crée le RTL)
csynth_design

# 3.3. Co-simulation C/RTL
# Vérifie que le RTL généré (VHDL/Verilog) se comporte comme le code C/C++
cosim_design

# Fermeture du projet
close_project
exit
