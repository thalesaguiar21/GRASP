# GRASP
GRASP Metaheuristic implementation for the Generalised Assignment Problem

# How to run

Primeiro tenha ceteza que você possui um compilador c++ 11 em sua máquina e que o sistema operacional sendo usado é o Linux. Com isso, vá ao diretório onde o repositório foi clonado e digite "make". Isso fará com que o código seja compilado, caso não ocorra nenhum erro
digite "make run" e o código será executado, o qual pedirá para que você digite o caminho para o arquivo que contém a instância, o número áximo de iterações do rGRASP e finalmente o valor do parâmetro alpha. Ao final será retornado um vetor "(1, 2, 0)" em que o índice do elemento representa a tarefa e valor contido nele o agente desisgnado para essa tarefa.