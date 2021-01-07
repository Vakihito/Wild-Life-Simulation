### [Overview](#overview) | [Análises](#análises) | [Examples](#examples)  | [Executar](#executar) | [References](#references) 

# Wild-Life-Simulation

### Overview
Este projeto tem como objetivo simularcomo animais se comportariam em um ambiente, para tal definimos um estado inicial no qual alguns bixinhos buscam por comida, cada comida dá energia e pontos para o bixinho. Feito isso, aplicamos algorítmos evolutivos para melhorar a pupulação, os resultados podem ser encontrados em <code>data.csv</code>

### Executar
Para a execução deste projeto precisamos inicialmente instalar OpenGl para C++.

Para compilar deve-se compilar o código : <code>make</code>

Para se executar o executável criado: <code>make run</code>

Ou simplesmente execute: <code>make runA</code>

### Análises
Nestes nootebooks pode-se encontrar algumas análises das diferentes heurísticas que foram feitas ao longo das gerações. *Estes nootbooks só estão liberados à pessoas de email USP, caso queira acesso, enviar email para: akihito012@usp.br*

Em relação aos notebooks a baixo verificamos a distribuição de indivíduos, com base em seus genes (raio, velocidade e percepção), os dados estão normalizados com base nos dados dos indivíduos apresentados no gráfico. Além disso, indivíduos de cooloração mais viva apresentam cor mais clara.
 - **Elitismo**: [Elitismo](https://colab.research.google.com/drive/1n7B501ufRxevHtluHJtugB5h8x1YULJ0?usp=sharing)
 - **Torneio de 2**: [Torneio de 2](https://colab.research.google.com/drive/1PvCg96njYaVw2nVkTa2q4pPey0ie5cmb?usp=sharing)
 - **Roleta**: [Roleta](https://colab.research.google.com/drive/15TlJLa1dT7DNxu--EtM_KhlSb-x4ETl8?usp=sharing)
 - **Natural** : [Natural](https://colab.research.google.com/drive/1DAOj2WCbd1njS20uipnF1o_LK_92xLOp?usp=sharing)

Neste notebook, fazemos análises das diferentes heurísticas, em relação ao número de indivíduos e distância média entre os indivíduos de uma geração e o melhor da geração.
 - **Análise**: [Análises](https://colab.research.google.com/drive/1E2C6wToPrB1EkcMeVv_g5VoCWY3v7UaF?usp=sharing) 

<p align="center">
<img src="https://github.com/Vakihito/Wild-Life-Simulation/blob/main/wild.gif" width="600"/>
</p>
