# Projet-CHP-2A-Advection
    Solving the advection equation in C++ with parallel programming with MPI

# Sequential code
    To execute the sequential code you first need to execute the command 'make' in a terminal in the code_seq repository
    Then you write the parameter you want in the parametres.txt file 
    Finally you need to execute with the './run' command in the code_seq repository

    To visualize the solution you go into a Solutions/Cas_X repository and you execute the command 'gnuplot plot_sol.txt'
    
# Parallel code
    To execute the parallel code you first need to execute the command 'make' in a terminal in the code_para repository
    Then you write the parameter you want in the parametres.txt file 
    Finally you need to execute with the 'mpiexec -n x ./run' command in the code_para repository with x the number of proc you want to use 
    (You need to make sure that the function save_sol line 31-32-47-48 in main.cc are not in commentary if you want to see the visualisation, if you are only looking for the time of execution of the code you can let them in commentary)

    To visualize the solution you go into a Solutions/Cas_X repository and you execute the command 'chmod +x show_sol.sh'
    And then you run the command './show_sol.sh'
    