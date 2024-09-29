# Nano-Pedal
Arduino Nano Guitar Pedal with 6 Presets, 8 Digital Outputs

https://github.com/user-attachments/assets/e6ca5884-0019-4a50-946b-ab589dff7621

## Overview
This guitar pedal, controlled by an **Arduino Nano**, allows managing 8 digital outputs, which are configured into two groups of 4 outputs. The pedal also enables the creation of **6 presets**, which automatically save and restore the output configurations. A preset button allows quick selection between saved configurations, and holding this button for 2 seconds erases all stored presets.

## Operation

### Control of Digital Outputs
- The pedal controls 8 digital outputs, divided into two groups (1 to 4 and 5 to 8).
- Two navigation buttons allow switching between the outputs in each group, turning the digital outputs on or off as needed.

### Presets
- The pedal has 6 presets, which save the state of the 8 digital outputs.
- Each time the preset button is pressed, it cycles through the presets, restoring the saved configurations.
- These configurations are stored in the **EEPROM** memory of the Arduino, ensuring they are preserved even after the pedal is powered off.

### Erasing Configurations
- By holding the preset button for 2 seconds, all the configurations stored in the presets are erased, returning the pedal to its initial state.
- This allows for an easy reset of all configurations, preparing the pedal for new customizations.

---

## Portuguese Version

## Visão Geral
Este pedal de guitarra, controlado por um **Arduino Nano**, permite gerenciar 8 saídas digitais, que podem ser configuradas em dois grupos de 4 saídas. O pedal também possibilita a criação de **6 presets**, que salvam e restauram automaticamente as configurações das saídas. Um botão de preset permite a seleção rápida entre as configurações salvas, e segurar esse botão por 2 segundos apaga todos os presets armazenados.

## Funcionamento

### Controle de Saídas Digitais
- O pedal controla 8 saídas digitais, divididas em dois grupos (1 a 4 e 5 a 8). 
- Dois botões de navegação permitem alternar entre as saídas de cada grupo, ligando ou desligando as saídas digitais conforme a necessidade.

### Presets
- O pedal possui 6 presets, que salvam o estado das 8 saídas digitais.
- Cada vez que o botão de preset é pressionado, ele alterna entre os presets, restaurando as configurações salvas.
- Essas configurações são gravadas na memória **EEPROM** do Arduino, garantindo que sejam preservadas mesmo após desligar o pedal.

### Apagar Configurações
- Ao segurar o botão de preset por 2 segundos, todas as configurações armazenadas nos presets são apagadas, retornando o pedal ao estado inicial.
- Isso permite redefinir facilmente todas as configurações, preparando o pedal para novas personalizações.
