#Tarea2
Se utilizó C/C++ para la elaboracion de la tarea
## Empezar
clonar este repositorio:
 ```
  https://github.com/goldrian10/Tarea2.git
 ```
## Instalación
una vez clonado escriba los siguientes comandos en su consola:
```
cd </repo directory/Tarea2>
make build
```


### Correr programa

```
gunzip -c branch-trace-gcc.trace.gz|./tarea2 -s<#>-bp<#>-gh<#>-ph<#>-o<#>
```
-s es el tamaño de la tabla
-bp es el tipo de predictor
0-bimodal
1-gshare
2-pshare
-gh es el tamaño de la historia globlal
-ph es el tamaño de la historia privada
### Desinstalar
```
make uninstall
```
